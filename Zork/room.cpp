/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include "room.h"

room::room()
{
    //ctor
}

room::room(string n, string s)  // Create room with name and script
{
    name = n;
    script = s;
}

room::~room()
{
    //dtor
}

string room::getName()          // Return name
{
    return name;
}

void room::setName(string val)  // Set room name
{
    name = val;
}

string room::getScript()        // Get room script
{
    return script;
}

void room::setScript(string val)// Set room script
{
    script = val;
}

void room::displayRoom()        // Display room
{
    if( !hiddenItems.empty())   // Display room items
    {
        cout << "Items in this room: ";
        for(unsigned int i = 0; i < hiddenItems.size(); i++)
            cout <<"\n\t"<< hiddenItems[i] << endl;
    }
    cout << endl;
}

void room::setHiddenItem(string val)
{                               // Add item to hiddenItems
    hiddenItems.push_back(val);
}

string room::getHiddenItem(int &index)
{                               // Get item at index
    return hiddenItems[index];
}

ostream& operator<<(ostream& out, room& x)
{                               // Cout room info
    out << x.name << endl
        << x.script <<endl;
    return out;
}

bool room::findItem(string &val, int &index)
{
    for(unsigned int i = 0; i < hiddenItems.size(); i++)
    {
        if(hiddenItems[i] == val)
        {
            index = i;
            return true;
        }
    }
    return false;
}

void room::removeItem(int i)
{
    hiddenItems.erase(hiddenItems.begin()+i);
}
