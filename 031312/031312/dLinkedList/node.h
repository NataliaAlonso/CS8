#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

template<typename T>
struct node
{
    T data;
    int count;
    node<T> *prev, *next;

    node();
    ~node();
    node(T input, int qty = 1);

    node(const node<T> &other);
    node<T>& operator=(const node<T> &other);

    void copy(const node<T> &other);

    template<typename U>
    friend
    ostream& operator<<(ostream& out, node<U> &me);

    template<typename U>
    friend
    istream& operator>>(istream& in, node<U> &me);
};

template<typename T>
node<T>::node()
{
    prev = next = NULL;
    count = 0;
}

template<typename T>
node<T>::~node()
{
    prev = next = NULL;
}

template<typename T>
node<T>::node(T input, int qty)
{
    data = input;
    count = qty;
    prev = next = NULL;
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename T>
void node<T>::copy(const node<T> &other)
{
    data = other.data;
    count = other.count;
    next = prev = NULL;
}



template<typename U>
ostream& operator<<(ostream& out, node<U> &me)
{
    out<<me.data<<"["<<me.count<<"] ";
    return out;
}

template<typename U>
istream& operator>>(istream& in, node<U> &me)
{
   char junk;
   in>>me.data>>junk>>me.count>>junk;
   me.next = me.prev = NULL;
   return in;
}

#endif // NODE_H
