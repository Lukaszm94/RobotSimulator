#include "gui.h"
#include "defaultvalues.h"

GUI::GUI(QObject *parent) : QObject(parent)
{
	mainWindow = new MainWindow;
	startPointDialog = new PointDialog;
	finishPointDialog = new PointDialog;
	settingsDialog = new SettingsDialog;
	mainWindow->setup();

	mainWindow->show();
	startPointDialog->setPoint(DefaultValues::getStartPoint());
	finishPointDialog->setPoint(DefaultValues::getFinishPoint());
	mainWindow->setStartPointLabel(startPointDialog->getPoint().toString());
	mainWindow->setFinishPointLabel(finishPointDialog->getPoint().toString());

	connect(mainWindow, SIGNAL(machineCoordinatesSliderChanged()), this, SLOT(onMachineCoordinatesSliderChanged()));
	connect(mainWindow, SIGNAL(forwardKinematicsSelected()), this, SLOT(onForwardKinematicsSelected()));
	connect(mainWindow, SIGNAL(inverseKinematicsSelected()), this, SLOT(onInverseKinematicsSelected()));
	connect(mainWindow, SIGNAL(settingsButtonClicked()), this, SLOT(onSettingsButtonClicked()));
	connect(mainWindow, SIGNAL(setStartPointButtonClicked()), this, SLOT(onSetStartPointButtonClicked()));
	connect(mainWindow, SIGNAL(setFinishPointButtonClicked()), this, SLOT(onSetFinishPointButtonClicked()));
	connect(mainWindow, SIGNAL(moveButtonClicked()), this, SLOT(onMoveButtonClicked()));
}

MachineCoordinates GUI::getMachineCoordinates()
{
	return mainWindow->getMachineCoordinates();
}

void GUI::setMachineCoodinates(MachineCoordinates coords)
{
	mainWindow->setMachineCoordinates(coords);
}

void GUI::setTCP(Point tcp)
{
	mainWindow->setTCP(tcp.toString());
}

void GUI::setForwardKinematicsMode()
{
	mainWindow->setForwardKinematicsMode();
}

void GUI::setInverseKinematicsMode()
{
	mainWindow->setInverseKinematicsMode();
}

int GUI::getInterpolationPointsCount()
{
	return mainWindow->getInterpolationPointsCount();
}

Point GUI::getStartPoint()
{
	return startPointDialog->getPoint();
}

Point GUI::getFinishPoint()
{
	return finishPointDialog->getPoint();
}

MachineParameters GUI::getMachineParameters()
{
	return settingsDialog->getMachineParameters();
}

Deltas GUI::getDeltas()
{
	return settingsDialog->getDeltas();
}

ApproachVector GUI::getApproachVector()
{
	return settingsDialog->getApproachVector();
}

double GUI::getJointsSpeed()
{
	return settingsDialog->getJointsSpeed();
}

void GUI::onMachineCoordinatesSliderChanged()
{
	emit machineCoordinatesSliderChanged();
}

void GUI::updateRobotVisualisation(QVector<Point> points)
{
	mainWindow->updateRobotVisualisation(points);
}

void GUI::updateMachineCoordinatesPlot(MachineCoordinates coords)
{
	mainWindow->updateMachineCoordinatesPlot(coords);
}

void GUI::showMessage(QString message)
{
	QMessageBox::critical(mainWindow, "Information", message, QMessageBox::Ok, QMessageBox::Ok);
}

bool GUI::askQuestion(QString question)
{
	if(QMessageBox::question(mainWindow, "Question", question, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
		return true;
	}
	return false;
}

void GUI::onSetStartPointButtonClicked()
{
	int retCode = startPointDialog->exec();
	if(retCode == QDialog::Accepted) {
		Point p = startPointDialog->getPoint();
		mainWindow->setStartPointLabel(p.toString());
	}
}

void GUI::onSetFinishPointButtonClicked()
{
	int retCode = finishPointDialog->exec();
	if(retCode == QDialog::Accepted) {
		Point p = finishPointDialog->getPoint();
		mainWindow->setFinishPointLabel(p.toString());
	}
}

void GUI::onMoveButtonClicked()
{
	emit startMovementButtonClicked();
}

void GUI::onSettingsButtonClicked()
{
	int retCode = settingsDialog->exec();
	if(retCode == QDialog::Accepted) {
		emit parametersChanged();
	}
}

void GUI::onForwardKinematicsSelected()
{
	emit forwardKinematicsSelected();
}

void GUI::onInverseKinematicsSelected()
{
	emit inverseKinematicsSelected();
}
