#include "DynamicIntStack.h"
#include <iostream>

NODE::NODE()
{
	std::cout << "Letrejottem: " << this << "\n";
	next = NULL;
}

NODE::~NODE()
{
	std::cout << "Megszuntem: " << this << "\n";
}

DynamicIntStack::DynamicIntStack()
{
	node = new NODE;
}

DynamicIntStack::~DynamicIntStack()
{
	while (node->next!=NULL) 
	{
		NODE* snode = node->next;
		delete node;
		node = snode;
	}
	delete node;
}

bool DynamicIntStack::isEmpty()
{
	return (node->next==NULL);
}

int DynamicIntStack::top()
{
	if (node->next==NULL) {throw std::exception(); return 0;}
	return node->value;
}

int DynamicIntStack::pop()
{
	if (node->next==NULL) {throw std::exception(); return 0;}
	int value = node->value;
	NODE* snode = node->next;
	delete node;
	node = snode;
	return value;
}

void DynamicIntStack::push(int value)
{
	NODE* snode = new NODE;
	snode->value = value;
	snode->next = node;
	node = snode;
}

void DynamicIntStack::print()
{
	NODE* snode = node;
	while (snode->next!=NULL)
	{
		std::cout << snode->value << " ";
		snode = snode->next;
	}
}

