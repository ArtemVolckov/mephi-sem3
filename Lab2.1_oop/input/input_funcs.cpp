#include "input_funcs.h"

namespace Prog2 {
	std::string getString() { // функция ввода переменной типа string
		std::string string;
		while (true) {
			std::cout << ">";
			std::cin >> string;
			if (std::cin.eof()) { // обнаружен конец файла
				throw std::runtime_error("Failed to read number: EOF");
			}
			if (std::cin.bad()) { // обнаружена невосстановимая ошибка входного потока
				throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
			}
			if (std::cin.fail()) { // восстановимая ошибка входного потока(неправильный формат ввода)
				std::cin.clear(); // очищаем флаги состояния потока
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все символы до конца строки
				std::cout << "You are wrong; repeat please!" << std::endl;
			}
			else // успешный ввод
				return string;
		}
	}
}