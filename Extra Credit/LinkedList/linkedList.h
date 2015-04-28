#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "node.h"

using namespace std;

class linkedList
{
    public:
        linkedList();
        virtual ~linkedList();

    private:
        node* list;
        int qty;
};
#endif // LINKEDLIST_H
