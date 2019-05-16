#include <iostream>
#include <exception>

#include "DynamicIntStack.h"

using namespace std;

int main() {
	{
	cout << "Test the Dynamic Int Stack" << endl;

	DynamicIntStack Dynamic_int_stack;

	// empty stack
	cout << "\n/**********Empty Stack**********\\" << endl;
	cout << "isEmpty(): " << Dynamic_int_stack.isEmpty() << endl; //1 (true)
	cout << "print(): "; Dynamic_int_stack.print();	cout << endl;

	try {
		cout << "top(): ";
		cout << Dynamic_int_stack.top() << endl; //exception
	} catch (exception& e) {
		cout << e.what() << endl;
	}
	try {
		cout << "pop(): ";
		cout << Dynamic_int_stack.pop() << endl; //exception
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	// push & check
	cout << "\n/**********Push to Stack**********\\" << endl;

	Dynamic_int_stack.push(1);
	Dynamic_int_stack.push(2);
	Dynamic_int_stack.push(3);
	Dynamic_int_stack.push(4);
	Dynamic_int_stack.push(5);

	cout << "After 5 item: "; Dynamic_int_stack.print(); cout << endl;

	Dynamic_int_stack.push(6);
	Dynamic_int_stack.push(7);
	Dynamic_int_stack.push(8);
	Dynamic_int_stack.push(9);
	Dynamic_int_stack.push(10);

	cout << "After 10 item: "; Dynamic_int_stack.print(); cout << endl;
	cout << "isEmpty(): " << Dynamic_int_stack.isEmpty() << endl; //0 (false)

	Dynamic_int_stack.push(11);

	cout << "After 11 item: ";	Dynamic_int_stack.print(); cout << endl;

	// pop
	cout << "\n/**********Pop from Stack**********\\" << endl;
	try {
		cout << "top(): " << Dynamic_int_stack.top() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "After 5 item: "; Dynamic_int_stack.print(); cout << endl;
		cout << "top(): " << Dynamic_int_stack.top() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		//cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		//cout << "pop(): " << Dynamic_int_stack.pop() << endl;
		//cout << "pop(): " << Dynamic_int_stack.pop() << endl;

		//cout << "pop(): " << Dynamic_int_stack.pop() << endl; //exception
	} catch (exception& e) {
		cout << e.what() << endl;
	}
	}
	getchar();

	return 0;
}
