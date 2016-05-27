#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include <QObject>
#include <QVector>
#include "machinecoordinates.h"
#include "machineparameters.h"
#include "point.h"
#include "approachvector.h"

#define DEFAULT_JOINTS_SPEED 200 // deg/s

class RobotModel : public QObject
{
	Q_OBJECT
public:
	explicit RobotModel(QObject *parent = 0);
	void forceSetCurrentPosition(MachineCoordinates newCoordinates);
	void appendMachineCoordinate(MachineCoordinates newCoordinates);
	void clearMachineCoordinatesQueue();
	void setJointsSpeeds(QVector<double> speeds); // in deg/s
	void setJointsSpeed(double speed); // in deg/s
	void setParameters(MachineParameters parameters);
	MachineCoordinates getCurrentPosition();
	QVector<Point> getCurrentJointsPoints();
	QVector<Point> getJointsPoints(MachineCoordinates coords);
	void update();

signals:

public slots:

//private:
public:
	double deg2rad(double deg);
	MachineCoordinates currentPosition;
	MachineParameters machineParameters;
	QVector<double> jointsSpeeds; // in deg/s
	QVector<MachineCoordinates> coordinatesQueue;
	int lastUpdateTime;
};

#endif // ROBOTMODEL_H
