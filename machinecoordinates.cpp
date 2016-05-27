#include "machinecoordinates.h"
#include <QDebug>

#define DEFAULT_COORDINATES_VALUE 0

std::ostream &operator<<(std::ostream &os, const MachineCoordinates &coordinates)
{
	os << "[ " << coordinates.f_1 << " , " << coordinates.f_2 << " , " << coordinates.f_3 << " , " << coordinates.f_4 << " , " << coordinates.f_5 << " ]";
	return os;
}


MachineCoordinates::MachineCoordinates()
{
	f_1 = f_2 = f_3 = f_4 = f_5 = DEFAULT_COORDINATES_VALUE;
}

double MachineCoordinates::getFi(int index) const
{
	if(index == 0)
		return f_1;
	else if(index == 1)
		return f_2;
	else if(index == 2)
		return f_3;
	else if(index == 3)
		return f_4;
	else if(index == 4)
		return f_5;
	else {
		qDebug() << "MachineCoordinates: FATAL ERROR, wrong index!";
		return 0;
	}
}

void MachineCoordinates::setFi(int index, double value)
{
	if(index == 0)
		f_1 = value;
	else if(index == 1)
		f_2 = value;
	else if(index == 2)
		f_3 = value;
	else if(index == 3)
		f_4 = value;
	else if(index == 4)
		f_5 = value;
	else {
		qDebug() << "MachineCoordinates: FATAL ERROR, wrong index!";
	}
}

int MachineCoordinates::operator==(const MachineCoordinates &coord)
{
	for(int i = 0; i < COORDINATES_COUNT; i++) {
		if(this->getFi(i) != coord.getFi(i))
			return false;
	}
	return true;
}
