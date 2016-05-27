#ifndef TRAJECTORYINTERPOLATOR_H
#define TRAJECTORYINTERPOLATOR_H

#include <QObject>
#include <QVector>
#include "point.h"

#define NO_CIRCULAR_INTERPOLATION -99999999

class TrajectoryInterpolator : public QObject
{
	Q_OBJECT
public:
	explicit TrajectoryInterpolator(QObject *parent = 0);
	void setPointsCount(int pointsCount_);
	void setStartPoint(Point p);
	void setFinishPoint(Point p);
	void calculate();
	QVector<Point> getTrajectory();
signals:

public slots:

private:
	Point currentTCP, desiredTCP;
	QVector<Point> trajectoryPoints;
	int pointsCount;
};

#endif // TRAJECTORYINTERPOLATOR_H
