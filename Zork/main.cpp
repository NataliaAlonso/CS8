/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include "room.h"
#include "game.h"

using namespace std;

int main()
{
    game newGame;
    cout << "ZORK 0.5: HALF OF THE GREAT UNDERGROUND EMPIRE" <<endl
         << "Recreated 'halfway' by Natalia Alonso, CS8 Spring 2012" <<endl<<endl
         << "*  Your objective is to collect 5 treasures from the  *"<<endl
         << "* map and return them to the trophy case. Good luck!! *"<<endl
         << "*   Please enter movement with only letters N S E W   *"<<endl
         << "*      Other actions must be entered in the form      *"<<endl
         << "* VERB TARGET OBJECT, with no conjunctions or articles*"<<endl
         << "*     Example: 'add trophy egg' or 'open window'      *"<<endl
         << "*                                                     *"<<endl
         << "*  Please type 'diagnose' to view your health status  *"<<endl
         << "*                                                     *"<<endl
         << "* Recognized actions:                                 *"<<endl
         << "*\t\ttake\tdrop\tinventory             *"<<endl
         << "*\t\tadd\topen\tlook                  *"<<endl
         << "*\t\tkill\ttie\tring                  *"<<endl
         << "*\t\tlight\twave\tread                  *"<<endl
         << "*\t\tturn on                               *"<<endl<<endl<<endl;
    newGame.getRoomInfo(newGame.currentRoom);

    while(1)
    {
        newGame.checkTrophy();              // Check if trophy case is full
        string s = newGame.getInput();      // Otherwise get input
        if(s.length() == 1)                 // If user entered N S E W
        {
            char c = s[0];                  // Get char
            c = toupper(c);                 // Convert to upper
            newGame.move(c);                // Move in char direction
        }
        else                                // Otherwise
        {                                   // Perform action denoted by s
            newGame.checkCheat(s);
            newGame.action(s);
        }
    }
}
