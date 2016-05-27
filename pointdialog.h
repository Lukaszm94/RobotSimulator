#ifndef POINTDIALOG_H
#define POINTDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "point.h"

class PointDialog : public QDialog
{
	Q_OBJECT
public:
	explicit PointDialog(QWidget *parent = 0);
	Point getPoint();
	void setPoint(Point p);
signals:

public slots:

private:
	QLineEdit* xLineEdit, *yLineEdit, *zLineEdit;
	QPushButton* okButton, *cancelButton;
};

#endif // POINTDIALOG_H
