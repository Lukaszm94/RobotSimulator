#include "pointdialog.h"

PointDialog::PointDialog(QWidget *parent) : QDialog(parent)
{
	xLineEdit = new QLineEdit;
	yLineEdit = new QLineEdit;
	zLineEdit = new QLineEdit;
	okButton = new QPushButton("OK");
	cancelButton = new QPushButton("Cancel");

	QHBoxLayout* lineEditsLayout = new QHBoxLayout;
	lineEditsLayout->addWidget(new QLabel("x"));
	lineEditsLayout->addWidget(xLineEdit);
	lineEditsLayout->addWidget(new QLabel("y"));
	lineEditsLayout->addWidget(yLineEdit);
	lineEditsLayout->addWidget(new QLabel("z"));
	lineEditsLayout->addWidget(zLineEdit);
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(okButton);
	buttonsLayout->addWidget(cancelButton);
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(lineEditsLayout);
	mainLayout->addLayout(buttonsLayout);
	this->setLayout(mainLayout);
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
	this->setWindowTitle("Enter point coordinates:");
}

Point PointDialog::getPoint()
{
	bool okFlag = true;
	double x = xLineEdit->text().toDouble(&okFlag);
	if(!okFlag)
		x = 0;
	double y = yLineEdit->text().toDouble(&okFlag);
	if(!okFlag)
		y = 0;
	double z = zLineEdit->text().toDouble(&okFlag);
	if(!okFlag)
		z = 0;
	return Point(x,y,z);
}

void PointDialog::setPoint(Point p)
{
	xLineEdit->setText(QString::number(p.x, 'f', 1));
	yLineEdit->setText(QString::number(p.y, 'f', 1));
	zLineEdit->setText(QString::number(p.z, 'f', 1));
}
