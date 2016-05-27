#include "timeplotwidget.h"
#include <iterator>

#define DEFAULT_X_RANGE_MS 20000

TimePlotWidget::TimePlotWidget(QWidget *parent) : QWidget(parent)
{
	plotXRange = DEFAULT_X_RANGE_MS;

	QVBoxLayout* mainLayout = new QVBoxLayout;
	plot = new QCustomPlot;

	mainLayout->addWidget(plot);

	plot->xAxis->setLabel("Time [s]");
	//plot->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	plot->legend->setVisible(true);
	plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
	plot->yAxis->setRangeLower(-200);
	plot->yAxis->setRangeUpper(200);
	plot->plotLayout()->insertRow(0); // inserts an empty row above the default axis rect
	plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(plot, "Machine coordinates"));

	this->setLayout(mainLayout);
	//this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	this->setMinimumHeight(300);
}

TimePlotWidget::~TimePlotWidget()
{
	delete plot;
}

void TimePlotWidget::addGraph(QString label, QString color)
{
	auto graph = plot->addGraph();
	graph->setName(label);
	graph->setPen(QPen(QColor(color)));

}

void TimePlotWidget::plotNewPoint(int graphNo, int timestamp, double point)
{
	//qDebug()<<"Plotting new point: x= "<<timestamp<<", y= "<<point;
	plot->graph(graphNo)->addData(timestamp / 1000.0, point);
	//plot->xAxis->setRange(timestamp+10, plotXRange, Qt::AlignRight);
	plot->xAxis->setRange((timestamp - plotXRange) / 1000.0, timestamp / 1000.0);
	plot->graph(graphNo)->removeDataBefore((timestamp - 1.2 * plotXRange) / 1000.0);
	plot->replot();
}

void TimePlotWidget::removeAllGraphs()
{
	plot->clearGraphs();
}

void TimePlotWidget::setYAxisLabel(QString label)
{
	plot->yAxis->setLabel(label);
}
