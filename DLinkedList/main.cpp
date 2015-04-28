#include <cstdlib>
#include <iostream>
#include "driver.h"
#include "dlinkedlist.h"

using namespace std;

void prompt(dLinkedList<char> &list);
void insertCharacter(dLinkedList<char> &list);
void removeCharacter(dLinkedList<char> &list);
void displayList(dLinkedList<char> &list);
void printDirection(dLinkedList<char> &list);
void findList(dLinkedList<char> &list);

int main()
{
    dLinkedList<char> temp;
    while(1)
    {
        prompt(temp);
    }

}

void prompt(dLinkedList<char> &list)
{
    char input;
    cout << "Please make a selection:" << endl
         << "D: Change print direction" << endl
         << "P: Print the list" << endl
         << "A: Add an item" << endl
         << "R: Remove an item" << endl
         << "F: Find an item" <<endl
         << "Q: Quit" <<endl <<endl
         << "Your selection: ";
         cin >> input;
         input = toupper(input);
    switch(input)
    {
        case 'D': printDirection(list);
                  break;
        case 'P': displayList(list);
                  break;
        case 'A': insertCharacter(list);
                  break;
        case 'R': removeCharacter(list);
                  break;
        case 'F': findList(list);
                  break;
        case 'Q': exit(0);
                  break;
        default: cout << "I don't understand your selection."<<endl;
    }
}

void insertCharacter(dLinkedList<char> &list)
{
    char input;
    cout << "What character would you like to insert?: ";
    cin >> input;
    list.insert(input,1);
    cout << endl<<endl;
}

void removeCharacter(dLinkedList<char> &list)
{
    char input;
    cout << "What character would you like to remove?: ";
    cin >> input;
    list.remove(input,1);
    cout << endl<<endl;
}

void displayList(dLinkedList<char> &list)
{
    cout << "Your list: " << list << endl<<endl;
}

void printDirection(dLinkedList<char> &list)
{
   if(list.printDirection() == ASCENDING)
   {
      cout<<"Print direction was ascending. It is now descending."<<endl<<endl;
      list.printDirection() = DESCENDING;
   }
   else
   {
      cout<<"Print direction was descending. It is now ascending."<<endl<<endl;
      list.printDirection() = ASCENDING;
   }
}

void findList(dLinkedList<char> &list)
{
    char input;
    cout << "Which character would you like to see a count of?:";
    cin >> input;
    int count = list.find(input);
    cout << "\n" << count << " " << input << "'s in the list."<<endl<<endl;

}

