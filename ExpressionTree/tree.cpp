#include "tree.h"

tree::tree()
{
    //ctor
}

tree::~tree()
{
    //dtor
}

tree::tree(const tree& other)
{
    //copy ctor
}

tree& tree::operator=(const tree& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
