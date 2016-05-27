#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QtWidgets>
#include <QVector>
#include "point.h"
#include "mainwindow.h"
#include "robotvisualisationwidget.h"
#include "machinecoordinates.h"
#include "pointdialog.h"
#include "machineparameters.h"
#include "deltas.h"
#include "approachvector.h"
#include "settingsdialog.h"

class GUI : public QObject
{
	Q_OBJECT
public:
	explicit GUI(QObject *parent = 0);
	MachineCoordinates getMachineCoordinates(); // forward kinematics mode
	void setMachineCoodinates(MachineCoordinates coords); // inverse kinematics mode
	void setTCP(Point tcp);
	void setForwardKinematicsMode();
	void setInverseKinematicsMode();
	int getInterpolationPointsCount();
	Point getStartPoint();
	Point getFinishPoint();
	MachineParameters getMachineParameters();
	Deltas getDeltas();
	ApproachVector getApproachVector();
	double getJointsSpeed();
	void updateRobotVisualisation(QVector<Point> points);
	void updateMachineCoordinatesPlot(MachineCoordinates coords);
	void showMessage(QString message);
	bool askQuestion(QString question);

signals:
	void forwardKinematicsSelected();
	void inverseKinematicsSelected();
	void machineCoordinatesSliderChanged();
	void startMovementButtonClicked();
	void parametersChanged();
private slots: // internal
	void onMachineCoordinatesSliderChanged();
	void onSetStartPointButtonClicked();
	void onSetFinishPointButtonClicked();
	void onMoveButtonClicked();
	void onSettingsButtonClicked();
	void onForwardKinematicsSelected();
	void onInverseKinematicsSelected();
private:
	void setupMachineCoordinatesPlot();

	MainWindow* mainWindow;
	PointDialog* startPointDialog;
	PointDialog* finishPointDialog;
	SettingsDialog* settingsDialog;


};

#endif // GUI_H
