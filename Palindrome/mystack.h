/*
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef MYSTACK_H
#define MYSTACK_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "mynode.h"

using namespace std;

template<typename T>
class stack
{
    public:
        stack();
		stack(const T &d);
        ~stack();
        stack<T>& operator=(stack<T> &other);
		stack(const stack<T> &other);

        void clear(node<T>* &ptr);
        int sizeOf();
        void push(T data);
        void pop();
        T top();
        bool empty();

    private:
        node<T> *tol;
        int size;
        void copy(stack<T> &other);
};

template<typename T>                        // Constructor
stack<T>::stack()
{
	tol = NULL;
	size = 0;
}

template<typename T>                        // Constructor
stack<T>::stack(const T &d)
{
	tol = new node<T>(d);
	size++;
}

template<typename T>                        // Destructor
stack<T>::~stack()
{
   clear(tol);
}

template<typename T>                        // Assignment operator
stack<T>& stack<T>::operator=(stack<T> &other)
{
	if(this != &other)
	{
		clear(tol);
		copy(other);
	}
	return *this;
}

template<typename T>                        // Copy constructor
stack<T>::stack(const stack<T> &other)
{
	copy(other);
}

template<typename T>                        // Clear stack
void stack<T>::clear(node<T>* &ptr)
{
	ptr ? clear(ptr->next) : delete ptr;
}

template<typename T>
int stack<T>::sizeOf()
{
	return size;
}

template<typename T>                        // Push
void stack<T>::push(T data)
{
	node<T> *temp = new node<T>(data);
	temp->next = tol;
	tol = temp;
	size++;
}

template<typename T>                        // Pop
void stack<T>::pop()
{
	node<T> *temp = tol;
	tol = tol->next;
	delete temp;
	size--;
}

template<typename T>                        // Top
T stack<T>::top()
{
    return tol->data;
}

template<typename T>
bool stack<T>::empty()
{
    if(size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>                        // Copy stack
void stack<T>::copy(stack<T> &other)
{
	node<T> *tmp = other.tol;
	for(;tmp != NULL; tmp=tmp->next)
		push(tmp->data);
}

#endif //MYSTACK_H
