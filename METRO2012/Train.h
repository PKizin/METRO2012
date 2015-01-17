// Train.h

#pragma once

#include "stdafx.h"
#include "iostream"
#include <math.h>
#include <vector>

#define PI acos(-1.0)

enum Dir {Around, Against};
enum St {AcceleratedToCenter, 
		 DeceleratedToCenter, 
		 Moved, 
		 Stopped, 
		 AcceleratedToStation, 
		 DeceleratedToStation,
		 AcceleratedFromStation,
		 DeceleratedFromStation,
		 Waited};

class Train
{
private:
	double mRadius;
	double mAngle;
	double mSpeed;
	double mAcceleration;
	double mTimer1;			// timer for sector.
	double mTimer2;			// timer for stopping.
	double mTimer3;			// timer for arriving.
	double mTimer4;			// timer for departure.
	Dir    mDirection;
	St	   mState;

public:
	Train();
	Train(double radius, 
		  double angle, 
		  double speed, 
		  double acceleration,
		  double timer1, 
		  double timer2, 
		  double timer3,
		  double timer4,
		  Dir direct, 
		  St state);
	~Train();

	double Radius();
	double Angle();
	double Speed();
	double Acceleration();
	double Timer1();
	double Timer2();
	double Timer3();
	double Timer4();
	Dir    Direction();
	St	   State();

	//void ChangeAngle(double angle);
	//void ChangeSpeed(double speed);
	//void ChangeTimer1(double timer1);
	//void ChangeTimer2(double timer2);
	//void ChangeState(St state);

	void Move();
	void Stop();
	void AccelerateToCenter();
	void AccelerateToStation();
	void DecelerateToCenter();
	void DecelerateToStation();
	void AccelerateFromStation();
	void DecelerateFromStation();

	void CheckAngle(double fi1, double fi2);
	void CheckTimer2();
	void CheckStopping(double pos, double eps);
	void CheckSectorCenter(double fi1, double fi2, double fi3);
	void CheckArrive(double fi1, double fi2, double fi3, int tr1, int tr2);
	void CheckDeparture(double fi1, double fi2, double fi3);
};