#pragma once

#include <cstring>
#include <tuple>
#include <compare>

#include "../input/input_funcs.h"

namespace Prog2 {
	class Message {
	private:

		std::string text; // переменная типа string для хранения текста сообщения
		std::string chat; // переменная типа string для хранения чата сообщения
		std::time_t time; // переменная типа time_t для хранения времени в формате unix timestamp

	public:

		Message(); // явный конструктор по умолчанию
		Message(std::string text, std::string chat, size_t time); // конструктор со всеми параметрами
		Message(std::string text, std::string chat); // конструктор с текстом и чатом

		void Print(); // метод вывода состояния класса
		void Input(); // метод ввода состояния класса
		bool word_search(std::string word); // метод поиска заданного слова по сообщению

		// сеттеры (setters)
		void SetText(std::string text) {
			this->text = text;
		}
		void SetChat(std::string chat) {
			this->chat = chat;
		}
		void SetTime(std::time_t time);

		// геттеры (getters)
		std::string GetText() {
			return text;
		}
		std::string GetChat() {
			return chat;
		}
		std::time_t GetTime() {
			return time;
		}

		// операторы (operators)
		Message operator +(const Message& other) const; // перегруженный оператор сложения(объединение двух сообщений из одного чата в одно)
		std::tuple<std::strong_ordering, std::strong_ordering> operator <=>(const Message& other) const; // перегруженный оператор эквивалентности
		
		friend std::ostream& operator <<(std::ostream& stream, const Message& message) { // перегрузка оператора ввода
			std::string cur_time = ctime(&(message.time));
			stream << "Text -> " << message.text << " Chat -> " << message.chat << "  " << cur_time;
			return stream;
		}
		
		friend std::istream& operator >>(std::istream& stream, Message& message) { // перегрузка оператора ввода
			std::cout << "Enter the text\n";
			message.text = getString();
			std::cout << "Enter the chat\n";
			message.chat = getString();
			std::cout << "Enter the time\n";
			message.time = getNum<time_t>(0, std::time(nullptr));
			return stream;
		}

		//способ реализации перегрузки оператора spaceshp <=> без кортежа
		//std::strong_ordering operator <=>(const Message& other) const;
	};
}
