#ifndef INVERSEKINEMATICSENGINE_H
#define INVERSEKINEMATICSENGINE_H

#include <QObject>
#include "point.h"
#include "machinecoordinates.h"
#include "deltas.h"
#include "machineparameters.h"
#include "approachvector.h"

class InverseKinematicsEngine : public QObject
{
	Q_OBJECT
public:
	explicit InverseKinematicsEngine(QObject *parent = 0);
	void setTCP(Point newTCP);
	void setMachineParameters(MachineParameters machineParameters);
	void setDeltas(Deltas deltas);
	void setApproachVector(ApproachVector approachVector);
	bool solve();
	MachineCoordinates getMachineCoordinates();

signals:

public slots:

private:
	double sSqrt(double x);
	double pow2(double x);
	Point calculateP_P();
	double calculateS_1();
	double calculateC_1();
	double calculateS_5(double S_1, double C_1);
	double calculateC_5(double S_5);
	double calculateS_234(double C_5);
	double calculateC_234(double C_5, double S_1, double C_1);
	Point calculateP_R(double C_1, double S_1, double C_234, double S_234);
	double calculateA();
	double calculateB(double a);
	double calculateS_2(double a, double b);
	double calculateC_2(double a, double b);
	double calculateS_3(double a, double b);
	double calculateC_3(double a);
	double calculateS_23(double a, double b);
	double calculateC_23(double a, double b);
	double calculateS_4(double C_234, double S_234, double C_23, double S_23);
	double calculateC_4(double C_234, double S_234, double C_23, double S_23);
	double getFi(double S, double C);
	bool isSinCosValid(double S, double C);

	MachineCoordinates machineCoordinates;
	MachineParameters machineParameters;
	Deltas deltas;
	ApproachVector approachVector;
	Point P_T, P_R, P_P;
	bool debugPrinting;
};

#endif // INVERSEKINEMATICSENGINE_H
