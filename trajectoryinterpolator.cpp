#include "trajectoryinterpolator.h"
#include <qdebug.h>

#define MINIMUM_POINTS_COUNT 1

TrajectoryInterpolator::TrajectoryInterpolator(QObject *parent) : QObject(parent)
{
	pointsCount = MINIMUM_POINTS_COUNT;
}

void TrajectoryInterpolator::setPointsCount(int pointsCount_)
{
	pointsCount = pointsCount_;
	if(pointsCount < MINIMUM_POINTS_COUNT) {
		pointsCount = MINIMUM_POINTS_COUNT;
	}
}

void TrajectoryInterpolator::setStartPoint(Point p)
{
	currentTCP = p;
}

void TrajectoryInterpolator::setFinishPoint(Point p)
{
	desiredTCP = p;
}

void TrajectoryInterpolator::calculate()
{
	trajectoryPoints.clear();
	double dx = desiredTCP.x - currentTCP.x;
	double dy = desiredTCP.y - currentTCP.y;
	double dz = desiredTCP.z - currentTCP.z;
	double stepX = dx / pointsCount;
	double stepY = dy / pointsCount;
	double stepZ = dz / pointsCount;
	Point point = currentTCP;
	trajectoryPoints.append(point);
	for(int i = 0; i < pointsCount; i++) {
		point.x += stepX;
		point.y += stepY;
		point.z += stepZ;
		trajectoryPoints.append(point);
	}
}

QVector<Point> TrajectoryInterpolator::getTrajectory()
{
	return trajectoryPoints;
}
