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
        node<T>* find(T &data);
        void insert(node<T> &newNode);

};

template<typename T>
dLinkedList<T>::dLinkedList()
{
    front = back = middle = NULL;
    nodeTotal = dataTotal = leftCount = rightCount = 0;
}

template<typename T>
dLinkedList<T>::~dLinkedList()
{
    nukem();
}

template<typename T>
dLinkedList<T>::dLinkedList(T data, int qty)
{
    node<T> *newNode = new node<T>(data,qty);
    insert(*newNode);
}

template<typename T>
dLinkedList<T>::dLinkedList(const dLinkedList<T> &other)
{
    copy(other);
}

template<typename T>
dLinkedList<T>& dLinkedList<T>::operator=(const dLinkedList<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename T>
bool dLinkedList<T>::full()
{
    return false;
}

template<typename T>
bool dLinkedList<T>::empty()
{
    return !front;
}

template<typename T>
void dLinkedList<T>::clear()
{
    nukem();
}

template<typename T>
int dLinkedList<T>::nodeQty()
{
    return nodeTotal;
}

template<typename T>
int dLinkedList<T>::dataQty()
{
    return dataTotal;
}

template<typename T>
DIRECTION& dLinkedList<T>::printDirection()
{
    return printDir;
}

template<typename T>
void dLinkedList<T>::insert(const T &data, int qty)
{
    node<T> *newNode = new node<T>(data, qty);
    insert(*newNode);
}

template<typename T>
void dLinkedList<T>::getData(DIRECTION dir, T &data, int &qty) // Pull first item off of the list
{
    if( dir == SMALLEST &&back)
    {
       data = back->data;
       qty = back->count;
       remove(data,qty);
    }
    else
    {
        data = back->data;
        qty = back->count;
        remove(data,qty);
    }
}

template<typename T>
int dLinkedList<T>::find(const T &data)
{
    node<T> *ptr = find(data);
    return ptr ? ptr->count : 0;
}

template<typename T>
node<T>* dLinkedList<T>::find(T &data)
{
    node<T>*ptr, *stop;
    if(data == middle->data)
        return middle;
    if(data < middle->data)
    {
        stop = middle;
        ptr = front;
    }
    else
    {
        stop = back;
        ptr = middle;
    }
    for(;ptr && (ptr->data != data && ptr != stop); ptr = ptr->next);
    return ptr->data == data ? ptr : NULL;

}

template<typename T>
void dLinkedList<T>::remove(const T &data, int qty)
{
    node<T> *ptr = find(data);
    if( (ptr->count-= qty) < 1)
    {
        if(ptr == front)
        {
            front = ptr->next;
            front->prev = NULL;
            leftCount--;
        }
        else
            if(ptr == back)
            {
                back = ptr->prev;
                back->next = NULL;
                rightCount--;
            }
            else
            {
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                    if(ptr->data < middle->data)
                        leftCount--;
                    else
                        rightCount--;
             }
        balance();
        delete ptr;
    }
}

template<typename T>
dLinkedList<T>& dLinkedList<T>::operator<<(const T &data)
{
    node<T> *newNode = new node<T>(data);
    insert(*newNode);
    return *this;
}

template<typename T>
dLinkedList<T>& dLinkedList<T>::operator>>(T &data)
{
    remove(data);
    return *this;
}

template<typename T>
void dLinkedList<T>::copy(const dLinkedList<T> &other)
{
   front = middle = back = NULL;
   nodeTotal = 0;
   dataTotal = 0;
   leftCount = 0;
   rightCount = 0;
   for(node<T> *ptr; ptr; ptr = ptr->next)
   {
       node<T> *newNode = new node<T>(*ptr);
       insert(*newNode);
   }
}

template<typename T>
void dLinkedList<T>::balance()
{
   if( abs(leftCount - rightCount) > 1)
       if(leftCount > rightCount)
       {
           middle = middle->prev;
           leftCount--;
           rightCount++;
       }
       else
       {
           middle = middle->next;
           leftCount++;
           rightCoount--;
       }
}

//Friends
template<typename U>
ostream& operator<<(ostream& out, dLinkedList<U> &list)
{
    for(node<T> *ptr = list.front; ptr ; ptr = ptr->next)
        out<<*ptr;
    return out;
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
