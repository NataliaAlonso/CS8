#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "node.h"

using namespace std;

template<typename T>
class linkList
{
    public:
        linkList();
        linkList(const T &d, int qty = 1);
        linkList(const linkList<T> &other);
        ~linkList();
        linkList<T>& operator=(const linkList<T> &other);

        bool find(T data);
        bool empty();
        int removeAll();
        int quantity();
        int quantity(T &data);
        void insert(T data, int qty = 1);
        void remove(T data, int qty = 1);

        linkList<T>& operator<<(T &data); // insertion operator
        linkList<T>& operator>>(T &data);// extraction operator

        template<typename U>
        friend
        ostream& operator<<(ostream &out, linkList<U> &list);template<typename U>

        template<typename U>
        friend
        istream& operator>>(istream &in, linkList<U> &list);


    private:
        node<T>* tol;
        int qty;

        void copy(const linkList<T> &other);
        void nukem(node<T>* &ptr); //delete entire list
        node<T>* find(node<T>* ptr, T item);
};


template<typename T>
linkList<T>::linkList()
{
    tol = NULL;
    qty = 0;
}

template<typename T>
linkList<T>::linkList(const T &d, int amt)
{
    tol = new node<T>(d, qty);
    qty = amt;
}

template<typename T>
linkList<T>::linkList(const linkList<T> &other)
{
    copy(other);
}

template<typename T>
linkList<T>::~linkList()
{
    nukem(tol);

}

template<typename T>
linkList<T>& linkList<T>::operator=(const linkList<T> &other)
{
    if(this != &other)
    {
        nukem(tol);
        copy(other);
    }
    return *this;
}

template<typename T>
bool linkList<T>::find(T data)
{
    node<T> *tmp = new node, *tmp2;
    tmp->next = tol;
    tmp2 = find(tmp, data);
    delete tmp;
    return tmp2;
}

template<typename T>
bool linkList<T>::empty();

template<typename T>
int linkList<T>::removeAll();

template<typename T>
int linkList<T>::quantity();

template<typename T>
int linkList<T>::quantity(T &data);

template<typename T>
void linkList<T>::insert(T data, int qty = 1);

template<typename T>
void linkList<T>::remove(T data, int qty = 1);

template<typename T>
linkList<T>& operator<<(T &data); // insertion operator

template<typename T>
linkList<T>& linkList<T>::operator>>(T &data);// extraction operator

template<typename U>
ostream& operator<<(ostream &out, linkList<U> &list)
{
    node<T>* tmp = list.tol;
    for(;tmp != NULL; tmp = tmp->next)
        out<<tmp->data<<"["<<tmp->count<<"] ";
    return out;
}


template<typename U>
istream& operator>>(istream &in, linkList<U> &list)
{
    U data;
    int qty;
    char junk;
    while(in>>data)
    {
        in>>junk>>data>>junk;
        list.insert(data, qty);
    }
    return in;
}


template<typename T>
void linkList<T>::copy(const linkList<T> &other)
{
    node<T> *tmp = other.tol;
    for(; tmp != NULL; tmp = tmp->next)
        insert(tmp->data,tmp->count);
}

template<typename T>
void linkList<T>::nukem(node<T>* &ptr) //delete entire list
{
    if(ptr != NULL)
    {
        nukem(ptr->next);
        delete ptr;
    }
}

template<typename T>
node<T>* linkList<T>::find(node<T>* ptr, T item)
{
    for(; ptr != NULL; ptr = ptr->next)
        if(ptr->next->data == item)
            return ptr;
    return NULL;
}

#endif // LINKEDLIST_H
