#include "inversekinematicsengine.h"
#include <iostream>
#include <cmath>
#define PI 3.14159265

using namespace std;

InverseKinematicsEngine::InverseKinematicsEngine(QObject *parent) : QObject(parent)
{
	debugPrinting = false;
}

void InverseKinematicsEngine::setTCP(Point newTCP)
{
	newTCP = Point(newTCP.x, newTCP.y, newTCP.z - machineParameters.h);
	P_T = newTCP;
}

void InverseKinematicsEngine::setMachineParameters(MachineParameters machineParameters)
{
	this->machineParameters = machineParameters;
}

void InverseKinematicsEngine::setDeltas(Deltas deltas)
{
	this->deltas = deltas;
}

void InverseKinematicsEngine::setApproachVector(ApproachVector approachVector)
{
	this->approachVector = approachVector;
}

bool InverseKinematicsEngine::solve()
{
// 2
	P_P = calculateP_P();
	if(debugPrinting)
		cout << "P_P: " << P_P << endl;
// 4
	double S_1 = calculateS_1();
	double C_1 = calculateC_1();
	if(debugPrinting)
		cout << "C_1= " << C_1 <<", S_1= " << S_1 << endl;
// 6
	double S_5 = calculateS_5(S_1, C_1);
	double C_5 = calculateC_5(S_5);
	if(debugPrinting)
		cout << "C_5= " << C_5 <<", S_5= " << S_5 << endl;
// 7
	double S_234 = calculateS_234(C_5);
	double C_234 = calculateC_234(C_5, S_1, C_1);
	if(debugPrinting)
		cout << "C_234= " << C_234 <<", S_234= " << S_234 << endl;
// 8
	P_R = calculateP_R(C_1, S_1, C_234, S_234);
	if(debugPrinting)
		cout << "P_R: " << P_R << endl;
// 9
	double a = calculateA();
	double b = calculateB(a);
	if(debugPrinting)
		cout << "a= " << a <<", b= " << b << endl;
// 11
	double S_2 = calculateS_2(a, b);
	double C_2 = calculateC_2(a, b);
	if(debugPrinting)
		cout << "C_2= " << C_2 <<", S_2= " << S_2 << endl;
// 12
	double S_3 = calculateS_3(a, b);
	double C_3 = calculateC_3(a);
	if(debugPrinting)
		cout << "C_3= " << C_3 <<", S_3= " << S_3 << endl;
// 13
	double S_23 = calculateS_23(a, b);
	double C_23 = calculateC_23(a, b);
	if(debugPrinting)
		cout << "C_23= " << C_23 <<", S_23= " << S_23 << endl;
// 14
	double S_4 = calculateS_4(C_234, S_234, C_23, S_23);
	double C_4 = calculateC_4(C_234, S_234, C_23, S_23);
	if(debugPrinting)
		cout << "C_4= " << C_4 <<", S_4= " << S_4 << endl;
// resolve fi
	if(isSinCosValid(S_1, C_1)) {
		machineCoordinates.f_1 = getFi(S_1, C_1);
	} else {
		return false;
	}

	if(isSinCosValid(S_2, C_2)) {
		machineCoordinates.f_2 = getFi(S_2, C_2);
	} else {
		return false;
	}

	if(isSinCosValid(S_3, C_3)) {
		machineCoordinates.f_3 = getFi(S_3, C_3);
	} else {
		return false;
	}

	if(isSinCosValid(S_4, C_4)) {
		machineCoordinates.f_4 = getFi(S_4, C_4);
	} else {
		return false;
	}

	if(isSinCosValid(S_5, C_5)) {
		machineCoordinates.f_5 = getFi(S_5, C_5);
	} else {
		return false;
	}
	return true;
}

MachineCoordinates InverseKinematicsEngine::getMachineCoordinates()
{
	return machineCoordinates;
}

double InverseKinematicsEngine::sSqrt(double x)
{
	if(x < 0.0) {
		cerr << "Sqrt argument less than 0 (=" << x <<"), returning 1" << std::endl;
		return 1.0;
	}
	return sqrt(x);
}

double InverseKinematicsEngine::pow2(double x)
{
	return x * x;
}


Point InverseKinematicsEngine::calculateP_P()
{
	Point P_P;
	double l = machineParameters.l_5 + machineParameters.l_6;
	double cos_theta = cos(approachVector.theta * PI / 180);
	double sin_theta = sin(approachVector.theta * PI / 180);
	double cos_psi = cos(approachVector.psi * PI / 180);
	double sin_psi = sin(approachVector.psi * PI / 180);
	P_P.x = P_T.x - l * cos_theta * cos_psi;
	P_P.y = P_T.y - l * cos_theta * sin_psi;
	P_P.z = P_T.z - l * sin_theta;
	return P_P;
}

double InverseKinematicsEngine::calculateS_1()
{
	double S_1 = (machineParameters.e * P_P.x + deltas.d_1 * P_P.y * sSqrt(pow2(P_P.x) + pow2(P_P.y) - pow2(machineParameters.e))) / (pow2(P_P.x) + pow2(P_P.y));
	return S_1;
}

double InverseKinematicsEngine::calculateC_1()
{
	double C_1 = (-machineParameters.e * P_P.y + deltas.d_1 * P_P.x * sSqrt(pow2(P_P.x) + pow2(P_P.y) - pow2(machineParameters.e))) / (pow2(P_P.x) + pow2(P_P.y));
	return C_1;
}

double InverseKinematicsEngine::calculateS_5(double S_1, double C_1)
{
	double cos_theta = cos(approachVector.theta * PI / 180);
	double cos_psi = cos(approachVector.psi * PI / 180);
	double sin_psi = sin(approachVector.psi * PI / 180);
	double S_5 = cos_theta * (sin_psi * C_1 - cos_psi * S_1);
	return S_5;
}

double InverseKinematicsEngine::calculateC_5(double S_5)
{
	return deltas.d_5 * sSqrt(1 - pow2(S_5));
}

double InverseKinematicsEngine::calculateS_234(double C_5)
{
	double sin_theta = sin(approachVector.theta * PI / 180);
	if(C_5 == 0.0) {
		return -999999.9;
	}
	double S_234 = sin_theta / C_5;
	return S_234;
}

double InverseKinematicsEngine::calculateC_234(double C_5, double S_1, double C_1)
{
	double cos_theta = cos(approachVector.theta * PI / 180);
	double cos_psi = cos(approachVector.psi * PI / 180);
	double sin_psi = sin(approachVector.psi * PI / 180);
	if(C_5 == 0.0) {
		return -999999.9;
	}
	double C_234 = cos_theta * (cos_psi * C_1 + sin_psi * S_1) / C_5;
	return C_234;
}

Point InverseKinematicsEngine::calculateP_R(double C_1, double S_1, double C_234, double S_234)
{
	Point P_R;
	P_R.x = P_P.x - machineParameters.l_4 * C_1 * C_234;
	P_R.y = P_P.y - machineParameters.l_4 * S_1 * C_234;
	P_R.z = P_P.z - machineParameters.l_4 * S_234;
	return P_R;
}

double InverseKinematicsEngine::calculateA()
{
	double a = -machineParameters.l_1 + deltas.d_1 * sSqrt(pow2(P_R.x) + pow2(P_R.y) - pow2(machineParameters.e));
	return a;
}

double InverseKinematicsEngine::calculateB(double a)
{
	double b = (pow2(a) + pow2(P_R.z) + pow2(machineParameters.l_2) - pow2(machineParameters.l_3)) / (2 * machineParameters.l_2);
	return b;
}

double InverseKinematicsEngine::calculateS_2(double a, double b)
{
	double S_2 = (P_R.z * b + deltas.d_2 * a * sSqrt(pow2(a) + pow2(P_R.z) - pow2(b))) / (pow2(a) + pow2(P_R.z));
	return S_2;
}

double InverseKinematicsEngine::calculateC_2(double a, double b)
{
	double C_2 = (a * b - deltas.d_2 * P_R.z * sSqrt(pow2(a) + pow2(P_R.z) - pow2(b))) / (pow2(a) + pow2(P_R.z));
	return C_2;
}

double InverseKinematicsEngine::calculateS_3(double a, double b)
{
	double S_3 = -deltas.d_2 * sSqrt(pow2(a) + pow2(P_R.z) - pow2(b)) / machineParameters.l_3;
	return S_3;
}

double InverseKinematicsEngine::calculateC_3(double a)
{
	double C_3 = (pow2(a) + pow2(P_R.z) - pow2(machineParameters.l_2) - pow2(machineParameters.l_3)) / (2 * machineParameters.l_2 * machineParameters.l_2);
	return C_3;
}

double InverseKinematicsEngine::calculateS_23(double a, double b)
{
	double S_23 = (P_R.z - machineParameters.l_2 * (P_R.z * b + deltas.d_2 * a * sSqrt(pow2(a) + pow2(P_R.z) - pow2(b))) / (pow2(a) + pow2(P_R.z))) / machineParameters.l_3;
	return S_23;
}

double InverseKinematicsEngine::calculateC_23(double a, double b)
{
	double C_23 = (a - machineParameters.l_2 * (a * b - deltas.d_2 * P_R.z * sSqrt(pow2(a) + pow2(P_R.z) - pow2(b))) / (pow2(a) + pow2(P_R.z))) / machineParameters.l_3;
	return C_23;
}

double InverseKinematicsEngine::calculateS_4(double C_234, double S_234, double C_23, double S_23)
{
	double S_4 = S_234 * C_23 - C_234 * S_23;
	return S_4;
}

double InverseKinematicsEngine::calculateC_4(double C_234, double S_234, double C_23, double S_23)
{
	double C_4 = C_234 * C_23 + S_234 * S_23;
	return C_4;
}

double InverseKinematicsEngine::getFi(double S, double C)
{
	double fi = 0.0;
	/*if(abs(S)<=abs(C))
		fi = asin(S);
	else
		fi = acos(C);
	return (fi * 180 / PI);*/
	fi = atan2(S, C) * 180 / PI;
	/*if(fi < 0.0) {
		fi += 360;
	}*/
	return fi;
}

bool InverseKinematicsEngine::isSinCosValid(double S, double C)
{
	if(abs(S)>1 || abs(C)>1 || S==NAN || C==NAN)
	{
		return false;
	}
	else
	{
		return true;
	}
}
