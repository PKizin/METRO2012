// Window.h

#pragma once

#include "stdafx.h"
#include "Sector.h"
#include "Train.h"
#include "Station.h"
#include "C:/glut/glut.h"
#include <vector>
#include <iostream>

class Window
{
	friend void draw();

private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;

public:
	Window();
	Window(int x, int y, int width, int height);
	~Window();
	void Init(int argc, char** argv);
	void Start();
};