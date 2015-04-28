/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include "item.h"

item::item()
{
    //dtor
}

item::item(string n, string s)
{
    name = n;
    script = s;
    action = "";
}

item::~item()
{
    //dtor
}

item::item(const item& other)
{
    name = other.name;
    script = other.script;
    action = other.action;
}

item& item::operator=(const item& other)
{
    if(this == &other)
        return *this;

    name = other.name;
    script = other.script;
    action = other.action;
    return *this;
}

ostream& operator<<(ostream& out, item& x)
{
    out << x.name;
    return out;
}

string item::getScript()
{
    return script;
}
