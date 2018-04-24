/*
 * linked_list.cpp
 *
 *  Created on: 20-Nov-2017
 *      Author: user
 */

#include <iostream>

struct Element
{
	Element(){};
	~Element(){};
	int key;
	Element* prev;
	Element* next;
};

class LinkedList
{
public:
	LinkedList()
	{
		head = nullptr;
	};
	~LinkedList(){};
	Element* head;
	void insert(int key)
	{
		Element* new_element = new Element();
		new_element->key = key;
		new_element->next = head;
		if(head!=nullptr)
		{
			(*head).prev = new_element;
		}
			new_element->prev = nullptr;
			head = new_element;
	};
};

int main()
{
	std::cout << "TEst";
	LinkedList l = LinkedList();
	l.insert(10);
}
