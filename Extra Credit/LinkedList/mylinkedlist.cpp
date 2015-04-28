#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "mylinkedlist.h"
#include "linkedList.h"

using namespace std;

myLinkedList::myLinkedList()
{
    tol = NULL;
    qty = 0;
}


myLinkedList::myLinkedList(void* &d, int amt)
{
    tol = new node(d, amt);
    // qty = amt;
}


myLinkedList::myLinkedList(const myLinkedList &other)
{
    copy(other);
}


myLinkedList::~myLinkedList()
{
    nukem(tol);
}


myLinkedList& myLinkedList::operator=(const myLinkedList &other)
{
    if(this != &other)
    {
        nukem(tol);
        copy(other);
    }
    return *this;
}


bool myLinkedList::find(void* data)
{
    node  *tmp = new node , *tmp2;
    tmp->next = tol;
    tmp2 = find(tmp, data);
    delete tmp;
    return tmp2;
}


bool myLinkedList::empty()
{
    /*
    if(tol == NULL)
        return true;
    else
        return false;
    */
    return !tol;
}


int myLinkedList::removeAll()
{
    nukem(tol);
    tol = NULL;
    int total = qty;
    qty = 0;
    return total;
}


int myLinkedList::quantity()
{
    return qty;
}


int myLinkedList::dataQty()
{
    int sum = 0;
    for(node  *tmp = tol; tmp; tmp=tmp->next)
        sum+=tmp->count;
    return sum;
}


int myLinkedList::quantity(void* &data)      // Number of a particular data item in the linked list
{
    node *tmp = find(tol, data);
    /*
      if(tmp)
         return tmp->next->count;
      else
         return 0;
    */
    return tmp ? tmp->next->count : 0;
}


void myLinkedList::insert(void* data, int amt)
{
    node *newTol= new node;
    newTol->next = tol;
    node *mover = newTol;
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
            node *newGuy = new node(data, amt);
            newGuy->next = mover->next;
            mover->next = newGuy;
            qty++;
        }
    }
    tol = newTol->next;
    delete newTol;
}


void myLinkedList::remove(void* data, int amt)
{
    node  *newTol = new node ;
    newTol->next = tol;
    node  *byeBye = find(newTol, data);
    if(byeBye)
        if((byeBye->next->count -= amt < 1))
        {
            node *nuked = byeBye->next;
            byeBye->next = byeBye->next->next;
            delete nuked;
            qty--;
        }
    tol = newTol->next;
    delete newTol;
}


myLinkedList& myLinkedList::operator<<(void* &data) // insertion operator
{
    insert(data);
    return *this;
}


myLinkedList& myLinkedList::operator>>(void* &data)// extraction operator
{
    if(empty())
        throw 403;
    data = tol->data;
    if(--tol->count < 1)
    {
        node *tmp = tol;
        tol = tol->next;
        delete tmp;
   }
   return *this;
}

ostream& operator<<(ostream &out, myLinkedList &list)
{
    node* tmp = list.tol;
    for(;tmp != NULL; tmp = tmp->next)
        out<<tmp->data<<"["<<tmp->count<<"] ";
    return out;
}

istream& operator>>(istream &in, myLinkedList &list)
{
    void* data;
    int qty=1;
    char junk;
    while(in>>data)
    {
        in>>junk>>data>>junk;
        list.insert(data, qty);
    }
    return in;
}



void myLinkedList::copy(const myLinkedList &other)
{
    node *tmp = other.tol;
    for(; tmp != NULL; tmp = tmp->next)
        insert(tmp->data,tmp->count);
}


void myLinkedList::nukem(node* &ptr) //delete entire list
{
    /*
    if(ptr)
    {
        nukem(ptr->next);
        delete ptr;
    }
    */
    ptr ? nukem(ptr->next) : delete ptr;
}


node * myLinkedList ::find(node * ptr, void* item)
{
    for(; ptr != NULL; ptr = ptr->next)
        if(ptr->next->data == item)
            return ptr;
    return NULL;
}
