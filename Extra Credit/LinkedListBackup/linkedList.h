#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "node.h"

using namespace std;

template<typename T>
class linkList
{
    public:
        linkList();
        linkList(const T &d, int amt = 1);
        linkList(const linkList<T> &other);
        ~linkList();
        linkList<T>& operator=(const linkList<T> &other);

        bool find(T data);
        bool empty();
        int removeAll();
        int quantity();
        int quantity(T &data);
        int dataQty();
        void insert(T data, int amt = 1);
        void remove(T data, int amt = 1);
        T top();

        linkList<T>& operator<<(T &data); // insertion operator
        linkList<T>& operator>>(T &data); // extraction operator

        template<typename U>
        friend
        ostream& operator<<(ostream &out, linkList<U> &list);

        template<typename U>
        friend
        istream& operator>>(istream &in, linkList<U> &list);

    private:
		node<T>* tol;
        int qty; // Number of nodes in linked list
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
    tol = new node<T>(d, amt);
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
    node<T>  *tmp = new node<T> , *tmp2;
    tmp->next = tol;
    tmp2 = find(tmp, data);
    delete tmp;
    return tmp2;
}

template<typename T>
bool linkList<T>::empty()
{
    return !tol;
}

template<typename T>
int linkList<T>::removeAll()
{
    nukem(tol);
    tol = NULL;
    int total = qty;
    qty = 0;
    return total;
}

template<typename T>
int linkList<T>::quantity()
{
    return qty;
}

template<typename T>
int linkList<T>::dataQty()
{
    int sum = 0;
    for(node<T>  *tmp = tol; tmp; tmp=tmp->next)
        sum+=tmp->count;
    return sum;
}

template<typename T>
int linkList<T>::quantity(T &data)      // Number of a particular data item in the linked list
{
    node<T> *tmp = find(tol, data);
    return tmp ? tmp->next->count : 0;
}

template<typename T>
void linkList<T>::insert(T data, int amt)
{
    node<T> *newTol= new node<T>;
    newTol->next = tol;
    node<T> *mover = newTol;
    mover->next = newTol->next;
    cout << mover->next<<endl;
    for(; mover->next && (mover->next->data <= data); mover=mover->next)
    cout << mover->next <<endl;
    if(mover->data == data)                     // If data is equal to current data, increment counter
        mover->count+= amt;
    else                                        // Otherwise, if mover is at end of list or if next data
    {                                           // is larger than current data, insert node
        if(!mover->next || (mover->next->data > data) )
        {
            node<T> *newGuy = new node<T>(data,amt);
            newGuy->next = mover->next;
            mover->next = newGuy;
            qty++;
        }
    }
    tol = newTol->next;
    delete newTol;
}

template<typename T>
void linkList<T>::remove(T data, int amt)
{
    node<T>  *newTol = new node<T> ;
    newTol->next = tol;
    node<T>  *byeBye = find(newTol, data);
    if(byeBye)
        if((byeBye->next->count -= amt < 1))
        {
            node<T> *nuked = byeBye->next;
            byeBye->next = byeBye->next->next;
            delete nuked;
            qty--;
        }
    tol = newTol->next;
    delete newTol;
}

template<typename T>
T linkList<T>::top()
{
    return tol->data;
}

template<typename T>
linkList<T>& linkList<T>::operator<<(T &data) // insertion operator
{
    insert(data);
    return *this;
}

template<typename T>
linkList<T>& linkList<T>::operator>>(T &data)// extraction operator
{
    if(empty())
        throw 403;
    data = tol->data;
    if(--tol->count < 1)
    {
        node<T> *tmp = tol;
        tol = tol->next;
        delete tmp;
   }
   return *this;
}

template<typename U>
ostream& operator<<(ostream &out, linkList<U> &list)
{
    node<U>* tmp = list.tol;
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
    ptr ? nukem(ptr->next) : delete ptr;
}

template<typename T>
node<T> * linkList<T> ::find(node<T> * ptr, T item)
{
    for(; ptr != NULL; ptr = ptr->next)
        if(ptr->next->data == item)
            return ptr;
    return NULL;
}

#endif // LINKEDLIST_H
