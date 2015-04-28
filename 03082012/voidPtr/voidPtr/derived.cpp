#include "derived.h"

derived::derived(int x)
{
    resize(x);
    for(int i=0; i<x; i++)
      access(i) = new char;
}

derived::~derived(){}

char& derived::operator[](int x)
{
      try
      {
            return *(char *)access(x).data;
      }
      catch(...)
      {
          cout<<"Illegal array index"<<endl;
      }
}


derived2::derived2(int x)
{
    resize(x);
    for(int i=0; i<x; i++)
      access(i) = new int;
}

derived2::~derived2(){}

int& derived2::operator[](int x)
{
      try
      {
            return *(int *)access(x).data;
      }
      catch(...)
      {
          cout<<"Illegal array index"<<endl;
      }
}

