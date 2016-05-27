#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include "QDialog"
#include <QtWidgets>
#include "machineparameters.h"
#include "approachvector.h"
#include "deltas.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT
public:
	explicit SettingsDialog(QWidget* parent = 0);
	MachineParameters getMachineParameters();
	Deltas getDeltas();
	ApproachVector getApproachVector();
	double getJointsSpeed();

private:
	void loadDefaultValues();

	QLineEdit* l_1LineEdit;
	QLineEdit* l_2LineEdit;
	QLineEdit* l_3LineEdit;
	QLineEdit* l_4LineEdit;
	QLineEdit* l_5LineEdit;
	QLineEdit* l_6LineEdit;
	QLineEdit* dLineEdit;
	QLineEdit* eLineEdit;
	QLineEdit* hLineEdit;
	QLineEdit* psiLineEdit;
	QLineEdit* thetaLineEdit;
	QLineEdit* jointsSpeedLineEdit;
	QRadioButton* delta1PlusRadioButton;
	QRadioButton* delta1MinusRadioButton;
	QRadioButton* delta2PlusRadioButton;
	QRadioButton* delta2MinusRadioButton;
	QRadioButton* delta5PlusRadioButton;
	QRadioButton* delta5MinusRadioButton;
	QPushButton* okButton;
	QPushButton* cancelButton;
};

#endif // SETTINGSDIALOG_H
