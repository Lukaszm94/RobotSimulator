#ifndef TIMEPLOTWIDGET_H
#define TIMEPLOTWIDGET_H

#include <QtWidgets>
#include "qcustomplot.h"


class TimePlotWidget : public QWidget
{
	Q_OBJECT
public:
	TimePlotWidget(QWidget* parent = 0);
	~TimePlotWidget();
	void addGraph(QString label, QString color);
	void plotNewPoint(int graphNo, int timestamp, double point);
	void removeAllGraphs();
	void setYAxisLabel(QString label);

private:
	void updatePlotAxesRanges();
	double getGraphMaxValue(int index);

	QCustomPlot* plot;
	int plotXRange;
};

#endif // TIMEPLOTWIDGET_H
