/*
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include <iostream>
#include <cstdlib>
#include "mystack.h"
#include <string>
#include "palindrome.h"

using namespace std;

int main()
{
    while(1)
    {
        stack<char> characters;
        string input;
        cout << "Please enter a word and I will check if it is a palindrome!" <<endl
             << "> ";
        getline(cin,input);                                             // Words AND phrases

        if(performPal(characters, input))
            cout << input << " is a palindrome." << endl << endl;
        else
            cout << input << " in not a palindrome." << endl << endl;
    }
}
