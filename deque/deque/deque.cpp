#include "deque.h"

deque::deque()
{
    //ctor
}

deque::~deque()
{
    //dtor
}

deque::deque(const deque& other)
{
    //copy ctor
}

deque& deque::operator=(const deque& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
