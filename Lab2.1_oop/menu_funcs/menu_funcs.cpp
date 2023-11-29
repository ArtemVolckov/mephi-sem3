#include "menu_funcs.h"

void first() {
}

void second() {
	std::cout << "gg2";
}

void third() {
	std::cout << "gg2";
}

void fourth() {
	std::cout << "gg2";
}

void fifth() {
	std::cout << "gg2";
}

void sixth() {
	std::cout << "gg2";
}

void Menu() {
	std::function<void()> dialog_funcs[] = { first, second };
	int choice = 0;
	while (true) {
		std::cout << "The menu of your Message class:\n";
		std::cout << "1.Constructors\n";
		std::cout << "2.Setters/Getters\n";
		std::cout << "3.Input/Output\n";
		std::cout << "4.Operators\n";
		std::cout << "5.Word search\n";
		std::cout << "0.quiet" << std::endl;
		choice = getNum<int>(0, 5);
		if (choice == 0) {
			return;
		}
	}
	//dialog_funcs[0]();
}