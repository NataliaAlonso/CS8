#include "base.h"

base::base(int x)
{
    list = new node[x];
    size = x;
}

base::~base()
{
    delete [] list;
}

void base::resize(int x)
{
    delete [] list;
    list = new node[size=x];
}


node& base::access(int x)
{
    if(x < 0 || x>=size)
        throw 999;
    return list[x];
}
