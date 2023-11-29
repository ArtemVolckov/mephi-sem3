#include "Message_Queue_List.h"

namespace Prog3 {
	message_queue_list::message_queue_list(Message arr[], int count, int arr_size) { // инициализация из массива сообщений
		if (count > arr_size)
			throw std::invalid_argument("Invalid argument. Initialization error, count member is not suitable");
		if (count == 0) {
			this->head = NULL;
		}
		else {
			this->head = new Node;
			Node* ptr = this->head;
			ptr->message = arr[0];

			for (int i = 1; i < count; ++i) {
				Node* new_node = new Node;
				new_node->message = arr[i];
				ptr->next = new_node;
				ptr = new_node;
			}
		}
	}

	message_queue_list::message_queue_list(const message_queue_list& other) {
		std::cout << "Copy constructor";
		Node* ptr = other.head;
		if (ptr == NULL)
			this->head = NULL;
		else {
			this->head = new Node;
			this->head->next = NULL;
			this->head->message = ptr->message;
			Node* save = this->head;
			ptr = ptr->next;
			while (ptr != NULL) {
				save->next = new Node;
				save->next->next = NULL;
				save->next->message = ptr->message;
				save = save->next;
				ptr = ptr->next;
			}
		}
	}

	message_queue_list::message_queue_list(message_queue_list&& other) {
		Node* ptr = other.head;
		this->head = ptr;
		Node* save = this->head;
		while (ptr != NULL) {
			save = ptr;
			save = save->next;
			ptr = ptr->next;
		}
		other.head = NULL;
	}

	void message_queue_list::List_Print() { // вывод
		if (head == NULL) {
			std::cout << "List is empty\n";
			return;
		}
		Node* ptr = head;
		std::cout << "List:\n";
		while (ptr) {
			ptr->message.Print();
			ptr = ptr->next;
		}
	}

	Message* message_queue_list::list_pop() {
		if (head == NULL) {
			return NULL;
		}
		else {
			static Message message_ptr = head->message;
			Node* ptr = head;
			head = head->next;
			delete ptr;
			return &message_ptr;
		}
	}

	void message_queue_list::list_is_empty() {
		if (head == NULL) {
			std::cout << "List is empty\n";
		}
		else {
			std::cout << "List is not empty\n";
		}
	}

	Message* message_queue_list::queue_word_search() {
		std::cout << "Enter the word to search\n";
		std::string word_to_search;
		word_to_search = getString();
		Node* ptr = head;
		while (ptr != NULL) {
			if (ptr->message.word_search(word_to_search)) {
				return &ptr->message;
			}
			ptr = ptr->next;
		}
		return NULL;
	}

	void message_queue_list::queue_list_ordering_time() {
		if (head == NULL)
			return;
		if (head->next == NULL)
			return;
		else {
			Node* ptr = head;
			Node* par = NULL;
			int counter = 0;
			while (ptr != NULL) {
				counter++;
				ptr = ptr->next;
			}
			ptr = head;
			for (int i = 0; i < counter - 1; ++i) {
				while (ptr->next != NULL) {
					std::tuple<std::strong_ordering, std::strong_ordering> spaceship_tuple = ptr->message <=> ptr->next->message;
					if (std::is_gt(std::get<1>(spaceship_tuple))) {
						if (par == NULL) {
							Node* save = ptr->next;
							ptr->next = save->next;
							save->next = ptr;
							head = save;
							par = save;
							continue;
						}
						else {
							Node* save = ptr->next;
							ptr->next = save->next;
							save->next = ptr;
							par->next = save;
							par = save;
							continue;
						}
					}
					par = ptr;
					ptr = ptr->next;
				}
			}
		}
	}

	void message_queue_list::queue_list_ordering_chat() {
		if (head == NULL)
			return;
		if (head->next == NULL)
			return;
		else {
			Node* ptr = head;
			Node* par = NULL;
			int counter = 0;
			while (ptr != NULL) {
				counter++;
				ptr = ptr->next;
			}
			ptr = head;
			for (int i = 0; i < counter - 1; ++i) {
				while (ptr->next != NULL) {
					std::tuple<std::strong_ordering, std::strong_ordering> spaceship_tuple = ptr->message <=> ptr->next->message;
					if (std::is_gt(std::get<0>(spaceship_tuple))) {
						if (par == NULL) {
							Node* save = ptr->next;
							ptr->next = save->next;
							save->next = ptr;
							head = save;
							par = save;
							continue;
						}
						else {
							Node* save = ptr->next;
							ptr->next = save->next;
							save->next = ptr;
							par->next = save;
							par = save;
							continue;
						}
					}
					par = ptr;
					ptr = ptr->next;
				}
			}
		}
	}

	void message_queue_list::queue_reorganize() {
		if (head == NULL) {
			std::cout << "List is empty\n";
			return;
		}
		Node* ptr = head;
		while (ptr->next != NULL) {
			if (ptr->message.GetChat() == ptr->next->message.GetChat()) {
				ptr->message = ptr->message + ptr->next->message;
				Node* save = ptr->next;
				ptr->next = save->next;
				delete save;
			}
			ptr = ptr->next;
		}
	}

	message_queue_list message_queue_list::operator [](std::string chat) {
		message_queue_list a;
		Node* ptr = head;
		Node* par = NULL;
		while (ptr != NULL) {
			if (ptr->message.GetChat() == chat) {
				if (par == NULL) {
					head = ptr->next;
				}
				else {
					par->next = ptr->next;
				}
				Node* save = ptr->next;
				static Message message = ptr->message;
				a += message;
				delete ptr;
				ptr = save;
				continue;
			}
			ptr = ptr->next;
		}
		return a;
	}

	message_queue_list& message_queue_list::operator =(message_queue_list& other) {
		if (this == &other) {
			return *this;
		}

		Node* ptr = this->head;
		while (ptr != NULL) {
			Node* ptr_next = ptr->next;
			delete ptr;
			ptr = ptr_next;
		}

		this->head = NULL;

		if(other.head != NULL) {
			ptr = other.head;
			Node* new_node = new Node;
			new_node->message = ptr->message;
			this->head = new_node;
			Node* first_ptr = this->head;
			ptr = ptr->next;

			while (ptr != NULL) {
				Node* new_node = new Node;
				new_node->message = ptr->message;
				first_ptr->next = new_node;
				ptr = ptr->next;
				first_ptr = first_ptr->next;
			}
		}
		return *this;
	}

	message_queue_list& message_queue_list::operator =(message_queue_list&& other) {
		if (this != &other) {
			Node* ptr = this->head;
			while (ptr != NULL) {
				Node* ptr_next = ptr->next;
				delete ptr;
				ptr = ptr_next;
			}

			this->head = NULL;

			if (other.head != NULL) {
				this->head = other.head;
				other.head = NULL;
			}
		}
		return *this;
	}

	void message_queue_list::operator +=(const Message & message) {
		if (this->head == NULL) {
			this->head = new Node;
			this->head->message = message;
			this->head->next = NULL;
			return;
		}
		else {
			Node* ptr = this->head;
			Node* par = ptr;
			while(ptr!=NULL) {
				par = ptr;
				ptr = ptr->next;
			}
			par->next = new Node;
			par->next->next = NULL;
			par->next->message = message;
		}
	}

	std::ostream& operator <<(std::ostream& stream, message_queue_list& list) {
		list.List_Print();
		return stream;
	}

	std::istream& operator >>(std::istream& stream, message_queue_list& list) {
		if (list.head != NULL) {
			Node* ptr = list.head;
			while (ptr != NULL) {
				Node* save = ptr->next;
				delete ptr;
				ptr = save;
			}
			list.head = NULL;
		}
		int num = 0;
		std::cout << "Enter the number of messages\n";
		num = getNum<int>(0);
		for (int i = 0; i < num; ++i) {
			std::cout << i+1 << " Message:\n";
			Message a;
			a.Input();
			list += a;
		}
		return stream;
	}
}