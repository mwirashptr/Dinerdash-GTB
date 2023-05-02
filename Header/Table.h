#pragma once
#include <iostream>
#include <queue>

#include "Game.h"
#include "Customer.h"
#include "Chef.h"

class Table {
private:
	Game game;
	Customer cust;
	int size = 0;
	bool filled = false;

public:
	Game getGame();
	void setCust(Customer input);
	Customer getCust();
	void setSize(int input);
	int getSize();
	void setFilled(bool input);
	bool getFilled();

	void reading();
	void ordering(int input, std::list<std::string>& q);
	void waiting(Chef food[], int input, std::list<std::string>& q);
	void eating();
	void paying(int input, std::list<std::string>& q);
};
