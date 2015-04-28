#ifndef MYSTACK_H
#define MYSTACK_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "mynode.h"

using namespace std;

template<typename T>
class mystack
{
    public:
        mystack();
		mystack(const T &d);
        ~mystack();
        mystack<T>& operator=(mystack<T> &other);
		mystack(const mystack<T> &other);

        void erase();
        void clear(node<T>* &ptr);
        int sizeOf();
        void push(T data);
        void pop();
        T top();
        bool empty();
/*
        friend
        istream& operator>>(istream &in, mystack<T> &stack);
*/

    private:
        node<T> *tol;
        int size;
        void copy(mystack<T> &other);
};

template<typename T>                        // Constructor
mystack<T>::mystack()
{
	tol = NULL;
	size=0;
}

template<typename T>                        // Constructor
mystack<T>::mystack(const T &d)
{
	tol = new node<T>(d);
	size++;
}

template<typename T>                        // Destructor
mystack<T>::~mystack()
{
   clear(tol);
}

template<typename T>                        // Assignment operator
mystack<T>& mystack<T>::operator=(mystack<T> &other)
{
	if(this != &other)
	{
		clear(tol);
		copy(other);
	}
	return *this;
}

template<typename T>                        // Copy constructor
mystack<T>::mystack(const mystack<T> &other)
{
	copy(other);
}

template<typename T>                        // Clear mystack
void mystack<T>::clear(node<T>* &ptr)
{
	ptr ? clear(ptr->next) : delete ptr;
}

template<typename T>
int mystack<T>::sizeOf()
{
	return size;
}

template<typename T>                        // Push
void mystack<T>::push(T data)
{
	node<T> *temp = new node<T>(data);
	temp->next = tol;
	tol = temp;
	size++;
}

template<typename T>                        // Pop
void mystack<T>::pop()
{
	node<T> *temp = tol;
	tol = tol->next;
	delete temp;
	size--;
}

template<typename T>                        // Top
T mystack<T>::top()
{
    return tol->data;
}

template<typename T>
bool mystack<T>::empty()
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

template<typename T>                        // Copy mystack
void mystack<T>::copy(mystack<T> &other)
{
	node<T> *tmp = other.tol;
	for(;tmp != NULL; tmp=tmp->next)
		push(tmp->data);
}

/*

template<typename T>
istream& operator>>(istream &in, mystack<T> &stack)
{
    T temp;
    in >> temp;
    stack.push(temp);
    return in;
}*/

template<typename T>
void mystack<T>::erase()
{
    clear(tol);
}

#endif //MYSTACK_H
