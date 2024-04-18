#pragma once
#include <windows.h>

class LineManager
{
public:
	int greenLine[4]; //[x0,y0,x1,y1]
	int redLine[4]; //[x0,y0,x1,y1]
	short orient=0;
	int width=0;
	int height=0;
	int tol=0;
	int tolAxis[2] = { 0,0 }; // [x_tolerance, y_tolerance]
	int initMousePos[2];
	LineManager(short orientation,int screenWidth,int screenHeight,int tolerance){
		orient = orientation;
		tol = tolerance;
		width = screenWidth;
		height = screenHeight;
		initLineLocations();
	}
	LineManager(int screenWidth, int screenHeight) {
		width = screenWidth;
		height = screenHeight;
	}

	void setOrientation(short orientation,int tolerance) {
		orient = orientation;
		tol = tolerance;
		initLineLocations();
	}
	void setOrientation(short orientation) {
		orient = orientation;
		initLineLocations();
	}
	void setParameters(short orientation, int screenWidth, int screenHeight, int tolerance) {
		orient = orientation;
		tol = tolerance;
		width = screenWidth;
		height = screenHeight;
		initLineLocations();
	}
	bool redCollisionDetect(POINT mouse); //general detection
	bool redCollisionDetect_old(POINT mouse);//very specific detection
	bool greenCollisionDetect_old(POINT mouse); //very specific detection

private:
	void initLineLocations();
};

