#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "inversekinematicsengine.h"
#include "trajectoryinterpolator.h"
#include "robotvisualisationwidget.h"
#include "robotmodel.h"
#include "gui.h"
#include "harness.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

//inverse kinematics test
	/*InverseKinematicsEngine inverseKinematics;
	MachineParameters machineParameters;
	ApproachVector approachVector;
	Deltas deltas;
	Point P_T;

	machineParameters.l_1 = 200;
	machineParameters.l_2 = 1000;
	machineParameters.l_3 = 1000;
	machineParameters.l_4 = 200;
	machineParameters.l_5 = 200;
	machineParameters.l_6 = 200;
	machineParameters.d = 200;
	machineParameters.e = 100;
	machineParameters.h = 500;

	approachVector.psi = 45;
	approachVector.theta = 45;

	deltas.d_1 = 1;
	deltas.d_2 = 1;
	deltas.d_5 = 1;

	P_T.x = 1000;
	P_T.y = 1000;
	P_T.z = 500;
	inverseKinematics.setApproachVector(approachVector);
	inverseKinematics.setDeltas(deltas);
	inverseKinematics.setMachineParameters(machineParameters);
	inverseKinematics.setTCP(P_T);
	if(inverseKinematics.solve()) {
		cout << inverseKinematics.getMachineCoordinates() << endl;
	} else {
		cout << "Invalid TCP" << endl;
	}

//trajectory interpolator test
	TrajectoryInterpolator interpolator;
	Point from, to;
	from.x = from.y = from.z = 10;
	to.x = to.y = to.z = 20;
	interpolator.setStartPoint(from);
	interpolator.setFinishPoint(to);
	interpolator.setPointsCount(1);
	interpolator.calculate();
	QVector<Point> points = interpolator.getTrajectory();
	for(Point point : points) {
		cout << point;
	}
	cout << endl;

//robot visualisation test
	RobotVisualisationWidget* robotVisualisation = new RobotVisualisationWidget;
	//w.setCentralWidget(robotVisualisation);
	QVector<Point> jointsPoints;
	jointsPoints.append(Point());
	jointsPoints.append(Point(0,1000,1000));
	jointsPoints.append(Point(3, 0, 1));
	jointsPoints.append(Point(0, 2, 1));
	jointsPoints.append(Point(2, 2, 0));
	jointsPoints.append(Point(1, 0, 1));
	jointsPoints.append(Point(3, 3, 3));
	robotVisualisation->setRobotJointsPoints(jointsPoints);

//robot model test
	RobotModel robotModel;
	MachineCoordinates machineCoordinates;
	machineCoordinates.f_1 = 0;
	machineCoordinates.f_2 = 0;
	machineCoordinates.f_3 = 0;
	machineCoordinates.f_4 = 0;
	machineCoordinates.f_5 = 0;

	robotModel.setParameters(machineParameters);
	robotModel.currentPosition = inverseKinematics.getMachineCoordinates();
	//robotModel.currentPosition = machineCoordinates;
	robotVisualisation->setRobotJointsPoints(robotModel.getCurrentJointsPoints());

//robot model test2
	Point P1(1000, 1000, 500);
	Point P2(1500, 1500, 500);
	interpolator.setStartPoint(P1);
	interpolator.setFinishPoint(P2);
	interpolator.setPointsCount(5);
	interpolator.calculate();
	QVector<Point> trajectory = interpolator.getTrajectory();
	for(Point p : trajectory) {
		inverseKinematics.setTCP(p);
		if(inverseKinematics.solve()) {
			robotModel.appendMachineCoordinate(inverseKinematics.getMachineCoordinates());
		} else {
			cout << "Wrong TCP: " << p << std::endl;
		}
	}*/

	Harness* harness = new Harness;
	return a.exec();
}
