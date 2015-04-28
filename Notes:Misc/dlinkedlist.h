#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "node.h"

using namespace std;

enum DIRECTION{SMALLEST, LARGEST};

template<typename T>
class dLinkedList
{
    public:
        dLinkedList();
        ~dLinkedList();
        dLinkedList(T data, int qty=1);
        dLinkedList(const dLinkedList<T> &other);
        dLinkedList<T>& operator=(const dLinkedList<T> &other);

        bool full();
        bool empty();
        void clear();
        int nodeQty();
        int dataQty();
        DIRECTION& printDirection();
        void insert(const T &data, int qty = 1);
        void getData(DIRECTION dir, T &data, int &qty); // Pull first item off of the list
        int find(const T &data);
        void remove(const T &data, int qty = 1);
        dLinkedList<T>& operator<<(const T &data);
        dLinkedList<T>& operator>>(T &data);

        template<typename U>
        friend
        ostream& operator<<(ostream& out, dLinkedList<U> &list);

        template<typename U>
        friend
        istream& operator>>(istream& in, dLinkedList<U> &list);


    private:
        node<T> *front, *back, *middle;
        int nodeTotal,dataTotal, leftCount, rightCount;
        DIRECTION printDir;

        void copy(const dLinkedList<T> &other);
        void balance();
        void nukem();

        void insert(node<T> &newNode);

};

template<T>
dLinkedList<T>::dLinkedList()
{
    front = back = middle = NULL;
    nodeTotal = dataTotal = leftCount = rightCount = 0;
}

template<T>
dLinkedList<T>:~dLinkedList()
{
    nukem();
}

template<T>
dLinkedList<T>::dLinkedList(T data, int qty)
{
    node<T> *newNode = new node<T>(data,qty);
    insert(*newNode);
}

template<T>
dLinkedList<T>::dLinkedList(const dLinkedList<T> &other)
{
    copy(other);
}

template<T>
dLinkedList<T>& dLinkedList<T>::operator=(const dLinkedList<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<T>
bool dLinkedList<T>::full()
{
    return false;
}

template<T>
bool dLinkedList<T>::empty()
{
    return !front;
}

template<T>
void dLinkedList<T>::clear()
{
    nukem();
}

template<T>
int dLinkedList<T>::nodeQty()
{
    return nodeTotal;
}

template<T>
int dLinkedList<T>::dataQty()
{
    return dataTotal;
}

template<T>
DIRECTION& dLinkedList<T>::printDirection()
{
    return printDir;
}

template<T>
void dLinkedList<T>::insert(const T &data, int qty)
{
    node<T> *newNode = new node<T>(data, qty);
    insert(*newNode);
}

template<T>
void dLinkedList<T>::getData(DIRECTION dir, T &data, int &qty); // Pull first item off of the list

template<T>
int dLinkedList<T>::find(const T &data);


template<T>
void dLinkedList<T>::remove(const T &data, int qty = 1);

template<T>
dLinkedList<T>& dLinkedList<T>::operator<<(const T &data)
{
    node<T> *newNode = new node<T>(data);
    insert(*newNode);
    return *this;
}

template<T>
dLinkedList<T>& dLinkedList<T>::operator>>(T &data);

template<T>
void dLinkedList<T>::copy(const dLinkedList<T> &other)
{

}

template<T>
void dLinkedList<T>::balance()
{

}

//Friends
template<typename U>
ostream& operator<<(ostream& out, dLinkedList<U> &list)
{

}

template<typename U>
istream& operator>>(istream& in, dLinkedList<U> &list)
{
    node<T> *newNode = new node<T>;
    while(in>>*newNode)
        list.insert(newNode);
    return in;
}

#endif // DLINKEDLIST_H
