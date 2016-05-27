#include "settingsdialog.h"
#include "defaultvalues.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
	l_1LineEdit = new QLineEdit;
	l_2LineEdit = new QLineEdit;
	l_3LineEdit = new QLineEdit;
	l_4LineEdit = new QLineEdit;
	l_5LineEdit = new QLineEdit;
	l_6LineEdit = new QLineEdit;
	dLineEdit = new QLineEdit;
	eLineEdit = new QLineEdit;
	hLineEdit = new QLineEdit;
	psiLineEdit = new QLineEdit;
	thetaLineEdit = new QLineEdit;
	jointsSpeedLineEdit = new QLineEdit;
	delta1PlusRadioButton = new QRadioButton;
	delta1MinusRadioButton = new QRadioButton;
	delta2PlusRadioButton = new QRadioButton;
	delta2MinusRadioButton = new QRadioButton;
	delta5PlusRadioButton = new QRadioButton;
	delta5MinusRadioButton = new QRadioButton;
	okButton = new QPushButton("Ok");
	cancelButton = new QPushButton("Cancel");

	int lineEditWidth = 50;
	l_1LineEdit->setFixedWidth(lineEditWidth);
	l_2LineEdit->setFixedWidth(lineEditWidth);
	l_3LineEdit->setFixedWidth(lineEditWidth);
	l_4LineEdit->setFixedWidth(lineEditWidth);
	l_5LineEdit->setFixedWidth(lineEditWidth);
	l_6LineEdit->setFixedWidth(lineEditWidth);
	dLineEdit->setFixedWidth(lineEditWidth);
	eLineEdit->setFixedWidth(lineEditWidth);
	hLineEdit->setFixedWidth(lineEditWidth);
	psiLineEdit->setFixedWidth(lineEditWidth);
	thetaLineEdit->setFixedWidth(lineEditWidth);
	jointsSpeedLineEdit->setFixedWidth(lineEditWidth);

	QHBoxLayout* l_1Layout = new QHBoxLayout;
	l_1Layout->addWidget(new QLabel("l1"));
	l_1Layout->addWidget(l_1LineEdit);
	l_1Layout->addWidget(new QLabel("mm"));

	QHBoxLayout* l_2Layout = new QHBoxLayout;
	l_2Layout->addWidget(new QLabel("l2"));
	l_2Layout->addWidget(l_2LineEdit);
	l_2Layout->addWidget(new QLabel("mm"));

	QHBoxLayout* l_3Layout = new QHBoxLayout;
	l_3Layout->addWidget(new QLabel("l3"));
	l_3Layout->addWidget(l_3LineEdit);
	l_3Layout->addWidget(new QLabel("mm"));

	QHBoxLayout* l_4Layout = new QHBoxLayout;
	l_4Layout->addWidget(new QLabel("l4"));
	l_4Layout->addWidget(l_4LineEdit);
	l_4Layout->addWidget(new QLabel("mm"));

	QHBoxLayout* l_5Layout = new QHBoxLayout;
	l_5Layout->addWidget(new QLabel("l5"));
	l_5Layout->addWidget(l_5LineEdit);
	l_5Layout->addWidget(new QLabel("mm"));

	QHBoxLayout* l_6Layout = new QHBoxLayout;
	l_6Layout->addWidget(new QLabel("l6"));
	l_6Layout->addWidget(l_6LineEdit);
	l_6Layout->addWidget(new QLabel("mm"));

	QHBoxLayout* dLayout = new QHBoxLayout;
	dLayout->addWidget(new QLabel("d"));
	dLayout->addWidget(dLineEdit);
	dLayout->addWidget(new QLabel("mm"));

	QHBoxLayout* eLayout = new QHBoxLayout;
	eLayout->addWidget(new QLabel("e"));
	eLayout->addWidget(eLineEdit);
	eLayout->addWidget(new QLabel("mm"));

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->addWidget(new QLabel("h"));
	hLayout->addWidget(hLineEdit);
	hLayout->addWidget(new QLabel("mm"));

	QHBoxLayout* psiLayout = new QHBoxLayout;
	psiLayout->addWidget(new QLabel("Ψ"));
	psiLayout->addWidget(psiLineEdit);
	psiLayout->addWidget(new QLabel("°"));

	QHBoxLayout* thetaLayout = new QHBoxLayout;
	thetaLayout->addWidget(new QLabel("Θ"));
	thetaLayout->addWidget(thetaLineEdit);
	thetaLayout->addWidget(new QLabel("°"));

	QHBoxLayout* jointsSpeedLayout = new QHBoxLayout;
	jointsSpeedLayout->addWidget(new QLabel("ω"));
	jointsSpeedLayout->addWidget(jointsSpeedLineEdit);
	jointsSpeedLayout->addWidget(new QLabel("°/s"));

	QHBoxLayout* delta1Layout = new QHBoxLayout;
	delta1Layout->addWidget(new QLabel("δ1"));
	delta1Layout->addStretch();
	delta1Layout->addWidget(delta1PlusRadioButton);
	delta1Layout->addWidget(new QLabel("+1"));
	delta1Layout->addWidget(delta1MinusRadioButton);
	delta1Layout->addWidget(new QLabel("-1"));
	QGroupBox* delta1GroupBox = new QGroupBox;
	delta1GroupBox->setLayout(delta1Layout);

	QHBoxLayout* delta2Layout = new QHBoxLayout;
	delta2Layout->addWidget(new QLabel("δ2"));
	delta2Layout->addStretch();
	delta2Layout->addWidget(delta2PlusRadioButton);
	delta2Layout->addWidget(new QLabel("+1"));
	delta2Layout->addWidget(delta2MinusRadioButton);
	delta2Layout->addWidget(new QLabel("-1"));
	QGroupBox* delta2GroupBox = new QGroupBox;
	delta2GroupBox->setLayout(delta2Layout);

	QHBoxLayout* delta5Layout = new QHBoxLayout;
	delta5Layout->addWidget(new QLabel("δ5"));
	delta5Layout->addStretch();
	delta5Layout->addWidget(delta5PlusRadioButton);
	delta5Layout->addWidget(new QLabel("+1"));
	delta5Layout->addWidget(delta5MinusRadioButton);
	delta5Layout->addWidget(new QLabel("-1"));
	QGroupBox* delta5GroupBox = new QGroupBox;
	delta5GroupBox->setLayout(delta5Layout);

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(okButton);
	buttonsLayout->addWidget(cancelButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(new QLabel("<b>Regional part</b>"));
	mainLayout->addLayout(l_1Layout);
	mainLayout->addLayout(l_2Layout);
	mainLayout->addLayout(l_3Layout);
	mainLayout->addLayout(dLayout);
	mainLayout->addLayout(eLayout);
	mainLayout->addWidget(new QLabel("<b>Local part</b>"));
	mainLayout->addLayout(l_4Layout);
	mainLayout->addLayout(l_5Layout);
	mainLayout->addLayout(l_6Layout);
	mainLayout->addWidget(new QLabel("<b>Base height</b>"));
	mainLayout->addLayout(hLayout);
	mainLayout->addWidget(new QLabel("<b>Approach vector</b>"));
	mainLayout->addLayout(psiLayout);
	mainLayout->addLayout(thetaLayout);
	mainLayout->addWidget(new QLabel("<b>Position criterion</b>"));
	mainLayout->addWidget(delta1GroupBox);
	mainLayout->addWidget(delta2GroupBox);
	mainLayout->addWidget(delta5GroupBox);
	mainLayout->addWidget(new QLabel("<b>Joints speed</b>"));
	mainLayout->addLayout(jointsSpeedLayout);
	mainLayout->addLayout(buttonsLayout);
	this->setLayout(mainLayout);
	this->setWindowTitle("Settings");
	loadDefaultValues();
	connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

MachineParameters SettingsDialog::getMachineParameters()
{
	MachineParameters params;
	params.l_1 = l_1LineEdit->text().toDouble();
	params.l_2 = l_2LineEdit->text().toDouble();
	params.l_3 = l_3LineEdit->text().toDouble();
	params.l_4 = l_4LineEdit->text().toDouble();
	params.l_5 = l_5LineEdit->text().toDouble();
	params.l_6 = l_6LineEdit->text().toDouble();
	params.d = dLineEdit->text().toDouble();
	params.e = eLineEdit->text().toDouble();
	params.h = hLineEdit->text().toDouble();
	return params;
}

Deltas SettingsDialog::getDeltas()
{
	Deltas deltas;
	if(delta1PlusRadioButton->isChecked()) {
		deltas.d_1 = 1;
	} else {
		deltas.d_1 = -1;
	}
	if(delta2PlusRadioButton->isChecked()) {
		deltas.d_2 = 1;
	} else {
		deltas.d_2 = -1;
	}
	if(delta5PlusRadioButton->isChecked()) {
		deltas.d_5 = 1;
	} else {
		deltas.d_5 = -1;
	}
	return deltas;
}

ApproachVector SettingsDialog::getApproachVector()
{
	ApproachVector approachVector;
	approachVector.psi = psiLineEdit->text().toDouble();
	approachVector.theta = thetaLineEdit->text().toDouble();
	return approachVector;
}

double SettingsDialog::getJointsSpeed()
{
	double jointsSpeed = jointsSpeedLineEdit->text().toDouble();
	return jointsSpeed;
}

void SettingsDialog::loadDefaultValues()
{
	MachineParameters params = DefaultValues::getMachineParameters();
	Deltas deltas = DefaultValues::getDeltas();
	ApproachVector approachVector = DefaultValues::getApproachVector();
	double jointsSpeed = DefaultValues::getJointsSpeed();
	l_1LineEdit->setText(QString::number(params.l_1, 'f', 0));
	l_2LineEdit->setText(QString::number(params.l_2, 'f', 0));
	l_3LineEdit->setText(QString::number(params.l_3, 'f', 0));
	l_4LineEdit->setText(QString::number(params.l_4, 'f', 0));
	l_5LineEdit->setText(QString::number(params.l_5, 'f', 0));
	l_6LineEdit->setText(QString::number(params.l_6, 'f', 0));
	dLineEdit->setText(QString::number(params.d, 'f', 0));
	eLineEdit->setText(QString::number(params.e, 'f', 0));
	hLineEdit->setText(QString::number(params.h, 'f', 0));
	psiLineEdit->setText(QString::number(approachVector.psi, 'f', 0));
	thetaLineEdit->setText(QString::number(approachVector.theta, 'f', 0));
	jointsSpeedLineEdit->setText(QString::number(jointsSpeed, 'f', 0));
	if(deltas.d_1 == 1) {
		delta1PlusRadioButton->setChecked(true);
	} else {
		delta1MinusRadioButton->setChecked(true);
	}
	if(deltas.d_2 == 1) {
		delta2PlusRadioButton->setChecked(true);
	} else {
		delta2MinusRadioButton->setChecked(true);
	}
	if(deltas.d_5 == 1) {
		delta5PlusRadioButton->setChecked(true);
	} else {
		delta5MinusRadioButton->setChecked(true);
	}
}
