#include <point.h>

std::ostream &operator<<(std::ostream &os, Point const &p)
{
	os << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
	return os;
}


Point::Point(double x_, double y_, double z_)
{
	x = x_;
	y = y_;
	z = z_;
}

QString Point::toString()
{
	QString str = "[ " + QString::number(x, 'f', 1) + ", " + QString::number(y, 'f', 1) + ", " + QString::number(z, 'f', 1) + " ]";
	return str;
}
