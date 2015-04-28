#ifndef DERIVED_H
#define DERIVED_H
#include "base.h"

class derived : public base
{
    public:
        derived(int x = 5);
        ~derived();

        char& operator[](int x);

    private:
};

class derived2 : public base
{
    public:
        derived2(int x = 5);
        ~derived2();

        int& operator[](int x);

    private:
};

#endif // DERIVED_H
