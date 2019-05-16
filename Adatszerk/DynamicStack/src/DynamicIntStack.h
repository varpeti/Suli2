#ifndef DYNAMICINTSTACK_H_
#define DYNAMICINTSTACK_H_

struct NODE
{
	NODE();
	~NODE();

	int value;
	NODE* next;
};

class DynamicIntStack
{
public:
	private:
		NODE* node;

	protected:
	public:
		DynamicIntStack();
		~DynamicIntStack();
		bool isEmpty();
		int top();
		int pop();
		void push(int value);
		void print();
};

#endif /* DYNAMICINTSTACK_H_ */
