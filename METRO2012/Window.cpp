// Window.cpp

#include "stdafx.h"
#include "Window.h"
#include <math.h>

extern std::vector<Sector>	Sectors;
extern std::vector<Train>   Trains;
extern std::vector<Station> Stations;
extern double eps;

// Time.
double time = 0;

Window::Window() : mX(0), 
				   mY(0),
				   mWidth(100),
				   mHeight(100) {}

Window::Window(int x, int y, int width, int height) : mX(x),
													  mY(y),
													  mWidth(width),
													  mHeight(height) {}

Window::~Window() {}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//-------------------------------------------------------------------------------------------------------------
	// Train.
	for (unsigned int i=0; i<Trains.size(); ++i)
	{
		Trains[i].CheckAngle( Sectors[i].StartAngle(), Sectors[i].EndAngle() );
		
		//if (i == 0)
		//{
		glPointSize(10);
		glColor3f(0,0,0);
		glBegin(GL_POINTS);
			glVertex2f( Trains[i].Radius()*cos(Trains[i].Angle()), 
				        Trains[i].Radius()*sin(Trains[i].Angle())  );
		glEnd();
		//}
		
		// Debug.
		/*if (i == 0)
		{
			//if (Trains[i].State() == AcceleratedToCenter) std::cout << "ATC ";
			//if (Trains[i].State() == DeceleratedToCenter) std::cout << "DTC ";
			//if (Trains[i].State() == AcceleratedToStation) std::cout << "ATS ";
			//if (Trains[i].State() == DeceleratedToStation) std::cout << "DTS ";
			//if (Trains[i].State() == AcceleratedFromStation) std::cout << "AFS ";
			//if (Trains[i].State() == DeceleratedFromStation) std::cout << "DFS ";
			//if (Trains[i].State() == Moved) std::cout << "M ";
			//if (Trains[i].State() == Stopped) std::cout << "S ";

			//std::cout << Trains[i].Timer1() << " ";

			//std::cout << Trains[i].Angle() << " ";

			//std::cout << Sectors[i].CenterAngle() << " ";

			//std::cout << Sectors[i].DepartAngle() << " ";
			//std::cout << Sectors[i].FractAngle() << " ";
			//std::cout << Sectors[i].DestAngle() << " ";

			//std::cout << Stations[0].StartViewAngle() << " ";
			//std::cout << Stations[0].Angle() << " ";

			//std::cout << Stations[0].DepartAngleToStation(i) << " ";
			//std::cout << Stations[0].FractAngleToStation(i) << " ";
			//std::cout << Stations[0].DestAngleToStation(i) << " ";

			//std::cout << Stations[1].DepartAngleToStation(i) << " ";
			//std::cout << Stations[1].FractAngleToStation(i) << " ";
			//std::cout << Stations[1].DestAngleToStation(i) << " ";

			//std::cout << Stations[2].DepartAngleToStation(i) << " ";
			//std::cout << Stations[2].FractAngleToStation(i) << " ";
			//std::cout << Stations[2].DestAngleToStation(i) << " ";

			//std::cout << Stations[0].DepartAngleFromStation(i) << " ";
			//std::cout << Stations[0].FractAngleFromStation(i) << " ";
			//std::cout << Stations[0].DestAngleFromStation(i) << " ";

			//std::cout << Stations[1].DepartAngleFromStation(i) << " ";
			//std::cout << Stations[1].FractAngleFromStation(i) << " ";
			//std::cout << Stations[1].DestAngleFromStation(i) << " ";

			//std::cout << Trains[i].Timer1() << " ";
			//std::cout << Trains[i].Timer2() << " ";
			//std::cout << Trains[i].Timer3() << " ";
			//std::cout << std::endl;
		}*/

		// Synchronization with the center point of a sector.
		Trains[i].CheckSectorCenter( Sectors[i].DepartAngle(), Sectors[i].FractAngle(), Sectors[i].DestAngle() );

		//if ( i == 4)
		//{
		for (unsigned int j=0; j<Stations.size(); ++j)
		{
			// Arriving to the station.
			Stations[j].CheckTrainPosition( i, Trains[i].Angle(), Trains[i].Direction(), 4*Trains[i].Speed()*PI/180 );
			Trains[i].CheckArrive( Stations[j].DepartAngleToStation(i), 
								   Stations[j].FractAngleToStation(i), 
								   Stations[j].DestAngleToStation(i),
								   i,
								   Stations[j].Captured() );
			if ((Stations[j].DepartAngleToStation(i) >= eps)||
				(Stations[j].FractAngleToStation(i) >= eps)||
				(Stations[j].DestAngleToStation(i) >= eps)) 
					break;

			// Departure from the station.
			Trains[i].CheckDeparture( Sectors[i].DepartAngle(), 
									  0.5*Sectors[i].DepartAngle()+0.5*Sectors[i].DestAngle(), 
									  Sectors[i].DestAngle() );
		}
		//}

		// Stopping on the station.
		for (unsigned int j=0; j<Stations.size(); ++j)
			Trains[i].CheckStopping( Stations[j].Angle() , 1*Sectors[i].Speed()*PI/180 );
		Trains[i].CheckTimer2();

		switch (Trains[i].State())
		{
			case AcceleratedToCenter:
			{
				Trains[i].AccelerateToCenter();
				break;
			}

			case DeceleratedToCenter:
			{
				Trains[i].DecelerateToCenter();
				break;
			}

			case Moved:
			{
				Trains[i].Move();
				break;
			}

			case Stopped:
			{
				Trains[i].Stop();
				break;
			}

			case AcceleratedToStation:
			{
				Trains[i].AccelerateToStation();
				break;
			}

			case DeceleratedToStation:
			{
				Trains[i].DecelerateToStation();
				break;
			}

			case AcceleratedFromStation:
			{
				Trains[i].AccelerateFromStation();
				break;
			}

			case DeceleratedFromStation:
			{
				Trains[i].DecelerateFromStation();
				break;
			}
		}
	}

//-------------------------------------------------------------------------------------------------------------
	// Sectors.
	for (unsigned int i=0; i<Sectors.size(); ++i)
	{
		Sectors[i].CheckAngle();
		Sectors[i].CheckTrainPosition( Trains[i].Angle(), 4*Sectors[i].Speed()*PI/180, Trains[i].State() );

		if (Sectors[i].Color() == 0) 
			glColor3f(1, 0, 0);
		else			   
			glColor3f(0, 0, 1);
		glLineWidth(Sectors[i].Thickness());
		glBegin(GL_LINE_STRIP);
			for (int j=0; j<=ceil((Sectors[i].EndAngle()-Sectors[i].StartAngle())*180/PI); ++j)
			{
				glVertex2f( Sectors[i].Radius()*cos(Sectors[i].StartAngle()+
								j*(Sectors[i].EndAngle()-Sectors[i].StartAngle())/
									ceil((Sectors[i].EndAngle()-Sectors[i].StartAngle())*180/PI)),
							Sectors[i].Radius()*sin(Sectors[i].StartAngle()+
								j*(Sectors[i].EndAngle()-Sectors[i].StartAngle())/
									ceil((Sectors[i].EndAngle()-Sectors[i].StartAngle())*180/PI)) );
			}
		glEnd();
		glPointSize(6);
		glBegin(GL_POINTS);
			glVertex2f( Sectors[i].Radius()*cos(Sectors[i].CenterAngle()), 
						Sectors[i].Radius()*sin(Sectors[i].CenterAngle())  );
		glEnd();

		Sectors[i].Move();
	}

	// Circles instead of sectors.
	/*glColor3f(0, 1, 0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
		for (int j=0; j<360; ++j)
		{
			glVertex2f( Sectors[0].Radius()*cos(j*PI/180), Sectors[0].Radius()*sin(j*PI/180) );
		}
	glEnd();
	glBegin(GL_LINE_STRIP);
		for (int j=0; j<360; ++j)
		{
			glVertex2f( Sectors[Sectors.size()-1].Radius()*cos(j*PI/180), Sectors[Sectors.size()-1].Radius()*sin(j*PI/180) );
		}
	glEnd();*/

//-------------------------------------------------------------------------------------------------------------
	// Stations.
	for (unsigned int i=0; i<Stations.size(); ++i)
	{
		//if (i==0) 
		//	std::cout << Stations[i].State() << std::endl;
		Stations[i].CheckAngle();
		//for (int j = 0; j<Trains.size(); ++j)
		//	Stations[i].CheckTrainPosition( Trains[j].Angle(), Trains[j].Direction() );

		glPointSize(15);
		glColor3f(0,1,0);
		glBegin(GL_POINTS);
		glVertex2f(	Stations[i].Radius()*cos(Stations[i].Angle()), 
					Stations[i].Radius()*sin(Stations[i].Angle())  );
		glEnd();

		glLineWidth(20);
		glColor3f(1,1,0);
		glBegin(GL_POLYGON);
			for (int j=0; j<=ceil((Stations[i].EndViewAngle()-Stations[i].StartViewAngle())*180/PI); ++j)
				{
					glVertex2f( (Stations[i].Radius()-10)*cos(Stations[i].StartViewAngle()+
									j*(Stations[i].EndViewAngle()-Stations[i].StartViewAngle())/
										ceil((Stations[i].EndViewAngle()-Stations[i].StartViewAngle())*180/PI)),
								(Stations[i].Radius()-10)*sin(Stations[i].StartViewAngle()+
									j*(Stations[i].EndViewAngle()-Stations[i].StartViewAngle())/
										ceil((Stations[i].EndViewAngle()-Stations[i].StartViewAngle())*180/PI)) );
				}
			for (int j=ceil((Stations[i].EndViewAngle()-Stations[i].StartViewAngle())*180/PI); j>=0; --j)
				{
					glVertex2f( (Stations[i].Radius()+10)*cos(Stations[i].StartViewAngle()+
									j*(Stations[i].EndViewAngle()-Stations[i].StartViewAngle())/
										ceil((Stations[i].EndViewAngle()-Stations[i].StartViewAngle())*180/PI)),
								(Stations[i].Radius()+10)*sin(Stations[i].StartViewAngle()+
									j*(Stations[i].EndViewAngle()-Stations[i].StartViewAngle())/
										ceil((Stations[i].EndViewAngle()-Stations[i].StartViewAngle())*180/PI)) );
				}
		glEnd();
	}

	time += 0.001;
	//std::cout << time << std::endl;

	glFlush();  
	glutSwapBuffers();
	glutPostRedisplay();
}

void Window::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(mWidth, mHeight);
	glutInitWindowPosition(mX, mY);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	(void)glutCreateWindow("METRO 2012");
	glutDisplayFunc(draw);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-100,100,-100,100,-1,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
}

void Window::Start()
{
	glutMainLoop();
}