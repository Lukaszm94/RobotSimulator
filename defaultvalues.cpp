#include "defaultvalues.h"

DefaultValues::DefaultValues()
{

}

MachineCoordinates DefaultValues::getMachineCoordinates()
{
	MachineCoordinates machineCoordinates;
	double defaultAngle = 10;
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		machineCoordinates.setFi(i, defaultAngle);
	}
	return machineCoordinates;
}

MachineParameters DefaultValues::getMachineParameters()
{
	MachineParameters machineParameters;
	machineParameters.l_1 = 200;
	machineParameters.l_2 = 500;
	machineParameters.l_3 = 500;
	machineParameters.l_4 = 200;
	machineParameters.l_5 = 200;
	machineParameters.l_6 = 200;
	machineParameters.d = 200;
	machineParameters.e = 100;
	machineParameters.h = 500;
	return machineParameters;
}

ApproachVector DefaultValues::getApproachVector()
{
	ApproachVector approachVector;
	approachVector.psi = 45;
	approachVector.theta = 45;
	return approachVector;
}

Deltas DefaultValues::getDeltas()
{
	Deltas deltas;
	deltas.d_1 = -1;
	deltas.d_2 = 1;
	deltas.d_5 = 1;
	return deltas;
}

KinematicsMode DefaultValues::getKinematicsMode()
{
	return KinematicsMode::FORWARD;
}

int DefaultValues::getTrajectoryInterpolationPointsCount()
{
	return 60;
}

double DefaultValues::getJointsSpeed()
{
	return 40;
}

Point DefaultValues::getStartPoint()
{
	Point p;
	p.x = 800;
	p.y = 200;
	p.z = 500;
	return p;
}

Point DefaultValues::getFinishPoint()
{
	Point p;
	p.x = 200;
	p.y = 800;
	p.z = 700;
	return p;
}
