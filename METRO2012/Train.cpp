// Train.cpp

#include "stdafx.h"
#include "Train.h"

extern double eps;
extern double wait;

Train::Train() : mRadius(0), 
				 mAngle(0), 
				 mSpeed(0), 
				 mAcceleration(0),
				 mTimer1(0), 
				 mTimer2(0), 
				 mTimer3(0),
				 mTimer4(0),
				 mState(Stopped) {}

Train::Train( double radius, 
			  double angle, 
			  double speed, 
			  double acceleration,
			  double timer1,
			  double timer2,
			  double timer3,
			  double timer4,
			  Dir direct, 
			  St state) : mRadius(radius),
						  mAngle(angle),
						  mSpeed(speed),
						  mAcceleration(acceleration),
						  mTimer1(timer1),
						  mTimer2(timer2),
						  mTimer3(timer3),
						  mTimer4(timer4),
						  mDirection(direct),
						  mState(state) {}

Train::~Train() {}

double Train::Radius()		 {return mRadius;}
double Train::Angle()		 {return mAngle;}
double Train::Speed()		 {return mSpeed;}
double Train::Acceleration() {return mAcceleration;}
double Train::Timer1()		 {return mTimer1;}
double Train::Timer2()		 {return mTimer2;}
double Train::Timer3()		 {return mTimer3;}
double Train::Timer4()		 {return mTimer4;}
Dir Train::Direction()		 {return mDirection;}
St Train::State()			 {return mState;}

//void Train::ChangeAngle(double angle)	{mAngle = angle;}
//void Train::ChangeSpeed(double speed)	{mSpeed = speed;}
//void Train::ChangeTimer1(double timer1) {mTimer1 = timer1;}
//void Train::ChangeTimer2(double timer2) {mTimer2 = timer2;}
//void Train::ChangeState(St state)		{mState = state;}

void Train::Move()
{
	if (mDirection == Around) 
		mAngle += mSpeed*PI/180;
	else
		mAngle -= mSpeed*PI/180;
}

void Train::Stop() 
{
	mTimer2 += mSpeed / 5;
}

//--------------------------------------------------------------------------------------------------------------------
void Train::AccelerateToCenter() 
{
	mTimer1 += mSpeed / 5;
	if (mDirection == Around) 
		mAngle += (1+mAcceleration*mTimer1)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
	else
		mAngle -= (1+mAcceleration*mTimer1)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
}

void Train::DecelerateToCenter() 
{
	mTimer1 -= mSpeed / 5;
	if (mDirection == Around) 	
		mAngle += (1+mAcceleration*mTimer1)*mSpeed*PI/180;// - mAcceleration*mTimer1*PI/180;// - mAcceleration/2;
	else
		mAngle -= (1+mAcceleration*mTimer1)*mSpeed*PI/180;// - mAcceleration*mTimer1*PI/180;// - mAcceleration/2;
}

//--------------------------------------------------------------------------------------------------------------------
void Train::AccelerateToStation() 
{
	mTimer3 += mSpeed / 5;
	if (mDirection == Around) 
		mAngle += (1+mAcceleration*mTimer3)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
	else
		mAngle -= (1+mAcceleration*mTimer3)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
}

void Train::DecelerateToStation() 
{
	//mTimer3 -= 1.3*mSpeed / 5;
	if (mDirection == Around) 	
	{
		mTimer3 -= 1.5*mSpeed / 5;
		mAngle += (1+mAcceleration*mTimer3)*mSpeed*PI/180;// - mAcceleration*mTimer1*PI/180;// - mAcceleration/2;
	}
	else
	{
		mTimer3 -= 1.5*mSpeed / 5;
		mAngle -= (1+mAcceleration*mTimer3)*mSpeed*PI/180;// - mAcceleration*mTimer1*PI/180;// - mAcceleration/2;
	}
}

//--------------------------------------------------------------------------------------------------------------------
void Train::AccelerateFromStation() 
{
	mTimer1 += 1.5*mSpeed / 5;
	if (mDirection == Around) 
		mAngle += (1+mAcceleration*mTimer1)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
	else
		mAngle -= (1+mAcceleration*mTimer1)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
}

void Train::DecelerateFromStation() 
{
	//mTimer1 -= 1.5*mSpeed / 5;
	if (mDirection == Around) 
	{
		mTimer1 -= 1.5*mSpeed / 5;
		mAngle += (1+mAcceleration*mTimer1)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
	}
	else
	{
		mTimer1 -= 1.5*mSpeed / 5;
		mAngle -= (1+mAcceleration*mTimer1)*mSpeed*PI/180;// + mAcceleration*mTimer1*PI/180;// + mAcceleration/2;
	}
}

//--------------------------------------------------------------------------------------------------------------------

void Train::CheckAngle(double fi1, double fi2)
{
	/*if ((fi1 >= 2*PI)&&(fi2 >= 2*PI))
		mAngle -= 2*PI;
	if ((fi1 < 0)&&(fi2 < 0))
		mAngle += 2*PI;*/
	if (mAngle >= 2*PI) mAngle -= 2*PI;
	if (mAngle < 0) mAngle += 2*PI;
}

void Train::CheckTimer2()
{
	if (mTimer2 >= wait)
	{
		mTimer2 = 0;
		mState  = AcceleratedFromStation;
	}
}

void Train::CheckStopping(double pos, double eps)
{
	if (mState == AcceleratedFromStation) return;
	if (mState == DeceleratedFromStation) return;

	if (abs(mAngle - pos) <= eps)
	{
		if (mTimer1 == 0) 
			mTimer1 = mTimer3;
		mTimer3 = 0;
		mState = Stopped;
	}
}

void Train::CheckSectorCenter(double fi1, double fi2, double fi3)
{
	if (mState == AcceleratedToStation) return;
	if (mState == DeceleratedToStation) return;
	if (mState == AcceleratedFromStation) return;
	if (mState == DeceleratedFromStation) return;
	if (mState == Stopped) return;
	
	if ((fi1 == 0)&&(fi2 == 0)&&(fi3 == 0)) 
	{
		mState = Moved;
		mTimer1 = 0;
		return;
	}

	if (mDirection == Around)
	{
		if (mAngle > fi2) mState = DeceleratedToCenter;
		if (mAngle < fi2) mState = AcceleratedToCenter;
	}
	else
	{
		if (mAngle > fi2) mState = AcceleratedToCenter;
		if (mAngle < fi2) mState = DeceleratedToCenter;
	}
}

void Train::CheckArrive(double fi1, double fi2, double fi3, int tr1, int tr2)
{
	if (mState == Stopped) return;
	if (mState == AcceleratedFromStation) return;
	if (mState == DeceleratedFromStation) return;

	if ((abs(fi1) < eps)&&(abs(fi2) < eps)&&(abs(fi3) < eps)) 
	{
		//mState = Moved;
		//mTimer3 = 0;
		return;
	}

	if (tr1 == tr2)		// if current train is equal of "captured train" of the station.
	{
		if (mDirection == Around)
		{
			if (mAngle > fi2) mState = DeceleratedToStation;
			if (mAngle < fi2) mState = AcceleratedToStation;
		}
		else
		{
			if (mAngle > fi2) mState = AcceleratedToStation;
			if (mAngle < fi2) mState = DeceleratedToStation;
		}
	}
	else
	{
		if (mTimer3 < 1)
			mTimer3 = -2;
		mState = DeceleratedToStation;
	}
	mTimer1 = 0;
}

void Train::CheckDeparture(double fi1, double fi2, double fi3)
{
	if (mState == Stopped) return;
	if (mState == AcceleratedToStation) return;
	if (mState == DeceleratedToStation) return;
	if (mState == AcceleratedToCenter) return;
	if (mState == DeceleratedToCenter) return;

	if ((abs(fi1) < eps)&&(abs(fi2) < eps)&&(abs(fi3) < eps)) 
	{
		mState = Moved;
		return;
	}

	if (mDirection == Around)
	{
		if (mAngle > fi2) mState = DeceleratedFromStation;
		if (mAngle < fi2) mState = AcceleratedFromStation;
	}
	else
	{
		if (mAngle > fi2) mState = AcceleratedFromStation;
		if (mAngle < fi2) mState = DeceleratedFromStation;
	}
}