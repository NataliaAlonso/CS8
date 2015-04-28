#include "palindrome.h"
#include <iostream>
#include "mystack.h"
#include <string>
#include <cstdlib>

bool performPal(stack<char> &characters, string s)      // Performs check for palindrome and returns boolean value
{
        string temp, revline, line;                     // Create strings to handle input
        temp = revline = "";
        line = s;
        for(unsigned int i = 0; i < line.size(); i++)   // Convert characters to uppercase for comparison
        {
            temp += toupper(line[i]);
            characters.push(toupper(line[i]));
        }
        while(!characters.empty())                      // Reverses line in order to compare strings
        {
            revline += characters.top();
            characters.pop();
        }

        if ( revline.length() > 1)                      // If line is greater than one character, return comparison
            return revline == temp;
        else
            return false;
}
