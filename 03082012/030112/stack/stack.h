#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

enum ERROR {FULL, EMPTY};

template<typename T>
class myStack
{
  public:
    myStack(int qty = 5);
    ~myStack();
    myStack(const myStack<T> &other);
    myStack<T>& operator=(const myStack<T> &other);

    T& top();
    T& pop();
    void push(const T &data);
    int size();
    void resize(int qty);
    void clear();
    bool empty();
    bool full();

    myStack<T>& operator<<(const T & data);
    myStack<T>& operator>>(T &data);

    template<typename U>
    friend
    ostream& operator<<(ostream& out, myStack<T> &stack);


    template<typename U>
    friend
    istream& operator>>(istream& in, myStack<T> &stack);

  private:
    int size, tos;
    T* theStack;

    void copy(const myStack<T> &other);
};

template<typename T>
myStack<T>::myStack(int qty)
{
    theStack = new T[size = qty];
    tos = -1;
}

template<typename T>
myStack<T>::~myStack()
{
    delete [] theStack;
}

template<typename T>
myStack<T>::myStack(const myStack<T> &other)
{
    copy(other);
}

template<typename T>
myStack<T>& myStack<T>::operator=(const myStack<T> &other)
{
    if(this != &other)
    {
        delete [] theStack;
        copy(other);
    }
    return *this;
}

template<typename T>
T& myStack<T>::top()
{
    return theStack[tos];
}

template<typename T>
T& myStack<T>::pop()
{
    if(empty())
        throw EMPTY;
    T temp = theStack[tos--];
    return temp;
}

template<typename T>
void myStack<T>::push(const T &data)
{
    if(full())
        throw FULL;
    theStack[++tos] = data;
}

template<typename T>
int myStack<T>::size()
{
    return size;
}

template<typename T>
void myStack<T>::resize(int qty)
{
    delete [] theStack;
    theStack = new T[size = qty];
}


template<typename T>
void  myStack<T>::clear()
{
    tos = -1;
}


template<typename T>
bool myStack<T>::empty()
{
    return tos < 0;
}

template<typename T>
bool myStack<T>::full()
{
    return tos == size-1;
}


template<typename T>
myStack<T>& myStack<T>::operator<<(const T & data)
{
    push(data);
    return *this;
}


template<typename T>
myStack<T>& myStack<T>::operator>>(T &data)
{
    data = pop();
    return *this;
}

template<typename U>
ostream& operator<<(ostream& out, myStack<T> &stack)
{
    out<<"Stack size = "<<stack.size<<endl
       <<"Current top of stack = "<<stack.tos<<endl;
    for(int i = 0; i < stack.tos; i++)
        out<<stack[i]<<endl;
    return out;
}


template<typename U>
istream& operator>>(istream& in, myStack<T> &stack)
{
    stringstream ss;
    string line;
    int intVal;
    U data;
    if(in>>line)
    {
        ss<<line.substr(line.find("=")+1, string::npos);
        ss>>intVal;
        stack.resize();
        in>>line;
        ss<<line.substr(line.find("=")+1, string::npos);
        ss>>intVal;
        stack.tos = intVal;
        while(in>>data)
            stack.push(data);
    }
    return in;
}

template<typename T>
void myStack<T>::copy(const myStack<T> &other)
{
    theStack = new T[size = other.size];
    for(int i =0; i < size; i++)
        theStack[i] = other.theStack[i];
    tos = other.tos;
}


#endif // STACK_H
