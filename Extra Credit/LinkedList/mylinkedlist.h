#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "node.h"
#include "linkedList.h"

using namespace std;

class myLinkedList : public linkedList
{
    public:
        myLinkedList();
        myLinkedList(void* &d, int amt = 1);
        myLinkedList(const myLinkedList &other);
        ~myLinkedList();
        myLinkedList& operator=(const myLinkedList &other);

        bool find(void* data);
        bool empty();
        int removeAll();
        int quantity();
        int quantity(void* &data);
        int dataQty();
        void insert(void* data, int amt = 1);
        void remove(void* data, int amt = 1);
        virtual void accessData(void * &data){};

        myLinkedList& operator<<(void* &data); // insertion operator
        myLinkedList& operator>>(void* &data); // extraction operator

        friend
        ostream& operator<<(ostream &out, myLinkedList &list);

        friend
        istream& operator>>(istream &in, myLinkedList &list);

    private:
		node* tol;
        int qty; // Number of nodes in linked list
        void copy(const myLinkedList &other);
        void nukem(node* &ptr); //delete entire list
        node* find(node* ptr, void* item);
};

#endif // MYLINKEDLIST_H
