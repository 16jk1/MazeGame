/* items.h
*
* Created on: Oct 23, 2018
* Author: harrychan
*/
/*
#ifndef ITEMS_H_
#define ITEMS_H_
#include <time.h>

class Item {
protected:
	int location[1];
	int scarcity;
	char color[10];
public:
	void ability();
	int getLocation();

};

// Think about implementation of really rare boots kind of like fornite
class Boots: public Item {
public:
	void ability() {
// call on the player object and change the speed of
	}
// srand (time(NULL));
	int location(int gameDimentionX, int gameDimentionY) {
// Unless both the dimentions are the same
		for (int i = 0; i < scarcity; i++) {
			location[0] = rand() % gameDimentionX;
			location[1] = rand() % gameDimentionY;
			return location;
		}
	}
};


class Torch: public Item {
public:
	void ability() {
// call on the map object function and expand by a multiplier
	}
	int location(int gameDimentionX, int gameDimentionY) {
// Unless both the dimentions are the same
		for (int i = 0; i < scarcity; i++) {
			location[0] = rand() % gameDimentionX;
			location[1] = rand() % gameDimentionY;
			return location;
		}
	}
};


#endif /* ITEMS_H_ */

