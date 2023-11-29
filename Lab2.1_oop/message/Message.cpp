#include "Message.h"

namespace Prog2 {
	// констуркторы
	Message::Message() {
		this->text = "";
		this->chat = "";
		this->time = 0;
	}
	Message::Message(std::string text, std::string chat, size_t time) {
		this->text = text;
		this->chat = chat;
		this->time = time;
	}
	Message::Message(std::string text, std::string chat) {
		this->text = text;
		this->chat = chat;
		this->time = std::time(nullptr);
	}

	void Message::Print() { // вывод сообщения
		std::string cur_time = ctime(&(this->time)); // переводим время из unix timestamp в строку
		std::cout << "Text -> " << this->text << " Chat -> " << this->chat << "  " << cur_time;
	}
	void Message::Input() { // ввод сообщения
		std::cout << "Enter the text\n";
		this->text = getString();
		std::cout << "Enter the chat\n";
		this->chat = getString();
		std::cout << "Enter the time\n";
		this->time = getNum<time_t>(0, std::time(nullptr));
	}

	void Message::SetTime(std::time_t time) { // сеттер для времени
		if (time < 0) {
			throw std::invalid_argument("Invalid time");
		}
		this->time = time;
	}

	bool Message::word_search(std::string word) { // метод поиска заданного слова по сообщению
		size_t message_length = text.length();
		size_t word_length = word.length();
		if (message_length < word_length) 
			return false;

		bool match;
		for (size_t i = 0; i <= message_length - word_length; ++i) {
			match = true;
			for (size_t j = 0; j < word_length; ++j) {
				if (text[i + j] != word[j]) {
					match = false;
					break;
				}
			}
			if (match)
				return true;
		}
		return false;
	}

	Message Message::operator +(const Message& other) const { // перегруженный оператор сложения
		std::tuple<std::strong_ordering, std::strong_ordering> spaceship_tuple = *this <=> other;
		//if (this->chat != other.chat)
		//	throw std::invalid_argument("Invalid arguments. Messages have diffent chats");
		if (std::is_neq(std::get<0>(spaceship_tuple))) // is_neq - !=
			throw std::invalid_argument("Invalid arguments. Messages have diffent chats");

		Message result;
		result.chat = this->chat;

		//if (this->time < other.time || this->time == other.time) {
		if(std::is_lteq(std::get<1>(spaceship_tuple))) { // is_lteq - <=
			result.text = this->text + other.text;
			result.time = other.time;
		}

		else {
			result.text = other.text + this->text;
			result.time = this->time;
		}

		return result;
	}

	// перегруженный оператор эквивалентности. Возвращаяемое значение метода прредставлено кортежом tuple
	// обязательное использование ключевого слова const, без него функция не перегружается
	std::tuple <std::strong_ordering, std::strong_ordering> Message::operator <=>(const Message& other) const {
		std::strong_ordering chat, time;
		if (this->chat.length() < other.chat.length())
			chat = std::strong_ordering::less;
		else if (this->chat.length() > other.chat.length())
			chat = std::strong_ordering::greater;
		else {
			chat = std::strong_ordering::equal;
			for (int i = 0; i < this->chat.length(); ++i) {
				if(this->chat[i] < other.chat[i]) 
					chat = std::strong_ordering::less;
				else if(this->chat[i] > other.chat[i]) 
					chat = std::strong_ordering::greater;
			}
		}

		if (this->time < other.time)
			time = std::strong_ordering::less;
		if (this->time > other.time)
			time = std::strong_ordering::greater;
		else
			time = std::strong_ordering::equal;

		return std::make_tuple(chat, time);
	}

	/*std::strong_ordering Message::operator <=>(const Message& other) const {
		if (this->chat.length() < other.chat.length())
			return std::strong_ordering::less;
		else if (this->chat.length() > other.chat.length())
			return std::strong_ordering::greater;
		else
			return std::strong_ordering::equal;
	}*/
}