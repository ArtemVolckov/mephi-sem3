#include "Message_Queue.h"

namespace Prog3 {
	message_queue::message_queue(Message* arr[], int count) {
		if (count > this->SZ || count > sizeof(arr) / sizeof(arr[0])) 
			throw std::invalid_argument("Invalid argument. Initialization error, count member is not suitable");
		for (int i = 0; i < count; ++i) {
			*this += arr[i];
		}
	}

	void message_queue::Print_queue() {
		if (this->size == 0) {
			std::cout << "Queue is empty\n";
			return;
		}
		std::cout << "Queue:\n";
		int k = this->head;
		while (k != this->tail) {
			k = k % this->SZ;
			this->arr[k]->Print();
			k++;
		}
		return;
	}

	void message_queue::Insert_queue() {
		std::cout << "Enter the size of Queue. It has to be less or equal to " << this->SZ << std::endl;
		int size = getNum<int>(0, this->SZ);
		this->size = 0;
		this->head = 0;
		this->tail = 0;
		int count = 0;
		while (count != size) {
			this->size++;
			this->tail++;
			std::cout << count + 1 << std::endl;
			static Message a;
			a.Input();
			this->arr[count] = &a;
			count++;
		}
	}

	void message_queue::is_empty() {
		if (this->size == 0) {
			std::cout << "Queue is empty\n";
			return;
		}
		else if (this->size == this->SZ) {
			std::cout << "Queue is full\n";
		}
		else
			std::cout << "Queue is partially filled\n";
	}

	Message* message_queue::pop() {
		if (this->size == 0) {
			std::cout << "Queue is empty\n";
			return NULL;
		}
		int save = this->head;
		this->head = (this->head + 1) % this->SZ;
		this->size--;
		return this->arr[save];
	}

	void message_queue::queue_reorganize() {
		if (this->size == 0) {
			std::cout << "Queue is empty";
			return;
		}
		else if (this->size == 1) {
			return;
		}
		int save = this->head;
		while (save != this->tail - 1) {
			save = save % this->SZ;
			if (this->arr[save % this->SZ]->GetChat() == this->arr[(save + 1) % this->SZ]->GetChat()) {
				*this->arr[save % this->SZ] = *this->arr[save % this->SZ] + *this->arr[(save + 1) % this->SZ];
				int k = (save + 1) % this->SZ;
				while ((k + 1) /* % this->SZ*/ != this->tail) {
					k = k % this->SZ;
					this->arr[k % this->SZ] = this->arr[(k + 1) % this->SZ];
					k++;
				}
				save--;
				this->size--;
				this->tail--;
				if (this->tail == 0) {
					this->tail = 10;
				}
			}
			save++;
		}
		return;
	}

	Message* message_queue::queue_word_search() {
		std::cout << "Enter the word to search\n";
		std::string word_queue;
		word_queue = getString();
		int save = this->head;
		while (save != this->tail) {
			save = save % this->SZ;
			if (this->arr[save]->word_search(word_queue)) {
				return this->arr[save];
			}
			save++;
		}
		return NULL;
	}

	void message_queue::queue_ordering_time() { // сортировка пузырьком
		if (this->size == 0) {
			std::cout << "Queue is empty\n";
			return;
		}
		for (int i = 0; i < this->size; ++i) {
			for (int j = this->head; j != this->tail - 1; ++j) {
				j = j % this->SZ;
				std::tuple<std::strong_ordering, std::strong_ordering> spaceship_tuple = *this->arr[j] <=> *this->arr[(j + 1) % this->SZ];
				if (std::is_gt(std::get<1>(spaceship_tuple))) {
					Message* save = this->arr[j];
					this->arr[j] = this->arr[(j + 1) % this->SZ];
					this->arr[(j + 1) % this->SZ] = save;
				}
			}
		}
	}

	void message_queue::queue_ordering_chat() {
		if (this->size == 0) {
			std::cout << "Queue is empty\n";
			return;
		}
		for (int i = 0; i < this->size; ++i) {
			for (int j = this->head; j != this->tail - 1; ++j) {
				j = j % this->SZ;
				std::tuple<std::strong_ordering, std::strong_ordering> spaceship_tuple = *this->arr[j] <=> *this->arr[(j + 1) % this->SZ];
				if (std::is_gt(std::get<0>(spaceship_tuple))) {
					Message* save = this->arr[j];
					this->arr[j] = this->arr[(j + 1) % this->SZ];
					this->arr[(j + 1) % this->SZ] = save;
				}
			}
		}
	}

	message_queue& message_queue::operator +=(Message* message) {
		if (this->size == this->SZ) {
			std::cout << "Error. Queue is full\n";
			return *this;
		}
		this->arr[this->tail % this->SZ] = message;
		this->tail = (((this->tail + 1) - 1) % this->SZ) + 1;
		this->size++;
		return *this;
	}


	message_queue message_queue::operator [](std::string chat) {
		message_queue a;
		for (int i = this->head; i != this->tail; ++i) {
			i = i % this->SZ;
			if (this->arr[i]->GetChat() == chat) {
				a.arr[a.size] = this->arr[i];
				a.size++;
				a.tail++;
				int save = i;
				if (this->size != 1) {
					while ((save + 1) != this->tail) {
						save = save % this->SZ;
						this->arr[save] = this->arr[(save + 1) % this->SZ];
						save++;
					}
				}
				i--;
				this->tail--;
				this->size--;
			}
		}
		return a;
	}

	/*std::ostream& operator <<(std::ostream& stream, const message_queue& queue) {
		stream << "gg";
		return stream;
	}*/
}