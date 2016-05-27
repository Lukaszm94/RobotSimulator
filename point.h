#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <QString>

struct Point
{
	Point(double x_ = 0, double y_ = 0, double z_ = 0);
	QString toString();
	double x, y, z;
};

std::ostream &operator<<(std::ostream &os, Point const &p);

#endif // POINT_H
