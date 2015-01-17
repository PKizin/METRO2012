// METRO2012.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Window.h"
#include "C:/glut/glut.h"

std::vector<Sector>	 Sectors;
std::vector<Train>	 Trains;
std::vector<Station> Stations;

int	sectors	 = 4;
int	trains   = 4;
int stations = 2;
int r		 = 54;
int R		 = 60;
double wait  = 2;
double speed = 0.2;
double accel = 0.2;
double eps   = 0.00001;

int main(int argc, char** argv)
{
//--------------------------------------------------------------------------
	// Circles.
		// Inside circle.
	for (int i = 0; i < sectors; ++i)
	{
		Sector S( r, i*2*PI/sectors, (i+1)*2*PI/sectors, (2*i+1)*PI/sectors, 0, 0, 0, 4, speed, (Col)(i%2), Around );
		Sectors.push_back(S);
	}
		// Outside circle.
	for (int i = 0; i < sectors; ++i)
	{
		Sector S( R, i*2*PI/sectors, (i+1)*2*PI/sectors, (2*i+1)*PI/sectors, 0, 0, 0, 4, speed, (Col)(i%2), Against );
		Sectors.push_back(S);
	}

//--------------------------------------------------------------------------
	// Trains.
		// Inside circle.
	for (int i = 0; i < trains; ++i)
	{
		Train T( r, Sectors[i].CenterAngle(), speed, accel, 0, 0, 0, 0, Around, Moved );
		Trains.push_back(T);
	}
		// Outside circle.
	for (int i = 0; i < trains; ++i)
	{
		Train T( R, Sectors[i].CenterAngle(), speed, accel, 0, 0, 0, 0, Against, Moved );
		Trains.push_back(T);
	}

//--------------------------------------------------------------------------
	// Stations.
	/*std::vector<double> depart;
	std::vector<double> fract;
	std::vector<double> dest;
	for (int i = 0; i < stations; ++i)
	{
		depart.push_back(0);
		fract.push_back(0);
		dest.push_back(0);
	}*/
	for (int i = 0; i < stations; ++i)
	{
		Station St( (r+R)/2,  
					i*2*PI/stations+PI/stations,	
					i*2*PI/stations-PI/stations/2+PI/stations,  
					i*2*PI/stations+PI/stations/2+PI/stations );
		Stations.push_back(St);
	}

//--------------------------------------------------------------------------
	Window W(100,100,800,800);
	W.Init(argc,argv);
	W.Start();

	getchar();
	return 0;
}

