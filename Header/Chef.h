#pragma once

#include "Game.h"

class Chef {
private:
	int tableNumber = 0;
	int time = rnd(3) + 7;
	bool ready = false;

public:
	void setTableNumber(int input);
	int getTableNumber();
	void setTime(int input);
	int getTime();
	void setReady(bool input);
	bool getReady();
};
