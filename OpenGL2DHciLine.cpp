#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include <crtdbg.h>
#include <iostream>
#include <glut.h>
#include <LineManager.h>
#include <FileWriter.h>
#include <SequenceKeeper.h>
using namespace std;
using namespace std::chrono;

char* gameModeText = "HCI mouse Speed Experiment";
string userId;
char* userIdChar;
string folderPath;
queue<POINT> pointsQueue;
queue<milliseconds> timeQueue;
POINT currentPoint;

//NOTE: for mouse origin (0,0) is bottom left , and top right is max
//screen values, NOTE: origin (0,0) is top left in real screen so biggest height is down
int height = glutGet(GLUT_SCREEN_HEIGHT);
int width = glutGet(GLUT_SCREEN_WIDTH); //1280; //1920 //1280

int middleScreenY = height / 2;
int middleScreenX = width / 2;

bool mouseSet = false;

//background
float backRed = 0;
float backGreen = 0;
float backBlue = 0.5;

LineManager lineMang(0, width, height, 40); //tolerence is 40 pixels, it's the line width
FileWriter fileWriter;
// Change the experiment parameters here in the sequence keeper constructor
SequenceKeeper sequenceKeeper(4, 4, 300, 30, 30);//directions, blocksPerSpeed, directionBreakTimeInSec, blockBreakTimeInSec, TrialsInBlock) //real params
//SequenceKeeper sequenceKeeper(4, 2, 10, 5, 2); //(directions,blocksPerSpeed,directionBreakTimeInSec,blockBreakTimeInSec,TrialsInBlock) //test params
//SequenceKeeper sequenceKeeper(4, 1, 10, 5, 1); //(directions,blocksPerSpeed,directionBreakTimeInSec,blockBreakTimeInSec,TrialsInBlock) //test params

milliseconds time() {
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
	return ms;
}


void timer(int val)//timer animation function.
{
	if (--sequenceKeeper.breakTime <= 0) {
		sequenceKeeper.endBreak();
	}
	else
		glutTimerFunc(1000, timer, 0);
}
void next() {
	//controls execution flow and line manager
	if (sequenceKeeper.next()) { // experiment still on going
		lineMang.setOrientation(sequenceKeeper.orientation);
		if (sequenceKeeper.isBreak) { //if on break do timer
			glutTimerFunc(1000, timer, 0);
		}
	}
	else {// experiment ended
		exit(1);//terminate
	}
}
void mouseCollisions() {
	GetCursorPos(&currentPoint);
	timeQueue.push(time());
	pointsQueue.push(currentPoint);

	if (lineMang.redCollisionDetect(currentPoint)) {
		fileWriter.write(sequenceKeeper.trialIdx, sequenceKeeper.inBlockIdx, lineMang.orient, sequenceKeeper.speed, sequenceKeeper.blockIdx, pointsQueue, timeQueue, lineMang.greenLine, lineMang.redLine, height, userId);
		next();
		mouseSet = false;
	}
}// TODO: could display number of iterations in current block infront but could possibly cause user to be hasty and restless so better not. 
void textOutput(int x, int y, float r, float g, float b, char* string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
}
void textOutputBig(int x, int y, float r, float g, float b, char* string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void timerOutput(int passedTimer, int x, int y, char* word, float r, float g, float b)
{
	if (passedTimer <= 0) {
		textOutputBig(x, y, 1, 0, 0, "TIME COMPLETE!");
		return;
	}
	int string[40];
	int tempTime = passedTimer;
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len = 0;
	for (; tempTime > 0; len++) {
		string[len] = 48 + (tempTime % 10);
		tempTime /= 10;
	}
	int size = (int)strlen(word);
	for (int i = 0; i < size; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, word[i]);
	}
	for (int i = --len; i >= 0; i--) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
	//glFlush();
}
void speedOutput(short passedSpeed, float r, float g, float b)
{
	string s;
	glColor3f(r, g, b);
	glRasterPos2f(width / 2, height - 25);
	switch (passedSpeed) {
	case 0:s = "Speed: 1/5"; break;
	case 1:s = "Speed: 2/5"; break;
	case 2:s = "Speed: 3/5"; break;
	case 3:s = "Speed: 4/5"; break;
	case 4:s = "Speed: 5/5"; break;
	//case 5:s = "Speed: 6/6"; break;
		//case 5:s = "Speed: 5/5"; break;
		//case 6:s = "Speed: 6/6"; break;
	}
	int len = s.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}

}
void generateLines() {
	//green line
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(lineMang.greenLine[0], lineMang.greenLine[1], 0.0f);
	glVertex3f(lineMang.greenLine[0] + lineMang.tolAxis[0], lineMang.greenLine[1] + lineMang.tolAxis[1], 0.0f);
	glVertex3f(lineMang.greenLine[2] + lineMang.tolAxis[0], lineMang.greenLine[3] + lineMang.tolAxis[1], 0.0f);
	glVertex3f(lineMang.greenLine[2], lineMang.greenLine[3], 0.0f);
	glEnd();
	glPopMatrix();

	//red line
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(lineMang.redLine[0], lineMang.redLine[1], 0.0f);
	glVertex3f(lineMang.redLine[0] + lineMang.tolAxis[0], lineMang.redLine[1] + lineMang.tolAxis[1], 0.0f);
	glVertex3f(lineMang.redLine[2] + lineMang.tolAxis[0], lineMang.redLine[3] + lineMang.tolAxis[1], 0.0f);
	glVertex3f(lineMang.redLine[2], lineMang.redLine[3], 0.0f);
	glEnd();
	glPopMatrix();
}

void Display() {

	glClearColor(backRed, backGreen, backBlue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!sequenceKeeper.isBreak) {
		//show speed
		speedOutput(sequenceKeeper.speed, 1, 1, 1);
		//drawing lines
		generateLines();
		//setting mouse to before the line
		if (!mouseSet) {
			glutWarpPointer(lineMang.initMousePos[0], lineMang.initMousePos[1]);
			mouseSet = true;
		}
		//collision detection
		mouseCollisions();
	}
	else timerOutput(sequenceKeeper.breakTime, middleScreenX, middleScreenY, "Break Time Left: ", 1, 1, 1);

	glFlush();

}
void key(unsigned char k, int x, int y)//keyboard function, takes 3 parameters
// k is the key pressed from the keyboard
// x and y are mouse postion when the key was pressed.
{
	switch (k) {
	case ('q'): exit(1); break; //exit experiment
	case('s'): { sequenceKeeper.breakTime = 0; }; break; //skip break and continue experiment
	case('p'): {  //print to cmd
		cout << "Mouse X:" << currentPoint.x; //mouseX;
		cout << "MouseY:" << currentPoint.y;//mouseY;

		cout << "\b Green X:" << lineMang.greenLine[0] << " Y:" << lineMang.greenLine[1];
		cout << "\b Red X:" << lineMang.redLine[0] << " Y:" << lineMang.redLine[1];
		cout << endl;

	}; break;

	}

	glutPostRedisplay();//redisplay to update the screen with the changes
}
void Anim() {
	glutPostRedisplay();
}
void main(int argc, char** argr) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();

	lineMang.setOrientation(sequenceKeeper.orientation);
	cout << "Please input the UserID first \n";
	getline(cin, userId);
	cout << "Current user: " << userId;
	userIdChar = &userId[0u];
	fileWriter.setBasePath(string("outputs\\" + userId));

	glutInit(&argc, argr);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Line Test");
	glutDisplayFunc(Display);
	glutKeyboardFunc(key);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutIdleFunc(Anim);
	glutFullScreen();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, width, 0.0, height);
	glutMainLoop();//don't call any method after this line as it will not be reached.
}
