#ifndef STACK_H
#define STACK_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "TNode.h"

using namespace std;

template<typename T>
class Stack
{
    public:
        Stack(int size = 5);
        ~Stack();
        Stack<T>& operator=(Stack<T> &other);

        void clear();                       //Dump stack
        int size();                         //How many itmes in the stack
        int getStackSize();                 //returns the stack size

        bool push(T data);                  //Push data on stack
        bool pop();                         //Pop data off stack

        T peek();                           //See first item in stack
        bool isEmpty();                     //Is stack empty
        bool isFull();                      //Is stack full
                                            //std functions
        bool empty();
        T top();

    private:
        TNode<T> *head;
        int stackSize, stackQty;
        void copy(Stack<T> &other);
        void recurse(Stack<T> *ptr);

};

template<typename T>                        // Constructor
Stack<T>::Stack(int size)
{
	stackSize = size;
	stackQty = 0;
	head = NULL;

}

template<typename T>                        // Destructor
Stack<T>::~Stack()
{
   clear();
}

template<typename T>                        // Assignment operator
Stack<T>& Stack<T>::operator=(Stack<T> &other)
{
	if(this != &other)
		copy(other);
	return *this;
}

template<typename T>                        // Clear stack
void Stack<T>::clear()
{
	if( stackSize )
	{
		TNode<T> *temp;
		while( head )
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		head = NULL;
		stackSize = 0;
		stackQty = 0;
	}
}

template<typename T>                        // Return stackQty
int Stack<T>::size()
{
	return stackQty;
}

template<typename T>                        // Return stackSize
int Stack<T>::getStackSize()
{
	return stackSize;
}

template<typename T>                        // Resize stack
void Stack<T>::resize(int size) {
	clear();
	stackSize = size;
}

template<typename T>                        // Push
bool Stack<T>::push(T data)
{
	if (!(isFull()))
	{
		TNode<T> *temp = new TNode<T>(data);
		temp->next = head;
		head = temp;
		stackQty++;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>                        // Pop
bool Stack<T>::pop()
{
	if (!(isEmpty()))
	{
		TNode<T> *temp = head;
		head = head->next;
		delete temp;
		stackQty--;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>                        // isEmpty
bool Stack<T>::isEmpty()
{
	if(stackQty == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>                        // isFull
bool Stack<T>::isFull()
{
	if(stackQty == stackSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>                        // Empty
bool Stack<T>::empty()
{
	if(stackQty == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>                        // Top
T Stack<T>::top()
{
	if (!(isEmpty()))
	{
		return head->data;
	}
	else
	{
		return NULL;
	}
}

template<typename T>                        // Copy stack
void Stack<T>::copy(Stack<T> &other)
{
	stackSize = other.stackSize;
	stackQty = other.stackQty;
	head = NULL;
	recurse(other.head);
}

template<typename T>                        // Recurse
void Stack<T>::recurse(Stack<T> *ptr)
{
	if (!ptr)
	{
		recurse(ptr->next);
	}
	push(ptr->data);
}

#endif //STACK_H
