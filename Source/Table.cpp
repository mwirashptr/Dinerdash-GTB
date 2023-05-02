#include "Table.h"

Game Table::getGame() {
	return game;
}
void Table::setCust(Customer input) {
	cust = input;
}
Customer Table::getCust() {
	return cust;
}
void Table::setSize(int input) {
	size = input;
}
int Table::getSize() {
	return size;
}
void Table::setFilled(bool input) {
	filled = input;
}
bool Table::getFilled() {
	return filled;
}

void Table::reading() {
	if (cust.getReading() == true) {
		cust.setTime(cust.getTime() - 1);
		if (cust.getTime() == 0) {
			cust.setOrdering(true);
			cust.setReading(false);
			cust.setTime(rnd(5) + 18);
		}
	}
}
void Table::ordering(int input, std::list<std::string>& q) {
	if (cust.getOrdering() == true) {
		cust.setPatience(cust.getPatience() - 1);
		if (cust.getPatience() == 5) {
			game.addlog(q, "Customer from table " + std::to_string(input + 1) + " is angry, Take their order");
		}
		else if (cust.getPatience() == 0) {
			setFilled(false);
			cust.setOrdering(false);
			cust.setPatience(rnd(3) + 13);
			game.addlog(q, "Customer from table " + std::to_string(input + 1) + " leaved with disappointment");
		}
	}
}
void Table::waiting(Chef food[], int input, std::list<std::string>& q) {
	if (cust.getWaiting() == true) {
		cust.setPatience(cust.getPatience() - 1);
		if (cust.getPatience() == 5) {
			game.addlog(q, "Customer from table " + std::to_string(input + 1) + " is angry, Give their food");
		}
		else if (cust.getPatience() == 0) {
			setFilled(false);
			cust.setWaiting(false);
			food[input].setReady(false);
			food[input].setTableNumber(false);
			food[input].setTime(rnd(2) + 9);
			game.addlog(q, "Customer from table " + std::to_string(input + 1) + " leaved with disappointment");
		}
	}
}
void Table::eating() {
	if (cust.getEating() == true) {
		cust.setTime(cust.getTime() - 1);
		if (cust.getTime() == 0) {
			cust.setPaying(true);
			cust.setEating(false);
		}
	}
}
void Table::paying(int input, std::list<std::string>& q) {
	if (cust.getPaying() == true) {
		cust.setPatience(cust.getPatience() - 1);
		if (cust.getPatience() == 8) {
			game.addlog(q, "Customer from table " + std::to_string(input + 1) + " is angry, Take their payment");
		}
		else if (cust.getPatience() == 0) {
			setFilled(false);
			cust.setPaying(false);
			game.addlog(q, "Customer from table " + std::to_string(input + 1) + " leaved without paying");
		}
	}
}
