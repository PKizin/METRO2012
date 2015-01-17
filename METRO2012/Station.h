// Station.h

#pragma once

#include "stdafx.h"
#include <iostream>
#include "Train.h"

class Station
{
private:
	double mRadius;
	double mAngle;
	double mStartViewAngle;
	double mEndViewAngle;

	// Agnles for train movement state.
	double *mDepartAngleToStation;
	double *mFractAngleToStation;
	double *mDestAngleToStation;

	double *mDepartAngleFromStation;
	double *mFractAngleFromStation;
	double *mDestAngleFromStation;

	bool mState;
	int  mCaptured;		// Index of captured train.

public:
	Station();
	Station( double radius, 
			 double angle, 
			 double startViewAngle, 
			 double endViewAngle );
	~Station();
	
	double Radius();
	double Angle();
	double StartViewAngle();
	double EndViewAngle();
	double DepartAngleToStation(int index);
	double FractAngleToStation(int index);
	double DestAngleToStation(int index);
	double DepartAngleFromStation(int index);
	double FractAngleFromStation(int index);
	double DestAngleFromStation(int index);
	bool   State();
	int    Captured();

	void CheckAngle();
	void CheckTrainPosition(int index, double pos, Dir direct, double eps);
};