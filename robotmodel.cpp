#include "robotmodel.h"
#include <QTime>
#include <cmath>
#include <iostream>
#include "defaultvalues.h"

#define PI 3.14159265

RobotModel::RobotModel(QObject *parent) : QObject(parent)
{
	lastUpdateTime = QTime::currentTime().msecsSinceStartOfDay();
	currentPosition = DefaultValues::getMachineCoordinates();
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		jointsSpeeds.append(DEFAULT_JOINTS_SPEED);
	}
}

void RobotModel::forceSetCurrentPosition(MachineCoordinates newCoordinates)
{
	currentPosition = newCoordinates;
}

void RobotModel::appendMachineCoordinate(MachineCoordinates newCoordinates)
{
	if(coordinatesQueue.isEmpty()) {
		lastUpdateTime = QTime::currentTime().msecsSinceStartOfDay();
	}
	coordinatesQueue.append(newCoordinates);
	//std::cout << "RobotModel::appendMachineCoordinate: queue size: " << coordinatesQueue.size() << std::endl;
}

void RobotModel::clearMachineCoordinatesQueue()
{
	coordinatesQueue.clear();
}

void RobotModel::setJointsSpeeds(QVector<double> speeds)
{
	jointsSpeeds = speeds;
}

void RobotModel::setJointsSpeed(double speed)
{
	jointsSpeeds.clear();
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		jointsSpeeds.append(speed);
	}
}

void RobotModel::setParameters(MachineParameters parameters)
{
	machineParameters = parameters;
}

MachineCoordinates RobotModel::getCurrentPosition()
{
	return currentPosition;
}

QVector<Point> RobotModel::getCurrentJointsPoints()
{
	return getJointsPoints(currentPosition);
}

QVector<Point> RobotModel::getJointsPoints(MachineCoordinates coords)
{
	QVector<Point> jointsPoints;
	Point p;
	double x, y, z;
	x = y = z = 0;

	double C1, S1, C2, S2, C5, S5, C23, S23, C234, S234, C15, S15/*, Ctheta, Stheta, Cpsi, Spsi*/;
	C1 = cos(deg2rad(coords.f_1));
	S1 = sin(deg2rad(coords.f_1));
	C2 = cos(deg2rad(coords.f_2));
	S2 = sin(deg2rad(coords.f_2));
	C5 = cos(deg2rad(coords.f_5));
	S5 = sin(deg2rad(coords.f_5));
	C23 = cos(deg2rad(coords.f_2 + coords.f_3));
	S23 = sin(deg2rad(coords.f_2 + coords.f_3));
	C234 = cos(deg2rad(coords.f_2 + coords.f_3 + coords.f_4));
	S234 = sin(deg2rad(coords.f_2 + coords.f_3 + coords.f_4));
	C15 = cos(deg2rad(coords.f_1 + coords.f_5));
	S15 = sin(deg2rad(coords.f_1 + coords.f_5));
	//Ctheta = cos(deg2rad(approachVector.theta));
	//Stheta = sin(deg2rad(approachVector.theta));
	//Cpsi = cos(deg2rad(approachVector.psi));
	//Spsi = sin(deg2rad(approachVector.psi));

	// P0
	p = Point(0,0,machineParameters.h);
	jointsPoints.append(p);
	// P1
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P2
	x = machineParameters.l_1 * C1;
	y = machineParameters.l_1 * S1;
	z = 0;
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P3
	x = machineParameters.d * S1;
	y = -machineParameters.d * C1;
	z = 0;
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P4
	x = machineParameters.l_2 * C1 * C2;
	y = machineParameters.l_2 * S1 * C2;
	z = machineParameters.l_2 * S2;
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P5
	x = -(machineParameters.d - machineParameters.e) * S1;
	y = (machineParameters.d - machineParameters.e) * C1;
	z = 0;
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P6
	x = machineParameters.l_3 * C23 * C1;
	y = machineParameters.l_3 * S1 * C23;
	z = machineParameters.l_3 * S23;
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P7
	x = machineParameters.l_4 * C234 * C1;
	y = machineParameters.l_4 * C234 * S1;
	z = machineParameters.l_4 * S234;
	Point p7 = p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P8
	x = machineParameters.l_5 * (C1 * C234 * C5 - S1 * S5);
	y = machineParameters.l_5 * (S1 * C234 * C5 + C1 * S5);
	z = machineParameters.l_5 * S234 * C5;
	p = Point(p.x + x, p.y + y, p.z + z);
	jointsPoints.append(p);
	// P9
	/*double l = machineParameters.l_5 + machineParameters.l_6;
	x = l * Ctheta * Cpsi;
	y = l * Ctheta * Spsi;
	z = l * Stheta;
	p = Point(p.x + x, p.y + y, p.z + z);*/
	x = machineParameters.l_6 * (C1 * C234 * C5 - S1 * S5);
	y = machineParameters.l_6 * (S1 * C234 * C5 + C1 * S5);
	z = machineParameters.l_6 * S234 * C5;
	p = Point(p.x + x, p.y + y, p.z + z);

	//P8
	//P8 calculations using machine coordinates only doesn't work (it has to do something with
	//deltas, I don't have time to dig into that, let's cheat a bit)
	//P8 is average of point P7 and P9
	/*x = (p7.x * machineParameters.l_5 + p.x * machineParameters.l_6) / l;
	y = (p7.y * machineParameters.l_5 + p.y * machineParameters.l_6) / l;
	z = (p7.z * machineParameters.l_5 + p.z * machineParameters.l_6) / l;
	Point p8 = Point(x,y,z);
	jointsPoints.append(p8);*/

	jointsPoints.append(p);

	//int i = 0;
	/*std::cout << "RobotModel: joints points: " << std::endl;
	for(Point pt : jointsPoints) {
		std::cout << "P" << i << " " << pt << std::endl;
		i++;
	}
	std::cout << "------" << std::endl;*/
	return jointsPoints;
}

void RobotModel::update()
{
	if(coordinatesQueue.isEmpty()) {
		return;
	}
	MachineCoordinates desiredPosition = coordinatesQueue.first();
	int dt = QTime::currentTime().msecsSinceStartOfDay() - lastUpdateTime; // in ms
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		double maxAngularMovement = jointsSpeeds.at(i) * (double) dt / 1000.0;
		double desiredAngularMovement = desiredPosition.getFi(i) - currentPosition.getFi(i);
		if(fabs(desiredAngularMovement) <= maxAngularMovement) {
			currentPosition.setFi(i, desiredPosition.getFi(i));
		} else {
			if(fabs(desiredAngularMovement) > 180) {
				maxAngularMovement = -maxAngularMovement;
			}
			float sign = 1.0;
			if(desiredAngularMovement < 0.0)
				sign = -1.0;

			double currentFi = currentPosition.getFi(i) + sign * maxAngularMovement;
			if(currentFi < -180) {
				currentFi += 360;
			}
			if(currentFi > 180) {
				currentFi -= 360;
			}
			currentPosition.setFi(i, currentFi);
		}
	}
	bool removeFromQueue = true;
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		if(currentPosition.getFi(i) != desiredPosition.getFi(i)) {
			removeFromQueue = false;
			break;
		}
	}
	if(removeFromQueue) {
		coordinatesQueue.removeFirst();
	}
	lastUpdateTime = QTime::currentTime().msecsSinceStartOfDay();
}

double RobotModel::deg2rad(double deg)
{
	return (PI * deg / 180.0);
}
