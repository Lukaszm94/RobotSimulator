#include "harness.h"
#include <QDebug>
#include <iostream>
#include <QVector>
#include "defaultvalues.h"
#define SYSTEM_TIMER_UPDATE_INTERVAL_MS 20

Harness::Harness(QObject *parent) : QObject(parent)
{
	qRegisterMetaType<Point>("Point");
	systemTimer = new QTimer;
	robotModel = new RobotModel;
	inverseKinematics = new InverseKinematicsEngine;
	trajectoryInterpolator = new TrajectoryInterpolator;
	gui = new GUI;

	loadDefaultValues();

	systemTimer->setInterval(SYSTEM_TIMER_UPDATE_INTERVAL_MS);

	robotModel->setParameters(machineParameters);
	connect(systemTimer, SIGNAL(timeout()), this, SLOT(onSystemTimerTimeout()));
	connect(gui, SIGNAL(machineCoordinatesSliderChanged()), this, SLOT(onMachineCoordinatesSliderChanged()));
	connect(gui, SIGNAL(forwardKinematicsSelected()), this, SLOT(onForwardKinematicsSelected()));
	connect(gui, SIGNAL(inverseKinematicsSelected()), this, SLOT(onInverseKinematicsSelected()));
	connect(gui, SIGNAL(parametersChanged()), this, SLOT(onRobotParametersChanged()));
	connect(gui, SIGNAL(startMovementButtonClicked()), this, SLOT(onStartMovementButtonPressed()));
	systemTimer->start();
}

void Harness::onMachineCoordinatesSliderChanged()
{
	if(kinematicsMode == KinematicsMode::INVERSE) {
		return;
	}
	MachineCoordinates coords = gui->getMachineCoordinates();
	//std::cout << coords << std::endl;
	robotModel->appendMachineCoordinate(coords);
}

void Harness::onForwardKinematicsSelected()
{
	kinematicsMode = KinematicsMode::FORWARD;
	gui->setForwardKinematicsMode();
}

void Harness::onInverseKinematicsSelected()
{
	kinematicsMode = KinematicsMode::INVERSE;
	gui->setInverseKinematicsMode();
}

void Harness::onStartMovementButtonPressed()
{
	if(kinematicsMode == KinematicsMode::FORWARD) {
		return;
	}
	Point startPoint = gui->getStartPoint();
	Point finishPoint = gui->getFinishPoint();
	int trajectoryInterpolationPointsCount = gui->getInterpolationPointsCount();
	std::cout << "Start point: " << startPoint << std::endl;
	std::cout << "Finish point: " << finishPoint << std::endl;
	trajectoryInterpolator->setStartPoint(startPoint);
	trajectoryInterpolator->setFinishPoint(finishPoint);
	trajectoryInterpolator->setPointsCount(trajectoryInterpolationPointsCount);
	trajectoryInterpolator->calculate();
	QVector<Point> trajectory = trajectoryInterpolator->getTrajectory();
	bool intermediatePointsReachable;
	intermediatePointsReachable = true;
	int i = 0, trajectorySize = trajectory.size();
	QVector<MachineCoordinates> coords;
	for(Point p : trajectory) {
		inverseKinematics->setTCP(p);
		bool currentPointReachable = inverseKinematics->solve();
		if((i == 0) || (i == (trajectorySize - 1))) { // first or last point
			if(!currentPointReachable) {
				QString pointDescr = "finish";
				if(i == 0) {
					pointDescr = "start";
				}
				QString message = "Cannot set TCP in " + pointDescr + " point";
				gui->showMessage(message);
				//TODO print some kind of error message, notify user
				//TODO break or return
				return;
			}
		}
		if(currentPointReachable) {
			coords.append(inverseKinematics->getMachineCoordinates());
		} else {
			intermediatePointsReachable = false;
		}
		i++;
	}

	if(!intermediatePointsReachable) {
		if(!gui->askQuestion("Some interpolation points are not reachable, do you want to skip them? If no, the movement will be cancelled.")) {
			return;
		}
	}

	//check for hitting the ground
	bool groundHit = false;
	for(MachineCoordinates coord : coords) {
		QVector<Point> points = robotModel->getJointsPoints(coord);
		for(Point p : points) {
			if(p.z < 0) {
				groundHit = true;
			}
		}
	}
	if(groundHit) {
		if(!gui->askQuestion("The robot can hit the ground (z < 0 for at least one joint during the movement). Do you want to continue?")) {
			return;
		}
	}

	robotModel->clearMachineCoordinatesQueue();
	robotModel->forceSetCurrentPosition(coords.first());
	for(MachineCoordinates coord : coords) {
		//std::cout << coord << std::endl;
		robotModel->appendMachineCoordinate(coord);
	}
}

void Harness::onRobotParametersChanged()
{
	machineParameters = gui->getMachineParameters();
	approachVector = gui->getApproachVector();
	deltas = gui->getDeltas();

	if(approachVector.psi == 0.0) {
		approachVector.psi = 0.01;
	}
	if(approachVector.theta == 0.0) {
		approachVector.theta = 0.01;
	}

	inverseKinematics->setApproachVector(approachVector);
	inverseKinematics->setDeltas(deltas);
	inverseKinematics->setMachineParameters(machineParameters);
	robotModel->setJointsSpeed(gui->getJointsSpeed());
	robotModel->setParameters(machineParameters);
	robotModel->clearMachineCoordinatesQueue();
}

void Harness::onSystemTimerTimeout()
{
	robotModel->update();
	QVector<Point> jointsPoints = robotModel->getCurrentJointsPoints();
	gui->updateRobotVisualisation(jointsPoints);
	gui->setTCP(jointsPoints.last());
	gui->updateMachineCoordinatesPlot(robotModel->getCurrentPosition());
	if(kinematicsMode == KinematicsMode::INVERSE) {
		gui->setMachineCoodinates(robotModel->getCurrentPosition());
	}
}

void Harness::loadDefaultValues()
{
	kinematicsMode = DefaultValues::getKinematicsMode();
	if(kinematicsMode == KinematicsMode::FORWARD) {
		gui->setForwardKinematicsMode();
	} else {
		gui->setInverseKinematicsMode();
	}
	onRobotParametersChanged();
}
