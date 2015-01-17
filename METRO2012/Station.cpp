// Station.cpp

#include "stdafx.h"
#include "Station.h"

//extern double eps;
extern int trains;
extern int stations;

Station::Station() : mRadius(0),
					 mAngle(0),
					 mStartViewAngle(0),
					 mEndViewAngle(0),
					 mDepartAngleToStation(0),
					 mFractAngleToStation(0),
					 mDestAngleToStation(0),
					 mDepartAngleFromStation(0),
					 mFractAngleFromStation(0),
					 mDestAngleFromStation(0),
					 mState(false),
					 mCaptured(100500) {}

Station::Station( double radius, 
				  double angle, 
				  double startViewAngle, 
				  double endViewAngle) : mRadius(radius), 
										 mAngle(angle),
										 mStartViewAngle(startViewAngle),
										 mEndViewAngle(endViewAngle)
{
	mDepartAngleToStation = new double[1000];
	mFractAngleToStation = new double[1000];
	mDestAngleToStation = new double[1000];
	mDepartAngleFromStation = new double[1000];
	mFractAngleFromStation = new double[1000];
	mDestAngleFromStation = new double[1000];
	for (int i=0; i<trains; ++i)
	{
		mDepartAngleToStation[i] = 0;
		mFractAngleToStation[i] = 0;
		mDestAngleToStation[i] = 0;
		mDepartAngleFromStation[i] = 0;
		mFractAngleFromStation[i] = 0;
		mDestAngleFromStation[i] = 0;
	}
	mState = false;
	mCaptured = 100500;
}

Station::~Station() 
{
	for (int i=0; i<trains; ++i)
	{
		mDepartAngleToStation[i] = 0;
		mFractAngleToStation[i] = 0;
		mDestAngleToStation[i] = 0;
		mDepartAngleFromStation[i] = 0;
		mFractAngleFromStation[i] = 0;
		mDestAngleFromStation[i] = 0;
	}
	//delete(mOutsideDepartAngle);
	//delete(mOutsideFractAngle);
	//delete(mOutsideDestAngle);
}

double Station::Radius()		 {return mRadius;}
double Station::Angle()			 {return mAngle;}
double Station::StartViewAngle() {return mStartViewAngle;}
double Station::EndViewAngle()	 {return mEndViewAngle;}

double Station::DepartAngleToStation(int index)	  {return mDepartAngleToStation[index];}
double Station::FractAngleToStation(int index)	  {return mFractAngleToStation[index];}
double Station::DestAngleToStation(int index)	  {return mDestAngleToStation[index];}
double Station::DepartAngleFromStation(int index) {return mDepartAngleFromStation[index];}
double Station::FractAngleFromStation(int index)  {return mFractAngleFromStation[index];}
double Station::DestAngleFromStation(int index)	  {return mDestAngleFromStation[index];}

bool Station::State()	{return mState;}
int Station::Captured() {return mCaptured;}


void Station::CheckAngle()
{
	if (mAngle >= 2*PI) mAngle -= 2*PI;
	if (mAngle < 0) mAngle += 2*PI;
}

void Station::CheckTrainPosition(int index, double pos, Dir direct, double eps)
{
	if (abs(mAngle-pos) < eps)
	{
		mState = false;
		mCaptured = 100500;
	}
	if (direct == Around)
	{
		// To Station.
		if (((pos > mStartViewAngle)&&(pos < mAngle))||
			((pos-2*PI > mStartViewAngle)&&(pos-2*PI < mAngle))||
			((pos+2*PI > mStartViewAngle)&&(pos+2*PI < mAngle)))
		{
				if (mState == false)
				{
					mDepartAngleToStation[index] = pos;
					mDestAngleToStation[index]   = mAngle;
					mFractAngleToStation[index]  = (pos + mAngle) / 2;
					mState = true;
					mCaptured = index;
				}
				else
				{
					if ((mDepartAngleToStation[index] == 0)&&(mFractAngleToStation[index] == 0)&&(mDestAngleToStation[index] == 0))
					{
						mDepartAngleToStation[index] = pos;
						mDestAngleToStation[index]   = mAngle;
						mFractAngleToStation[index]  = (pos + mAngle) / 2;
						mState = true;
						mCaptured = index;
					}
				}
				return;
		}
		else
		{
			mDepartAngleToStation[index] = 0;
			mDestAngleToStation[index]   = 0;
			mFractAngleToStation[index]  = 0;
			return;
		}

	}
	else
	{
		// To Station.
		if (((pos < mEndViewAngle)&&(pos > mAngle))||
			((pos-2*PI < mEndViewAngle)&&(pos-2*PI > mAngle))||
			((pos+2*PI < mEndViewAngle)&&(pos+2*PI > mAngle)))
		{
				if (mState == false)
				{
					mDepartAngleToStation[index] = pos;
					mDestAngleToStation[index]   = mAngle;
					mFractAngleToStation[index]  = (pos + mAngle) / 2;
					mState = true;
					mCaptured = index;
				}
				else
				{
					if ((mDepartAngleToStation[index] == 0)&&(mFractAngleToStation[index] == 0)&&(mDestAngleToStation[index] == 0))
					{
						mDepartAngleToStation[index] = pos;
						mDestAngleToStation[index]   = mAngle;
						mFractAngleToStation[index]  = (pos + mAngle) / 2;
						mState = true;
						mCaptured = index;
					}
				}
				return;
		}
		else
		{
			mDepartAngleToStation[index] = 0;
			mDestAngleToStation[index]   = 0;
			mFractAngleToStation[index]  = 0;
			return;
		}

	}
}
