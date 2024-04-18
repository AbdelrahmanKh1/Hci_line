#include "SequenceKeeper.h"

bool SequenceKeeper::next() {
	trialIdx++;
	if (++inBlockIdx >= trialNPerBlock) { //if finished current block; ex:30 for slow,horiz
		isBreak = true;
		inBlockIdx = 0;
		breakTime = blockBreakTime; //can be changed below if direction ended
		if (++blockIdx >= maxBlocksPerSpeed) { // if finished number of blocks for speed in direction;ex 3 slow blocks in horiz
			blockIdx = 0;
			if (++orientBlockIdx >= maxOrientBlocks) { //if blocks for direction finished then direction ended; ex 3 blocks for each speed in direction
				breakTime = orientBreakTime; //direction ended
				orientBlockIdx = 0;
				sequenceQueue.pop();
				if (sequenceQueue.empty()) { //if no more directions left then experiment ended (return false)
					return false;
				}
				orientation = sequenceQueue.front().orientation; //change direction
				speed = sequenceQueue.front().speed.front(); //change speed
			}
			else { //if direction not finished then just change speed
				sequenceQueue.front().speed.pop(); //then get new speed
				speed = sequenceQueue.front().speed.front();
			}
		}		
	}	//no need for else since things will stay same with direction and speed
	return true;
}
void SequenceKeeper::endBreak() {
	isBreak = false;
}
