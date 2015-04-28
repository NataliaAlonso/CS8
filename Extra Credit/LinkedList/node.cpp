#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "node.h"

node::node()
{
    next = NULL;
    count = 0;
}

node::node(const node &other)
{
    data = other.data;
    count = other.count;
    next = other.next;
}

node::node(void* &d, int qty)
{
    data = d;
    count = qty;
    next = NULL;
}

node::~node()
{
    next = NULL;
    count = 0;
}

node& node::operator=(const node &other)
{
    if(this != &other)
    {
        data = other.data;
        count = other.count;
        next = NULL;
    }
    return *this;
}

