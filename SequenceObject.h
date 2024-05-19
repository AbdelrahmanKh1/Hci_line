#pragma once
#include <queue>
#include <cstdlib>   // for srand and rand
#include <ctime>     // for time
class SequenceObject
{
public:
	short orientation; //0->3
	std::queue<short> speed;
	SequenceObject(short orientation) {

		this->orientation = orientation;
		srand(time(0));  // initialize seed "randomly" for true random
		short speedArr[] = { 0,1,2,3 };

		for (short i = 0; i < 4; i++) { //shuffel speed array
			short r = rand() % 4;  // generate a random position
			short temp = speedArr[i];
			speedArr[i] = speedArr[r];
			speedArr[r] = temp;
		}

		for (short i = 0; i < 4; i++) {
			speed.push(speedArr[i]);
		}

	};
	//~SequenceObject(); //to make compiler create default destructor
};

