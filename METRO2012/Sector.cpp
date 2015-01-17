// Sector.cpp

#include "stdafx.h"
#include "Sector.h"

Sector::Sector() : mRadius(0),
				   mStartAngle(0),
				   mEndAngle(0),
				   mCenterAngle(0),
				   mThickness(0),
				   mSpeed(0),
				   mColor(Red),
				   mDirection(Around) {}

Sector::Sector(double radius, 
			   double startAngle, 
			   double endAngle, 
			   double centerAngle,
			   double departAngle,
			   double fractAngle,
			   double destAngle,
			   double thick, 
			   double speed, 
			   Col color, 
			   Dir direct) : mRadius(radius),
							 mStartAngle(startAngle),
							 mEndAngle(endAngle),
							 mCenterAngle(centerAngle),
							 mDepartAngle(departAngle),
							 mFractAngle(fractAngle),
							 mDestAngle(destAngle),
							 mThickness(thick),
							 mSpeed(speed),
							 mColor(color),
							 mDirection(direct) {}


Sector::~Sector() {}

double Sector::Radius()		 {return mRadius;}
double Sector::StartAngle()	 {return mStartAngle;}
double Sector::EndAngle()	 {return mEndAngle;}
double Sector::CenterAngle() {return mCenterAngle;}
double Sector::DepartAngle() {return mDepartAngle;}
double Sector::FractAngle()  {return mFractAngle;}
double Sector::DestAngle()   {return mDestAngle;}
double Sector::Thickness()	 {return mThickness;}
double Sector::Speed()		 {return mSpeed;}
Col	Sector::Color()			 {return mColor;}
Dir Sector::Direction()		 {return mDirection;}

void Sector::Info()
{
	std::cout << "=================="			  << std::endl;
	std::cout << "Radius	  = " << mRadius	  << std::endl;
	std::cout << "StartAngle  = " << mStartAngle  << std::endl;
	std::cout << "EndAngle    = " << mEndAngle	  << std::endl;
	std::cout << "CenterAngle = " << mCenterAngle << std::endl;
	std::cout << "DepartAngle = " << mDepartAngle << std::endl;
	std::cout << "FractAngle  = " << mFractAngle  << std::endl;
	std::cout << "DestAngle   = " << mDestAngle   << std::endl;
	std::cout << "Thickness   = " << mThickness	  << std::endl;
	std::cout << "Speed		  = " << mSpeed		  << std::endl;
	std::cout << "Color		  = " << mColor		  << std::endl;
	std::cout << "Direction   = " << mDirection	  << std::endl;
}

void Sector::Move()
{
	if (mDirection == Around)
	{
		mStartAngle  += mSpeed*PI/180;
		mEndAngle    += mSpeed*PI/180;
		mCenterAngle += mSpeed*PI/180;
		if ((mDepartAngle != 0)||(mFractAngle != 0)||(mDestAngle != 0))
		{	
			mDepartAngle += mSpeed*PI/180;
			mFractAngle	 += mSpeed*PI/180;
			mDestAngle	 += mSpeed*PI/180;
		}
	}
	else
	{
		mStartAngle  -= mSpeed*PI/180;
		mEndAngle    -= mSpeed*PI/180;
		mCenterAngle -= mSpeed*PI/180;
		if ((mDepartAngle != 0)||(mFractAngle != 0)||(mDestAngle != 0))
		{	
			mDepartAngle -= mSpeed*PI/180;
			mFractAngle	 -= mSpeed*PI/180;
			mDestAngle	 -= mSpeed*PI/180;
		}
	}
}

void Sector::CheckAngle()
{
	/*if (mCenterAngle >= 2*PI)
		mCenterAngle -= 2*PI;
	if (mCenterAngle < 0)
		mCenterAngle += 2*PI;*/
	if ((mStartAngle >= 2*PI)&&(mEndAngle >= 2*PI))
	{
		mStartAngle -= 2*PI;
		mCenterAngle -= 2*PI;
		mEndAngle -= 2*PI;
	}
	if ((mStartAngle < 0)&&(mEndAngle < 0))
	{
		mStartAngle += 2*PI;
		mCenterAngle += 2*PI;
		mEndAngle += 2*PI;
	}
	if ((mDepartAngle != 0)||(mFractAngle != 0)||(mDestAngle != 0))
	{
		/*if (mFractAngle >= 2*PI)
			mFractAngle -= 2*PI;
		if (mFractAngle < 0)
			mFractAngle += 2*PI;*/
		if ((mStartAngle >= 2*PI)&&(mEndAngle >= 2*PI))
		{
			mDepartAngle -= 2*PI;
			mFractAngle -= 2*PI;
			mDestAngle -= 2*PI;
		}
		if ((mStartAngle < 0)&&(mEndAngle < 0))
		{
			mDepartAngle += 2*PI;
			mFractAngle += 2*PI;
			mDestAngle += 2*PI;
		}
	}
}

void Sector::CheckTrainPosition(double pos, double eps, St state)
{
	// While the train stops on the station
	// we don't ñonsider its position
	if (state == Stopped) 
	{
		mDepartAngle = 0;
		mDestAngle   = 0;
		mFractAngle  = 0;
		return;
	}

	if ((abs(mCenterAngle - pos) > eps)&&(abs(mCenterAngle - pos) < PI))
	{
		if ((mDepartAngle == 0)&&(mFractAngle == 0)&&(mDestAngle == 0))
		{
			mDepartAngle = pos;
			mDestAngle   = mCenterAngle;
			mFractAngle  = (mDepartAngle + mDestAngle) / 2;
		}
	}
	else
	{
		mDepartAngle = 0;
		mDestAngle   = 0;
		mFractAngle  = 0;
	}
}