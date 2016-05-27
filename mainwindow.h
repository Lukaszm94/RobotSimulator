#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robotvisualisationwidget.h"
#include "machinecoordinates.h"
#include "timeplotwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void setup();
	MachineCoordinates getMachineCoordinates();
	void setMachineCoordinates(MachineCoordinates coords);
	void setTCP(QString str);
	int getInterpolationPointsCount();
	void updateMachineCoordinatesPlot(MachineCoordinates coords);
	void updateRobotVisualisation(QVector<Point> points);
	void setForwardKinematicsMode();
	void setInverseKinematicsMode();
	void setStartPointLabel(QString label);
	void setFinishPointLabel(QString label);
public slots:

private slots:
	void onMachineCoordinatesSliderChanged();
	void onForwardKinematicsSelected();
	void onInverseKinematicsSelected();
	void onSettingsButtonClicked();
	void onSetStartPointButtonClicked();
	void onSetFinishPointButtonClicked();
	void onMoveButtonClicked();
	void onSetViewTopButtonClicked();
	void onSetViewLeftButtonClicked();
	void onSetViewRightButtonClicked();
	void onSetViewFrontButtonClicked();
	void onSetViewBackButtonClicked();
signals:
	void forwardKinematicsSelected();
	void inverseKinematicsSelected();
	void setStartPointButtonClicked();
	void setFinishPointButtonClicked();
	void moveButtonClicked();
	void settingsButtonClicked();
	void machineCoordinatesSliderChanged();

private:
	void updateMachineCoordinatesLabels();
	void setKinematicsMode(bool forward);
	void loadDefaultValues();
	void setupMachineCoordinatesPlot();

	QHBoxLayout* mainLayout;
	RobotVisualisationWidget* robotVisualisation;
	TimePlotWidget* machineCoordinatesPlot;
	QVector<QSlider*> machineCoordinatesSliders;
	QVector<QLabel*> machineCoordinatesLabels;
	QRadioButton* forwardKinematicsRadioButton, *inverseKinematicsRadioButton;
	QLabel* tcpLabel;
	QLabel* startPointLabel, *finishPointLabel;
	QPushButton* setStartPointButton;
	QPushButton* setFinishPointButton;
	QSpinBox* interpolationPointsCountSpinBox;
	QPushButton* startMovementButton;
	QPushButton* robotSettingsButton;
	QPushButton* robotVisualisationTopViewButton;
	QPushButton* robotVisualisationLeftViewButton;
	QPushButton* robotVisualisationRightViewButton;
	QPushButton* robotVisualisationFrontViewButton;
	QPushButton* robotVisualisationBackViewButton;
	QTime time;


};

#endif // MAINWINDOW_H
