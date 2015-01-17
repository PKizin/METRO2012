// Sector.h

#pragma once

#include "stdafx.h"
#include <iostream>
#include "Train.h"

enum Col {Red, Blue};

class Sector
{
private:
	double mRadius;

	// Angles for sector position.
	double mStartAngle;
	double mEndAngle;
	double mCenterAngle;

	// Agnles for train movement state.
	double mDepartAngle;
	double mFractAngle;
	double mDestAngle;

	double mThickness;
	double mSpeed;
	Col	   mColor;
	Dir    mDirection;

public:
	Sector();
	Sector(double radius, 
		   double startAngle, 
		   double endAngle, 
		   double centerAngle,
		   double departAngle,
		   double fractAngle,
		   double destAngle,
		   double thick, 
		   double speed, 
		   Col color, 
		   Dir direct);
	~Sector();

	double Radius();		// Return a radius.
	double StartAngle();	// Return angle of the start.
	double EndAngle();		// Return angle of the end.
	double CenterAngle();	// Return angle of the center.
	double DepartAngle();
	double FractAngle();
	double DestAngle();
	double Thickness();		// Return a thickness.
	double Speed();			// Return a speed.
	Col Color();			// Return a color.
	Dir Direction();		// Return a direction.

	void Info();		// Showing information about a sector on the screen.
	void Move();		// Moving the sector around/against of the circle.

	void CheckAngle();											// Checking if the angle of the sector more than 2*PI.	
	void CheckTrainPosition(double pos, double eps, St state);	// Checking if the train deviates from a center point.
};
