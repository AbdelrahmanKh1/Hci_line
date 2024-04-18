#pragma once
#include <string>
#include <windows.h>
//#include <mmsystem.h>
//#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#include <direct.h> //_mkdir

using namespace std;
using namespace std::chrono;
//to use file writer 1st do constructor then set basepath then set current path then write in currentpath
class FileWriter
{
public:

	FileWriter() {
		currPath = basePath;
		_mkdir(&currPath[0u]);
	};
	FileWriter(string basePathwID) {
		_mkdir(&this->basePath[0u]); //can only make 1 folder or 1 layer at a time
		this->basePath = basePathwID;
		currPath = basePath;
		_mkdir(&currPath[0u]);
	};
	FileWriter(string basePathwID, int orientation,int speed,int blockNumber) {
		_mkdir(&this->basePath[0u]);

		this->basePath = basePathwID; //has user ID extra than before
		_mkdir(&this->basePath[0u]);

		this->orientation = to_string(orientation);
		currPath = basePath + "\\" + this->orientation;
		_mkdir(&currPath[0u]);

		this->speed = to_string(speed);
		currPath = basePath + "\\" + this->orientation + "\\" + this->speed;
		_mkdir(&currPath[0u]);

		this->blockNumber = to_string(blockNumber);
		currPath = basePath+"\\"+ this->orientation +"\\"+this->speed+"\\"+this->blockNumber;
		_mkdir(&currPath[0u]);
	};
	//~FileWriter();
	void setCurrPathDir(string basePathwID, int orientation, int speed, int blockNumber) {
		this->basePath = basePathwID; //has user ID extra than before
		_mkdir(&this->basePath[0u]);
		this->orientation = to_string(orientation);
		currPath = basePath + "\\" + this->orientation;
		_mkdir(&currPath[0u]);
		this->speed = to_string(speed);
		currPath = basePath + "\\" + this->orientation + "\\" + this->speed;
		_mkdir(&currPath[0u]);
		this->blockNumber = to_string(blockNumber);
		currPath = basePath + "\\" + this->orientation + "\\" + this->speed + "\\" + this->blockNumber;
		_mkdir(&currPath[0u]);
	}
	void setCurrPathDir(int orientation, int speed, int blockNumber) {
		this->orientation = to_string(orientation);
		currPath = basePath + "\\" + this->orientation;
		_mkdir(&currPath[0u]);
		this->speed = to_string(speed);
		currPath = basePath + "\\" + this->orientation + "\\" + this->speed;
		_mkdir(&currPath[0u]);
		this->blockNumber = to_string(blockNumber);
		currPath = basePath + "\\" + this->orientation + "\\" + this->speed + "\\" + this->blockNumber;
		_mkdir(&currPath[0u]);
	}
	void setBasePath(string basePathwID) {
		this->basePath = basePathwID; //has user ID extra than before
		_mkdir(&this->basePath[0u]);
		currPath = basePath;
	}
	void writeInCurr(int trialIdx, int countInBlock, queue<POINT> &pointsQueue,queue<milliseconds> &timeQueue, int greenLine[4],int redLine[4], int height);
	void write(int trialIdx, int countInBlock, queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4], int height);
	void write(int trialIdx, int countInBlock, int orientation, int speed, int blockNumber, queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4], int height);
	void write(int trialIdx, int countInBlock, string basePath, short orientation, int speed, int blockNumber, queue<POINT> &pointsQueue, queue<milliseconds> &timeQueue, int greenLine[4], int redLine[4], int height);

private:

	string basePath = "outputs"; //basepath: outputs\userID
	string orientation = "";
	string speed = "";
	string blockNumber = "";
	string currPath = "";
};

