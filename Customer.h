#pragma once
#include <queue>

#include "Game.h"

class Customer {
private:
	int size = 0;
	int time = rnd(2) + 5;
	int patience = rnd(10) + 20;
	bool reading = false;
	bool ordering = false;
	bool waiting = false;
	bool eating = false;
	bool paying = false;

public:
	void setSize(int input);
	int getSize();
	void setTime(int input);
	int getTime();
	void setPatience(int input);
	int getPatience();
	void setSitting(bool input);
	bool getSitting();
	void setReading(bool input);
	bool getReading();
	void setOrdering(bool input);
	bool getOrdering();
	void setWaiting(bool input);
	bool getWaiting();
	void setEating(bool input);
	bool getEating();
	void setPaying(bool input);
	bool getPaying();
};