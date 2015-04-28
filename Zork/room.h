/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef ROOM_H
#define ROOM_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class room
{
    public:
        room();                                 // Default constructor
        room(string n, string s);               // Constructor with name and script parameters
        virtual ~room();                        // Destructor

        string getName();                       // Get room name
        void setName(string val);               // Set room name
        string getScript();                     // Get room script
        void setScript(string val);             // Set the room script

        void displayRoom();                     // Display the room name and script

        string getHiddenItem(int &index);       // Return hiddenItem at index
        void setHiddenItem(string val);         // Add item to hiddenItem
        bool findItem(string &val, int &index); // Find item in hiddenItem
        void removeItem(int i);                 // Remove item from hiddenItem

        friend                                  // Extraction operator
        ostream& operator<<(ostream& out, room& x);

    protected:

    private:
        string name;                            // Room name
        string script;                          // Room script
        vector<string> hiddenItems;             // Item vector
};

#endif // ROOM_H
