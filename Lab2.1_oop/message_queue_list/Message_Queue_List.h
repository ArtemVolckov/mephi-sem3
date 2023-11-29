#pragma once

#include "../message/Message.h"

using namespace Prog2;

namespace Prog3 {
	struct Node { // структура для хранения узла 
		Message message;
		Node* next = NULL;
	};

	class message_queue_list {
	private:
		Node* head; // начало списка
	public:
		message_queue_list() : head(nullptr) {} // инициализация по умолчанию
		message_queue_list(Message arr[], int count, int arr_size); // инициализация из массива сообщений
		message_queue_list(const message_queue_list& other); // копирующий конструктор
		message_queue_list(message_queue_list&& other); // перемещающий конструктор
		
		~message_queue_list() { // деструктор
			Node* ptr = this->head;
			while (ptr != NULL) {
				Node* ptr_next = ptr->next;
				delete ptr;
				ptr = ptr_next;
			}
		}

		void List_Print(); // вывод списка
		Message* list_pop(); // чтение сообщения из очереди
		void list_is_empty(); // проверка состояния очереди
		Message* queue_word_search(); // поиск заданного слова в очереди
		void queue_list_ordering_time(); // сортировка списка по времени
		void queue_list_ordering_chat(); // сортировка списка по чату
		void queue_reorganize(); // реорганизация очереди

		message_queue_list operator [](std::string chat); // выделение всех сообщений из заданного чата в новую очередь
		message_queue_list& operator =(message_queue_list& other); // перегруженный оператор присваивания с копированием
		message_queue_list& operator =(message_queue_list&& other); // перегруженный оператор присваивания с перемещением
		void operator +=(const Message& message); // перегруженнный оператор += (занесение нового сообщения в очередь)
		friend std::ostream& operator <<(std::ostream& stream, message_queue_list& list); // перегрузка оператора вывода
		friend std::istream& operator >>(std::istream& stream, message_queue_list& list); // перегрузка оператора ввода
	};
}
