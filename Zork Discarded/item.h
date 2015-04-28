/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <cstdlib>

using namespace std;

class item
{
    public:
        item();
        item(string n, string s);
        virtual ~item();
        item(const item& other);
        item& operator=(const item& other); // Assignment operator
        string getScript();

        friend
        ostream& operator<<(ostream& out, item& x);

    protected:
    private:
        string name;
        string script;
        string action;
};

#endif // ITEM_H
