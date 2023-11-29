#pragma once
#pragma warning(disable : 4996)

#include <cstring>
#include <iostream>

#define _CRTDBG_MAP_ALLOC

namespace Prog2 {
	// функция ввода числа
	template<class T>
	T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
		T a = 0;
		while (true) {
			std::cout << ">";
			std::cin >> a;
			if (std::cin.eof()) // обнаружен конец файла
				throw std::runtime_error("Failed to read number: EOF");
			else if (std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
				throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
			// прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
			else if (std::cin.fail() || a < min || a > max) {
				std::cin.clear(); // очищаем флаги состояния потока
				// игнорируем все символы до конца строки
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "You are wrong. Repeat please!" << std::endl;
			}
			else // успешный ввод
				return a;
		}
	}

	std::string getString(); // функция ввода переменной типа string
}
