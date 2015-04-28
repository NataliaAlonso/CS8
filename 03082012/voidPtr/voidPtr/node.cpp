#include "node.h"
#include <cstdlib>

using namespace std;

node::node()
{
    data = NULL;
}

node::~node()
{
}


node& node::operator=(void *dptr)
{
    data = dptr;
    return *this;
}
