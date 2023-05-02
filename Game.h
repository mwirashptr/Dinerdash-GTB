#pragma once
#include <conio.h>
#include <iostream>
#include <string>
#include <list>

class Game {
private:
	char kbChar = ' ';
	int totalCust = 0;
	int coin = 0;
	std::list<std::string> log;

public:
	void setTotalCust(int input);
	int getTotalCust();
	void setCoin(int input);
	int getCoin();

	void addlog(std::list<std::string>& p, std::string input);
	void printLog(std::list<std::string> p);
	char kbInput();
	void kbControl();

	void mainMenu();
	bool retry();
};

int rnd(int size);