/*
Title: Towers of Hanoi Iterative Solution with Stack and Queue Options
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include <iostream>
#include <ctime>
#include "disk.h"
#include "board.h"

using namespace std;

int main()
{
    time_t start, end;
    time(&start);
    int size;

    cout << "|=-=-=-=-=-=-=-= Welcome to Towers of Hanoi! =-=-=-=-=-=-=-=|" <<endl
         << "There are three pegs, labeled A, B, and C from left to right." <<endl
         << "  The game begins with peg A holding n disks size 1 to n in  " <<endl
         << " descending order. The objective is to move the entire tower " <<endl
         << " of disks from the first peg to the last peg, one disk at a  " <<endl
         << "time, without placing a larger disk on top of a smaller disk." <<endl
         << " The most efficient solution to a game with n # of disks is  " <<endl
         << "        (2^n)-1 total moves. I will demonstrate this.        " <<endl
         << "\nPlease many disks would you like to solve (3+):            " <<endl;

    cin >> size;
    while(size < 3 || size > 20)
    {
        cout << "Invalid selection. Please re-enter." <<endl;;
        cin >> size;
    }
    Board game(size);
    cout << "Please enter S for stack or Q for queue." <<endl;
    char choice;
    cin >> choice;
    game.startGame(choice);
    time(&end);
    cout<< "\nTime elapsed: " << (double)difftime(end, start) << " seconds."<< endl;

    return 0;
}
