#include "menu_funcs.h"

namespace Prog3 {
	void first(message_queue_list& A) {
		std::cout << "Creating a new object using copy constructor (copy your queue-list)" << std::endl;
		message_queue_list B(A);
		std::cout << "Result:\n" << B << std::endl;

		std::cout << "Creating a new object using move constructor"
			<< "(as a movable object, we use the one created using the copy constructor)" << std::endl;
		message_queue_list C = std::move(B);
		std::cout << "Result:\n" << "Old object\n" << B << "New object\n" << C << std::endl;

		std::cout << "Using the move operator (we assign the last created object to our "
			<< "original object, this will not change the original object)" << std::endl;
		A = std::move(C);
		std::cout << "Result:\n" << "Old object\n" << C << "New object\n" << A << std::endl;

		std::cout << "Testing initializing constructor with parameters" << std::endl;
		std::cout << "Enter the number of elements in the message array" << std::endl;
		int num = getNum<int>(0);
		Message* message_arr = new Message[num];
		for (int i = 0; i < num; ++i) {
			Message a;
			std::cout << i + 1 << " Message" << std::endl;
			std::cin >> a;
			message_arr[i] = a;
		}
		std::cout << "Enter the number of elements you want to create the list" << std::endl;
		int count = getNum(0);
		try {
			message_queue_list D(message_arr, count, num);
			std::cout << "Result:\n" << D;
		}
		catch (...) {
			delete [] message_arr;
			throw;
		}
		delete [] message_arr;
	}

	void second(message_queue_list& A) {
		std::cout << "Enter a message" << std::endl;
		Message a;
		std::cin >> a;
		A += a;
	}

	void third(message_queue_list& A) {
		Message* a;
		a = A.list_pop();
		if (a == nullptr) {
			std::cout << "Error, your list is empty" << std::endl;
			return;
		}
		std::cout << *a;
	}

	void fourth(message_queue_list& A) {
		Message* a;
		a = A.queue_word_search();
		if (a == nullptr) {
			std::cout << "Error, the word has not been found" << std::endl;
			return;
		}
		std::cout << *a;
	}

	void fifth(message_queue_list& A) {
		A.queue_list_ordering_chat();
		std::cout << "Success" << std::endl;
	}

	void sixth(message_queue_list& A) {
		A.queue_list_ordering_time();
		std::cout << "Success" << std::endl;
	}

	void seventh(message_queue_list& A) {
		A.queue_reorganize();
		std::cout << "Success" << std::endl;
	}

	void eight(message_queue_list& A) {
		std::string str = getString();
		message_queue_list a = A[str];
		std::cout << a;
	}

	void ninth(message_queue_list& A) {
		std::cout << A;
	}

	void Menu() {
		message_queue_list A;
		std::function<void(message_queue_list&)> dialog_funcs[] = { first, second, third, fourth, fifth, sixth, seventh, eight, ninth};
		std::cout << "A list has been generated using the default constructor" << std::endl;
		int choice = 0;
		while (true) {
			std::cout << "The menu of your queue-list class:\n";
			std::cout << "1.Constructors | operator '='\n";
			std::cout << "2.List push\n";
			std::cout << "3.List pop\n";
			std::cout << "4.Word search\n";
			std::cout << "5.Sort by chat\n";
			std::cout << "6.Sort by time\n";
			std::cout << "7.Reorganization\n";
			std::cout << "8.Operator []\n";
			std::cout << "9.Print\n";
			std::cout << "0.quiet" << std::endl;
			choice = getNum<int>(0, 9);
			std::cout << std::endl;
			if (choice == 0) {
				return;
			}
			dialog_funcs[choice-1](A);
			std::cout << std::endl;
		}
	}
}