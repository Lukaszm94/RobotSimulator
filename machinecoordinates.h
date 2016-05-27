#ifndef MACHINECOORDINATES_H
#define MACHINECOORDINATES_H

#include <iostream>

#define COORDINATES_COUNT 5

struct MachineCoordinates
{
	MachineCoordinates();
	double getFi(int index) const;
	void setFi(int index, double value);
	int operator==(const MachineCoordinates& coord);
	double f_1, f_2, f_3, f_4, f_5;
};

std::ostream &operator<<(std::ostream &os, MachineCoordinates const &coordinates);


#endif // MACHINECOORDINATES_H
