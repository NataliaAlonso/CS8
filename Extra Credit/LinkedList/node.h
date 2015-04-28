#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>

struct node
{
    void* data;
    int count;
    node *next;

    node();
    node(const node &other);
    node(void* &d,int qty = 1);
    ~node();

    node& operator=(const node &other);
};

#endif // NODE_H
