#include "mainwindow.h"
#include "defaultvalues.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	robotVisualisation = new RobotVisualisationWidget;
	machineCoordinatesPlot = new TimePlotWidget;
	mainLayout = new QHBoxLayout;
	setStartPointButton = new QPushButton("Set");
	setFinishPointButton  = new QPushButton("Set");
	tcpLabel = new QLabel;
	startPointLabel = new QLabel;
	finishPointLabel = new QLabel;
	forwardKinematicsRadioButton = new QRadioButton("forward");
	inverseKinematicsRadioButton = new QRadioButton("inverse");
	interpolationPointsCountSpinBox = new QSpinBox;
	startMovementButton = new QPushButton("Move");
	robotSettingsButton = new QPushButton("Settings");
	robotVisualisationTopViewButton = new QPushButton("Up");
	robotVisualisationLeftViewButton = new QPushButton("Left");
	robotVisualisationRightViewButton = new QPushButton("Right");
	robotVisualisationFrontViewButton = new QPushButton("Front");
	robotVisualisationBackViewButton = new QPushButton("Back");
	time.start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setup()
{
	QVBoxLayout* slidersLayout = new QVBoxLayout;
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QSlider* tmpSlider = new QSlider;
		QLabel* tmpLabel = new QLabel;
		QLabel* fiLabel = new QLabel("φ" + QString::number(i));
		tmpSlider->setMinimum(-180);
		tmpSlider->setMaximum(180);
		tmpSlider->setOrientation(Qt::Horizontal);
		tmpSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		tmpLabel->setFixedWidth(50);
		machineCoordinatesSliders.append(tmpSlider);
		machineCoordinatesLabels.append(tmpLabel);
		QHBoxLayout* tmpLayout = new QHBoxLayout;
		tmpLayout->addWidget(fiLabel);
		tmpLayout->addWidget(tmpSlider);
		tmpLayout->addWidget(tmpLabel);
		slidersLayout->addLayout(tmpLayout);
		connect(tmpSlider, SIGNAL(valueChanged(int)), this, SLOT(onMachineCoordinatesSliderChanged()));
	}

	QGroupBox* robotVisualisationViewGroupBox = new QGroupBox("View");
	QVBoxLayout* robotVisualisationViewLayout = new QVBoxLayout;
	QHBoxLayout* robotVisualisationViewTopLayout = new QHBoxLayout;
	QHBoxLayout* robotVisualisationViewMiddleLayout = new QHBoxLayout;
	QHBoxLayout* robotVisualisationViewBottomLayout = new QHBoxLayout;

	robotVisualisationViewTopLayout->addWidget(robotVisualisationFrontViewButton);

	robotVisualisationViewMiddleLayout->addWidget(robotVisualisationLeftViewButton);
	robotVisualisationViewMiddleLayout->addWidget(robotVisualisationTopViewButton);
	robotVisualisationViewMiddleLayout->addWidget(robotVisualisationRightViewButton);

	robotVisualisationViewBottomLayout->addWidget(robotVisualisationBackViewButton);

	robotVisualisationViewLayout->addLayout(robotVisualisationViewTopLayout);
	robotVisualisationViewLayout->addLayout(robotVisualisationViewMiddleLayout);
	robotVisualisationViewLayout->addLayout(robotVisualisationViewBottomLayout);
	robotVisualisationViewGroupBox->setLayout(robotVisualisationViewLayout);

	int viewButtonSize = 40;
	robotVisualisationTopViewButton->setFixedSize(viewButtonSize,viewButtonSize);
	robotVisualisationLeftViewButton->setFixedSize(viewButtonSize,viewButtonSize);
	robotVisualisationRightViewButton->setFixedSize(viewButtonSize,viewButtonSize);
	robotVisualisationFrontViewButton->setFixedSize(viewButtonSize,viewButtonSize);
	robotVisualisationBackViewButton->setFixedSize(viewButtonSize,viewButtonSize);

	QGroupBox* kinematicsGroupBox = new QGroupBox("Kinematics");
	QVBoxLayout* kinematicsRadioButtonsLayout = new QVBoxLayout;
	kinematicsRadioButtonsLayout->addWidget(forwardKinematicsRadioButton);
	kinematicsRadioButtonsLayout->addWidget(inverseKinematicsRadioButton);
	kinematicsGroupBox->setLayout(kinematicsRadioButtonsLayout);

	QVBoxLayout* tcpLayout = new QVBoxLayout;
	tcpLayout->addWidget(new QLabel("<b>TCP:</b>"));
	tcpLayout->addWidget(tcpLabel);

	QVBoxLayout* startPointLayout = new QVBoxLayout;
	QHBoxLayout* startPointUpperLayout = new QHBoxLayout;
	startPointUpperLayout->addWidget(new QLabel("<b>Start point:</b>"));
	startPointUpperLayout->addWidget(setStartPointButton);
	startPointLayout->addLayout(startPointUpperLayout);
	startPointLayout->addWidget(startPointLabel);
	startPointLabel->setFixedWidth(150);
	setStartPointButton->setFixedWidth(50);

	QVBoxLayout* finishPointLayout = new QVBoxLayout;
	QHBoxLayout* finishPointUpperLayout = new QHBoxLayout;
	finishPointUpperLayout->addWidget(new QLabel("<b>Finish point:</b>"));
	finishPointUpperLayout->addWidget(setFinishPointButton);
	finishPointLayout->addLayout(finishPointUpperLayout);
	finishPointLayout->addWidget(finishPointLabel);
	finishPointLabel->setFixedWidth(150);
	setFinishPointButton->setFixedWidth(50);

	QHBoxLayout* interpolationPointsCountLayout = new QHBoxLayout;
	interpolationPointsCountLayout->addWidget(new QLabel("Interpolations points count"));
	interpolationPointsCountLayout->addWidget(interpolationPointsCountSpinBox);

	QVBoxLayout* controlPanelLayout = new QVBoxLayout;
	controlPanelLayout->addWidget(robotVisualisationViewGroupBox);
	controlPanelLayout->addWidget(kinematicsGroupBox);
	controlPanelLayout->addWidget(new QLabel("<b>Machine coordinates</b>"));
	controlPanelLayout->addLayout(slidersLayout);
	controlPanelLayout->addLayout(tcpLayout);
	controlPanelLayout->addLayout(startPointLayout);
	controlPanelLayout->addLayout(finishPointLayout);
	controlPanelLayout->addWidget(new QLabel("<b>Linear interpolation:</b>"));
	controlPanelLayout->addLayout(interpolationPointsCountLayout);
	controlPanelLayout->addWidget(startMovementButton);
	controlPanelLayout->addWidget(robotSettingsButton);
	controlPanelLayout->addStretch();

	QVBoxLayout* leftColumnLayout = new QVBoxLayout;
	leftColumnLayout->addWidget(robotVisualisation);
	leftColumnLayout->addWidget(machineCoordinatesPlot);

	QWidget* mainWidget = new QWidget;
	mainLayout->addLayout(leftColumnLayout);
	mainLayout->addLayout(controlPanelLayout);
	mainWidget->setLayout(mainLayout);
	this->setCentralWidget(mainWidget);
	this->setGeometry(100,100,1024,768);
	this->setWindowTitle("Robot Simulator");

	connect(forwardKinematicsRadioButton, SIGNAL(pressed()), this, SLOT(onForwardKinematicsSelected()));
	connect(inverseKinematicsRadioButton, SIGNAL(pressed()), this, SLOT(onInverseKinematicsSelected()));
	connect(robotSettingsButton, SIGNAL(clicked(bool)), this, SLOT(onSettingsButtonClicked()));
	connect(setStartPointButton, SIGNAL(clicked(bool)), this, SLOT(onSetStartPointButtonClicked()));
	connect(setFinishPointButton, SIGNAL(clicked(bool)), this, SLOT(onSetFinishPointButtonClicked()));
	connect(startMovementButton, SIGNAL(clicked(bool)), this, SLOT(onMoveButtonClicked()));
	connect(robotVisualisationTopViewButton, SIGNAL(clicked(bool)), this, SLOT(onSetViewTopButtonClicked()));
	connect(robotVisualisationLeftViewButton, SIGNAL(clicked(bool)), this, SLOT(onSetViewLeftButtonClicked()));
	connect(robotVisualisationRightViewButton, SIGNAL(clicked(bool)), this, SLOT(onSetViewRightButtonClicked()));
	connect(robotVisualisationFrontViewButton, SIGNAL(clicked(bool)), this, SLOT(onSetViewFrontButtonClicked()));
	connect(robotVisualisationBackViewButton, SIGNAL(clicked(bool)), this, SLOT(onSetViewBackButtonClicked()));
	loadDefaultValues();
	setupMachineCoordinatesPlot();
	interpolationPointsCountSpinBox->setMaximum(250);
}

MachineCoordinates MainWindow::getMachineCoordinates()
{
	MachineCoordinates coords;
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QSlider* slider = machineCoordinatesSliders.at(i);
		double fi = slider->value();
		coords.setFi(i, fi);
	}
	return coords;
}

void MainWindow::setMachineCoordinates(MachineCoordinates coords)
{
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QSlider* slider = machineCoordinatesSliders.at(i);
		double fi = coords.getFi(i);
		slider->setValue(fi);
	}
}

void MainWindow::setTCP(QString str)
{
	tcpLabel->setText(str);
}

int MainWindow::getInterpolationPointsCount()
{
	return interpolationPointsCountSpinBox->value();
}

void MainWindow::updateMachineCoordinatesPlot(MachineCoordinates coords)
{
	int currentTime = time.elapsed();
	for(int i = 0 ; i < COORDINATES_COUNT; i++) {
		machineCoordinatesPlot->plotNewPoint(i, currentTime, coords.getFi(i));
	}
}

void MainWindow::updateRobotVisualisation(QVector<Point> points)
{
	robotVisualisation->setRobotJointsPoints(points);
}

void MainWindow::setForwardKinematicsMode()
{
	setKinematicsMode(true);
}

void MainWindow::setInverseKinematicsMode()
{
	setKinematicsMode(false);
}

void MainWindow::setStartPointLabel(QString label)
{
	startPointLabel->setText(label);
}

void MainWindow::setFinishPointLabel(QString label)
{
	finishPointLabel->setText(label);
}

void MainWindow::onMachineCoordinatesSliderChanged()
{
	updateMachineCoordinatesLabels();
	emit machineCoordinatesSliderChanged();
}

void MainWindow::onForwardKinematicsSelected()
{
	qDebug() << "MainWindow::onForwardKinematicsSelected()";
	emit forwardKinematicsSelected();
}

void MainWindow::onInverseKinematicsSelected()
{
	qDebug() << "MainWindow::onInverseKinematicsSelected()";
	emit inverseKinematicsSelected();
}

void MainWindow::onSettingsButtonClicked()
{
	emit settingsButtonClicked();
}

void MainWindow::onSetStartPointButtonClicked()
{
	emit setStartPointButtonClicked();
}

void MainWindow::onSetFinishPointButtonClicked()
{
	emit setFinishPointButtonClicked();
}

void MainWindow::onMoveButtonClicked()
{
	emit moveButtonClicked();
}

void MainWindow::onSetViewTopButtonClicked()
{
	robotVisualisation->setViewAngles(0,0,0);
}

void MainWindow::onSetViewLeftButtonClicked()
{
	robotVisualisation->setViewAngles(-90,0,0);
}

void MainWindow::onSetViewRightButtonClicked()
{
	robotVisualisation->setViewAngles(-90,0,180);
}

void MainWindow::onSetViewFrontButtonClicked()
{
	robotVisualisation->setViewAngles(-90,0,-90);
}

void MainWindow::onSetViewBackButtonClicked()
{
	robotVisualisation->setViewAngles(-90,0,90);
}

void MainWindow::updateMachineCoordinatesLabels()
{
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QSlider* slider = machineCoordinatesSliders.at(i);
		QLabel* label = machineCoordinatesLabels.at(i);
		double fi = slider->value();
		label->setText(QString::number(fi, 'φ', 1));
	}
}

void MainWindow::setKinematicsMode(bool forward)
{
	setStartPointButton->setEnabled(!forward);
	setFinishPointButton->setEnabled(!forward);
	interpolationPointsCountSpinBox->setEnabled(!forward);
	startMovementButton->setEnabled(!forward);
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QSlider* tmpSlider = machineCoordinatesSliders.at(i);
		tmpSlider->setEnabled(forward);
	}
}

void MainWindow::loadDefaultValues()
{
	MachineCoordinates coords = DefaultValues::getMachineCoordinates();
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QSlider* slider = machineCoordinatesSliders.at(i);
		slider->setValue(coords.getFi(i));
	}
	if(DefaultValues::getKinematicsMode() == KinematicsMode::FORWARD) {
		forwardKinematicsRadioButton->setChecked(true);
	} else {
		inverseKinematicsRadioButton->setChecked(true);
	}
	interpolationPointsCountSpinBox->setValue(DefaultValues::getTrajectoryInterpolationPointsCount());
}

void MainWindow::setupMachineCoordinatesPlot()
{
	QString colors[] = {"red", "blue", "green", "magenta", "black"};
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		QString name = "φ" + QString::number(i + 1);
		machineCoordinatesPlot->addGraph(name, colors[i]);
	}
}
