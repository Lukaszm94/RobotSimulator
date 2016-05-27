#ifndef DEFAULTVALUES_H
#define DEFAULTVALUES_H

#include "machineparameters.h"
#include "approachvector.h"
#include "deltas.h"
#include "kinematicsmode.h"
#include "machinecoordinates.h"
#include "point.h"

class DefaultValues
{
public:
	DefaultValues();
	static MachineCoordinates getMachineCoordinates();
	static MachineParameters getMachineParameters();
	static ApproachVector getApproachVector();
	static Deltas getDeltas();
	static KinematicsMode getKinematicsMode();
	static int getTrajectoryInterpolationPointsCount();
	static double getJointsSpeed();
	static Point getStartPoint();
	static Point getFinishPoint();

};

#endif // DEFAULTVALUES_H
