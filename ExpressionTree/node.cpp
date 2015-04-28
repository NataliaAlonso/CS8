#include "node.h"

node::node()
{
    //ctor
}

node::~node()
{
    //dtor
}

node::node(const node& other)
{
    //copy ctor
}

node& node::operator=(const node& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
