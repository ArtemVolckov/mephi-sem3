#pragma once

#include "../message/Message.h"

using namespace Prog2;

namespace Prog3 {
	class message_queue {
	private:
		static const int SZ = 10;
		int size = 0;
		int head = 0;
		int tail = 0;
		Message* arr[SZ];

	public:
		message_queue() {}; // явный конструктор по умолчанию
		message_queue(Message* arr[], int count); // создание экземпляров класса с инициализацией заданным
		                                          // количеством сообщений из массива сообщений
		void Print_queue(); // вывод очереди
		void Insert_queue(); // ввод очереди
		void is_empty(); // проверка состояния очереди
		Message* pop(); // pop
		void queue_reorganize(); // реорганизация очереди все соседние сообщения из одного чата объединяются в одно
		Message* queue_word_search(); // поиск заданного слова в очереди
		void queue_ordering_time(); // упорядочивание очереди по времени
		void queue_ordering_chat(); // упорядочивание очереди по названию чата

		message_queue& operator +=(Message* message); // push back
		message_queue operator [](std::string chat); // выделение всех сообщений из заданного чата в новую очередь
		
		friend std::ostream& operator <<(std::ostream& stream, message_queue& queue) { // вывод очереди
			queue.Print_queue();
			return stream;
		}

		friend std::istream& operator >>(std::istream& stream, message_queue& queue) { // ввод очереди
			queue.Insert_queue();
			return stream;
		}
	};


}
