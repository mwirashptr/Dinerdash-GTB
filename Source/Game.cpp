#include "Game.h"

void Game::setTotalCust(int input) {
	totalCust = input;
}
int Game::getTotalCust() {
	return totalCust;
}
void Game::setCoin(int input) {
	coin = input;
}
int Game::getCoin() {
	return coin;
}

void Game::addlog(std::list<std::string>& p, std::string input) {
	p.push_front(input);
}
void Game::printLog(std::list<std::string> p) {
	for (int i = 0; i < 8; i++) {
		if (!p.empty()) {
			std::cout << "\n\t" << p.front();
			p.pop_front();
		}
	}
}
char Game::kbInput() {
	char kbChar;
	if (_kbhit()) {
		kbChar = _getch();
		return kbChar;
	}
}
void Game::mainMenu() {
	std::cout << "\n\tWelcome To DinerDash v0.8\n";
	std::cout << "\n\tThe Game will run for 5 minutes,";
	std::cout << "\n\tSo you need to serve Customer as much as you can.\n";
	std::cout << "\n\tThere are 4 keys to interact with:";
	std::cout << "\n\t A  : to put customers to the table";
	std::cout << "\n\t S  : to take the customers' order";
	std::cout << "\n\t D  : to serve food to the customers' table";
	std::cout << "\n\t F  : to take the customers' payment\n";
	std::cout << "\n\tOkay that's all.... Have fun!!!";

	std::cout << "\n\tEnter any key to continue... \n\t>";
	std::cin >> kbChar;
	system("CLS");
}
bool Game::retry() {
	while (true) {
		std::cout << "\n\tWanna try again??? [Y/N]\n\t>";
		std::cin >> kbChar;
		if (kbChar == 'y' || kbChar == 'Y') {
			system("CLS");
			return true;
			break;
		}
		else if (kbChar == 'n' || kbChar == 'N') {
			std::cout << "\n\tThank You for Playing :)\n";
			std::cout << "\n\tBayam :v";
			return false;
			break;
		}
		else {
			system("CLS");
		}
	}
}
int rnd(int size) {
	return rand() % size;
}
