#include <stdio.h>
#include "LineManager.h"
//#include <iostream>

using namespace std;

void LineManager::initLineLocations() {
	int bufferDist = 150; //distance between mouse and line when teleporting mouse
	switch (orient)
	{
	case 0: { //horizontal L->R
		greenLine[0] = width / 3; //x0
		greenLine[1] = (height / 2) - 220; //y0
		greenLine[2] = width / 3; //x1
		greenLine[3] = (height / 2) + 220; //y1

		redLine[0] = width - (width / 3);
		redLine[1] = (height / 2) - 220;
		redLine[2] = width - (width / 3);
		redLine[3] = (height / 2) + 220;

		tolAxis[0] = tol;
		tolAxis[1] = 0;

		initMousePos[1] = height - (((greenLine[3] - greenLine[1]) / 2) + greenLine[1]); //subtract height cause down is increasing
		initMousePos[0] = greenLine[0] - bufferDist;
	}; break;
	case 1: { //horizontal R->L
		redLine[0] = width / 3;
		redLine[1] = (height / 2) - 220;
		redLine[2] = width / 3;
		redLine[3] = (height / 2) + 220;

		greenLine[0] = width - (width / 3);
		greenLine[1] = (height / 2) - 220;
		greenLine[2] = width - (width / 3);
		greenLine[3] = (height / 2) + 220;

		tolAxis[0] = tol;
		tolAxis[1] = 0;

		initMousePos[1] = height - (((greenLine[3] - greenLine[1]) / 2) + greenLine[1]); //subtract height cause down is increasing
		initMousePos[0] = greenLine[0] + bufferDist;
	}; break;
	case 2: { //vertical up->down
		greenLine[0] = width / 3; //x0
		greenLine[1] = (height / 2) - 220; //y0
		greenLine[2] = width - (width / 3); //x1
		greenLine[3] = (height / 2) - 220; //y1

		redLine[0] = width / 3; //x0
		redLine[1] = (height / 2) + 220; //y0
		redLine[2] = width - (width / 3); //x1
		redLine[3] = (height / 2) + 220; //y1

		tolAxis[0] = 0;
		tolAxis[1] = tol;

		initMousePos[1] = height - ( greenLine[1])+ bufferDist; //subtract height cause down is increasing
		initMousePos[0] =((greenLine[2]-greenLine[0])/2)+ greenLine[0];
	}; break;
	case 3: { //vertical down->up
		redLine[0] = width / 3; //x0
		redLine[1] = (height / 2) - 220; //y0
		redLine[2] = width - (width / 3); //x1
		redLine[3] = (height / 2) - 220; //y1

		greenLine[0] = width / 3; //x0
		greenLine[1] = (height / 2) + 220; //y0
		greenLine[2] = width - (width / 3); //x1
		greenLine[3] = (height / 2) + 220; //y1

		tolAxis[0] = 0;
		tolAxis[1] = tol;

		initMousePos[1] = height - (greenLine[1]) - bufferDist; //subtract height cause down is increasing
		initMousePos[0] = ((greenLine[2] - greenLine[0]) / 2) + greenLine[0];
	}; break;
	case 4: { //diagonal L->R
		greenLine[0] = width / 3; //x0
		greenLine[1] = (height / 2) - 220-50; //y0
		greenLine[2] = width / 3; //x1
		greenLine[3] = (height / 2) + 220-50; //y1

		redLine[0] = width - (width / 3);
		redLine[1] = (height / 2) - 220+50;
		redLine[2] = width - (width / 3);
		redLine[3] = (height / 2) + 220+50;

		tolAxis[0] = tol;
		tolAxis[1] = 0;

		initMousePos[1] = height - (((greenLine[3] - greenLine[1]) / 2) + greenLine[1]); //subtract height cause down is increasing
		initMousePos[0] = greenLine[0] - bufferDist;
	}; break;
		/* // diagonal disabled currently only 4 directions
	case 5: { //diagonal R->L
		redLine[0] = width / 3; //x0
		redLine[1] = (height / 2) - 220 - 50; //y0
		redLine[2] = width / 3; //x1
		redLine[3] = (height / 2) + 220 - 50; //y1

		greenLine[0] = width - (width / 3);
		greenLine[1] = (height / 2) - 220 + 50;
		greenLine[2] = width - (width / 3);
		greenLine[3] = (height / 2) + 220 + 50;

		tolAxis[0] = tol;
		tolAxis[1] = 0;

		initMousePos[1] = height - (((greenLine[3] - greenLine[1]) / 2) + greenLine[1]); //subtract height cause down is increasing
		initMousePos[0] = greenLine[0] + bufferDist;
	}; break;*/
//	default:
//		break;
	}

}

bool LineManager::redCollisionDetect_old(POINT mouse) {
	switch (orient)
	{
	case 0: //horizontal L->R
	case 1: { //horizontal R->L
		if (redLine[0] + tol >= mouse.x && redLine[0] - 3 <= mouse.x) {
			//isCollidedRed = true;
			return true;
		}
		else {
			//isCollidedRed = false;
			return false;
		};
	}; break;
	case 2: //vertical up->down

	case 3: { //vertical down->up
		if (redLine[1] + tol >= height - mouse.y && redLine[1] - 3 <= height - mouse.y) {
			//isCollidedRed = true;
			return true;
		}
		else {
			//isCollidedRed = false;
			return false;
		}
	}; break;
	}
}
bool LineManager::redCollisionDetect(POINT mouse) {
	switch (orient)
	{
	case 0: { //horizontal L->R
		if (redLine[0] <= mouse.x) {
			return true;
		}
		return false; } break;
	case 1: { //horizontal R->L
		if (redLine[0] >= mouse.x) {
			return true;
		}
		else {
			return false;
		};
	}; break;
	case 2: { //vertical up->down
		if (redLine[1] <= height - mouse.y) { //openGL origin is down, mouse point origin is up
			return true;
		}
		else {
			return false;
		}
	}; break;
	case 3: { //vertical down->up
		if (redLine[1]>= height - mouse.y) {
			return true;
		}
		else {
			return false;
		}
	}; break;
}
}
bool LineManager::greenCollisionDetect_old(POINT mouse) {
	switch (orient)
	{
	case 0: //horizontal L->R
	case 1: { //horizontal R->L
		if (greenLine[0] + tol >= mouse.x && greenLine[0] - 3 <= mouse.x) {
			//isCollidedGreen = true;
			return true;
		}
		else {
			//isCollidedGreen = false;
			return false;
		};

	}
	case 2: //vertical up->down

	case 3: { //vertical down->up
		if (greenLine[1] + tol >= height - mouse.y && greenLine[1] - 3 <= height - mouse.y) {
			//isCollidedGreen = true;
			return true;
		}
		else {
			//isCollidedGreen = false;
			return false;
		};
	}; break;
	}
}