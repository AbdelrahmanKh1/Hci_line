#include "FileWriter.h"



void FileWriter::writeInCurr(int trialIdx,int countInBlock,queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4],int height) {
	ofstream myfile;
	string count = to_string(countInBlock);
	string idx= to_string(trialIdx);
	_mkdir(&currPath[0u]); //just to be sure but could be deleted
	string fileName = currPath + "\\" +count + ".csv"; //filename is the trial index in block
	myfile.open(fileName);
	myfile << "trialIdx,NumberInBlock,direction,speed,timeMilSec,mouseX,mouseY,InvertedMouseY,greenX0,greenX1,greenY0,greenY1,redX0,redX1,redY0,redY1"<<"\n"; //header
	POINT mouse;
	milliseconds time;
	while (!pointsQueue.empty()) {
		time = timeQueue.front();
		mouse = pointsQueue.front();
		myfile << idx+","+count+","+orientation+","+speed+","<<time.count()<<","<<mouse.x<<","<<mouse.y<<"," << height-mouse.y << "," <<greenLine[0] << "," << greenLine[2] << "," << greenLine[1] << "," << greenLine[3] << "," << redLine[0] << "," << redLine[2] << "," << redLine[1] << "," << redLine[3]<<"\n";
		timeQueue.pop();
		pointsQueue.pop();
	}
	myfile.close();
}
//only initals
void FileWriter::write(int trialIdx, int countInBlock, queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4], int height) {
	writeInCurr(trialIdx, countInBlock, pointsQueue, timeQueue,greenLine,redLine, height);
}
//no base path
void FileWriter::write(int trialIdx, int countInBlock, int orientation, int speed, int blockNumber, queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4], int height) {
	setCurrPathDir(orientation, speed, blockNumber);
	writeInCurr(trialIdx, countInBlock, pointsQueue, timeQueue, greenLine, redLine, height);
}
//has all
void FileWriter::write(int trialIdx, int countInBlock, string basePathwID, short orientation, int speed, int blockNumber, queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4], int height) {
	setCurrPathDir(basePathwID, orientation, speed, blockNumber);
	writeInCurr(trialIdx, countInBlock, pointsQueue, timeQueue, greenLine, redLine, height);
}