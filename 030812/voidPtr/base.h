#ifndef BASE_H
#define BASE_H
#include "node.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class base
{
    public:
      base(int x = 5);
      ~base();

      void resize(int x);
      node& access(int x);

    private:
      node *list;
      int size;
};

#endif // BASE_H
