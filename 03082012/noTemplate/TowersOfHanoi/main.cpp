#include <iostream>
#include <ctime>
#include "Disk.h"
#include "Board.h"

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
         << "\nPlease many disks would you like to solve:                 " <<endl;
    cin >> size;
    while ( size >= 100 )
    {
        cout << "I don't have enough time for this. Choose again. >:(" <<endl;
        cin >> size;
    }
    Board game(size);
    game.startGame();

    time(&end);
    cout<< "\n\nTime elapsed: " << (double)difftime(end, start) << " seconds."<< endl;

    return 0;
}
