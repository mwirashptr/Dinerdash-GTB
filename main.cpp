#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <typeinfo>
#include <string>
#include <queue>
#include <list>

#include "Game.h"
#include "Customer.h"
#include "Table.h"
#include "Chef.h"

Game Dash;

void randomCust(Customer cust[], std::queue<Customer>& p, std::list<std::string>& q) {
	Customer customer;
	int random = rnd(4);
	customer = cust[random];
	p.push(customer);
	Dash.addlog(q, "Customer entered your restaurant");
}

std::queue<Customer> patience(std::queue<Customer> p, std::list<std::string>& q) {
	std::queue<Customer> temp;
	while (!p.empty()) {
		p.front().setPatience(p.front().getPatience() - 1);
		if (p.front().getPatience() == 8) {
			Dash.addlog(q, "Customer is a little bit angry");
		}
		else if (p.front().getPatience() == 0) {
			p.pop();
			Dash.addlog(q, "Customer leaved with disappoinment");
		}
		if (!p.empty()) {
			temp.push(p.front());
			p.pop();
		}
	}
	return temp;
}

void pushToTable(std::queue <Customer>& cust, int input, Table table[], std::list<std::string>& q) {
	if (cust.empty()) {
		Dash.addlog(q, "The Queue is empty");
	}
	else if (table[input - 1].getFilled() == true) {
		Dash.addlog(q, "Table is filled");
		return;
	}
	else if (cust.front().getSize() <= table[input - 1].getSize()) {
		cust.front().setReading(true);
		table[input - 1].setCust(cust.front());
		cust.pop();
		table[input - 1].setFilled(true);
		Dash.addlog(q, "Customer is sat on Table " + std::to_string(input));
	}
	else if (cust.front().getSize() > table[input - 1].getSize()) {
		Dash.addlog(q, "Table size is too small, Try again");
	}
	else {
		Dash.addlog(q, "Table Error");
	}
}

Customer takeOrder(Table table[], int input, Chef food[], std::list<std::string>& q) {
	Customer temp = table[input - 1].getCust();
	if (table[input - 1].getFilled() == false) {
		Dash.addlog(q, "Table " + std::to_string(input) + " is empty");
	}
	else if (temp.getOrdering() == false) {
		Dash.addlog(q, "Customer from Table " + std::to_string(input) + " is not ordering");
	}
	else {
		temp.setOrdering(false);
		temp.setWaiting(true);
		temp.setPatience(rnd(5) + 12);
		food[input - 1].setTableNumber(input);
		Dash.addlog(q, "Order from Table " + std::to_string(input) + " has been taken");
	}
	return temp;
}

Customer giveFood(Table table[], int input, Chef food[], std::list<std::string>& q) {
	Customer temp = table[input - 1].getCust();
	if (table[input - 1].getFilled() == false) {
		Dash.addlog(q, "Table " + std::to_string(input) + " is empty");
	}
	else if (food[input - 1].getReady() == false) {
		Dash.addlog(q, "The Food is not cooked yet");
	}
	else {
		temp.setWaiting(false);
		temp.setEating(true);
		temp.setPatience(rnd(5) + 7);
		food[input - 1].setReady(false);
		food[input - 1].setTableNumber(0);
		Dash.addlog(q, "Food from table " + std::to_string(input) + " has been given");
	}
	return temp;
}

Customer takePayment(Table table[], int input, Chef food[], std::list<std::string>& q) {
	Customer temp = table[input - 1].getCust();
	if (table[input - 1].getFilled() == false) {
		Dash.addlog(q, "Table " + std::to_string(input) + " is empty");
	}
	else if (temp.getPaying() == false) {
		Dash.addlog(q, "Customer from Table " + std::to_string(input) + " is not ready to pay yet");
	}
	else {
		table[input - 1].setFilled(false);
		temp.setPaying(false);
		Dash.setTotalCust(Dash.getTotalCust() + 1);
		Dash.setCoin(Dash.getCoin() + ((rnd(10) + 10) * table[input - 1].getSize()));
		Dash.addlog(q, "Customer from Table " + std::to_string(input) + " is leaving The Restaurant, Good Job !!!");
	}
	return temp;
}

void printCust(std::queue<Customer> p) {
	std::cout << "\n\tQueue  :";
	while (!p.empty()) {
		std::cout << " ( " << p.front().getSize() << "," << p.front().getPatience() << " )";
		p.pop();
	}
}

std::string conTable(Customer cust) {
	if (cust.getReading() == true) {
		return " , Reading the menu";
	}
	else if (cust.getOrdering() == true) {
		return " , Ready to order";
	}
	else if (cust.getWaiting() == true) {
		return " , Waiting the food";
	}
	else if (cust.getEating() == true) {
		return " , Eating...";
	}
	else if (cust.getPaying() == true) {
		return " , Ready to pay";
	}
	else {
		return "";
	}
}

std::string filled(Table table) {
	if (table.getFilled() != true) {
		return std::to_string(table.getSize()) + " , Empty";
	}
	else {
		return std::to_string(table.getCust().getSize());
	}
}

void printTable(Table table[], Chef food[], std::list<std::string>& q) {
	std::cout << "\n\tTable  :";
	for (int i = 0; i < 6; i++) {
		table[i].reading();
		table[i].ordering(i, q);
		table[i].waiting(food, i, q);
		table[i].eating();
		table[i].paying(i, q);
		std::cout << "\n\t[" << i + 1 << "]( " << filled(table[i]) << conTable(table[i].getCust()) << " )";
	}
}

std::string conFood(Chef c) {
	if (c.getReady() == true) {
		return "Cooked";
	}
	else if (c.getTableNumber() == 0) {
		return " ";
	}
	else {
		return "Cooking...";
	}
}

void printFood(Chef food[], Table table[]) {
	std::cout << "\n\tFood   :";
	for (int i = 0; i < 6; i++) {
		if (table[i].getCust().getWaiting() == false) {
			food[i].setTableNumber(0);
		}
		else if (food[i].getTableNumber() != 0 && food[i].getReady() != true) {
			food[i].setTime(food[i].getTime() - 1);
			if (food[i].getTime() == 0) {
				food[i].setReady(true);
			}
		}
		std::cout << " [" << i + 1 << "](" << conFood(food[i]) << ") ";
	}
}

int main() {
	srand(std::time(NULL));
	int time = 300, timeout = 1;
	char kbChar;

	Customer custType[4];
	custType[0].setSize(4);
	custType[1].setSize(4);
	custType[2].setSize(4);
	custType[3].setSize(2);

	Table tableNumber[6]{};
	tableNumber[0].setSize(4);
	tableNumber[1].setSize(4);
	tableNumber[2].setSize(4);
	tableNumber[3].setSize(4);
	tableNumber[4].setSize(2);
	tableNumber[5].setSize(2);

	std::list<std::string> log;
	std::queue<Customer> custQ;
	Chef food[6]{};

	int running = true;
	while (running) {
		Dash.mainMenu();
		std::cin.ignore();
		while (running) {
			//Update
			time--;
			int MM, SS;
			MM = time / 60;
			SS = time % 60;
			if (time % 10 == rnd(5) && time > 45) {
				randomCust(custType, custQ, log);
			}
			custQ = patience(custQ, log);

			//Input
			kbChar = Dash.kbInput();
			int input = 0;
			switch (kbChar) {
			case 'a':
				system("CLS");
				std::cout << "\n\n\tPut customer to Table ";
				std::cin >> input;
				pushToTable(custQ, input, tableNumber, log);
				Sleep(100);
				system("CLS");
				break;

			case 's':
				system("CLS");
				std::cout << "\n\n\tTake order from Table ";
				std::cin >> input;
				tableNumber[input - 1].setCust(takeOrder(tableNumber, input, food, log));
				Sleep(100);
				system("CLS");
				break;

			case 'd':
				system("CLS");
				std::cout << "\n\n\tGive the food to Table ";
				std::cin >> input;
				tableNumber[input - 1].setCust(giveFood(tableNumber, input, food, log));
				Sleep(100);
				system("CLS");
				break;

			case 'f':
				system("CLS");
				std::cout << "\n\n\tTake payment from Table ";
				std::cin >> input;
				tableNumber[input - 1].setCust(takePayment(tableNumber, input, food, log));
				Sleep(100);
				system("CLS");
				break;
			}

			//Render
			std::cout << "\n\t\t\t\t[ " << MM << " : " << SS << " ]\n";
			printCust(custQ); std::cout << "\n";
			printTable(tableNumber, food, log); std::cout << "\n";
			printFood(food, tableNumber); std::cout << "\n\n";
			std::cout << "\n\tKey : a, s, d, f, 1, 2, 3, 4, 5, 6\n";
			std::cout << "\t-------------------------------------------------------------------\n\tLOG :";
			Dash.printLog(log);

			Sleep(1000);
			system("CLS");
			if (time == timeout) {
				running = false;
				time = 300;
			}
		}
		std::cout << "\n\tGame Over\n";
		std::cout << "\n\tYou have run the restaurant successfully";
		std::cout << "\n\tYou got [" << Dash.getTotalCust() << "] total Customer,";
		std::cout << "\n\tYour today's income is [" << Dash.getCoin() << "]";
		std::cout << "\n";

		running = Dash.retry();
	}
	return 0;
}