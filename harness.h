#ifndef HARNESS_H
#define HARNESS_H

#include <QObject>
#include <QTimer>
#include "inversekinematicsengine.h"
#include "trajectoryinterpolator.h"
#include "robotmodel.h"
#include "gui.h"
#include "kinematicsmode.h"

class Harness : public QObject
{
	Q_OBJECT
public:
	explicit Harness(QObject *parent = 0);

public slots:
	void onMachineCoordinatesSliderChanged();
	void onForwardKinematicsSelected();
	void onInverseKinematicsSelected();
	void onStartMovementButtonPressed();
	void onRobotParametersChanged();
	void onSystemTimerTimeout();
private:
	void loadDefaultValues();

	QTimer* systemTimer;
	GUI* gui;
	RobotModel* robotModel;
	InverseKinematicsEngine* inverseKinematics;
	TrajectoryInterpolator* trajectoryInterpolator;
	MachineParameters machineParameters;
	ApproachVector approachVector;
	Deltas deltas;
	KinematicsMode kinematicsMode;
};

#endif // HARNESS_H
