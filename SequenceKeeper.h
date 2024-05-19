#pragma once
#include <SequenceObject.h>
class SequenceKeeper
{
	// generates the random order of directions, random order of speeds and maintanes the next item to be run ( just use .next and call endBreak when breaks finish)
public:
	bool isBreak = false;
	short orientation;
	short speed;
	int breakTime; //either this or use function to send others
	int trialIdx = 0; //current trial number
	short inBlockIdx = 0; //trial index in current block
	short blockIdx = 0; //current block number

	SequenceKeeper(short maxOrientations, short maxBlocksPerSpeed, int orientBreakTime, short blockBreakTime, short trialNPerBlock) {
		this->maxOrientations = maxOrientations;
		this->maxBlocksPerSpeed = maxBlocksPerSpeed;
		this->orientBreakTime = orientBreakTime;
		this->blockBreakTime = blockBreakTime;
		this->trialNPerBlock = trialNPerBlock;
		maxOrientBlocks = 4; //3 speeds for now, TODO: change to N speeds
		/*
		std::vector<short> directionArr(maxOrientations); //temp array containing orientation order
		for (short i = 0; i<maxOrientations; i++)
			directionArr.push_back(i); //0 1 2 3 orientations

		std::srand(unsigned(std::time(0)));
		std::random_shuffle(directionArr.begin(), directionArr.end()); //shuffel orientation vector
		for (std::vector<short>::iterator it = directionArr.begin(); it != directionArr.end(); it++)
			sequenceQueue.push(SequenceObject(*it)); //create new sequence object and push to queue , sequence object creates random speed order
		*/
		srand(time(0));  // initialize seed "randomly" for true random
		short orientArr[] = { 0,1,2,3};
		for (short i = 0; i < 4; i++) { //shuffel speed array
			short r = rand() % 4;  // generate a random position
			short temp = orientArr[i];
			orientArr[i] = orientArr[r];
			orientArr[r] = temp;
		}
		for (short i = 0; i < 4; i++) {
			sequenceQueue.push(SequenceObject(orientArr[i])); //create new sequence object and push to queue , sequence object creates random speed order
		}
		orientation = sequenceQueue.front().orientation;
		speed = sequenceQueue.front().speed.front();

	}
	//~SequenceKeeper();
	bool next(); //if true there is still next, if false then experiment ended
	void endBreak(); //call after a break is ended

private:
	std::queue<SequenceObject> sequenceQueue;
	short maxOrientations; //0->3 //max number of orientations or directions
	short maxBlocksPerSpeed; //number of blocks per speed
	int maxOrientBlocks; //number of blocks needed for direction
	int orientBlockIdx = 0; //index for direction in block
	int orientBreakTime; //break between directions
	short blockBreakTime; //max 255 seconds cause short
	short trialNPerBlock;// number of trials for each block
};

