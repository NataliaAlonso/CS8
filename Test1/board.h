/*
Title: Towers of Hanoi Iterative Solution with Stack and Queue Options
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef BOARD_H
#define BOARD_H
#include "Disk.h"
#include "mystack.h"
#include "myqueue.h"
#include <fstream>
#include <cstdlib>

using namespace std;

class Board
{
    public:
        Board(int size);                                                // Constructor
        void displayMove(Disk &d, string &s);                           // Displays move "Disk &d -> Peg &p"
        void startGame(char c);                                         // Starts game, switch on c, S for stack, Q for queue

        //Stack Functions
        Disk createDisk(stack<Disk> &stk, stack<Disk> &temp, int size); // Create starting stack with n = size disks
        void oddGame();                                                 // Stack game for odd n disks
        void evenGame();                                                // Stack game for even n disks
        bool checkStack(char peg);                                      // Check if stack is empty
        void moveLeft(char &c);                                         // Move stack game disk left
        void moveRight(char &c);                                        // Move stack game disk right
        void moveDiskLeft(char pegArray[], int d);                      // Move stack game disk left according to location in pegArray
        void moveDiskRight(char pegArray[], int d);                     // Move stack game disk right according to location in pegArray
        void evenMoveSequence(char pegArray[], ofstream &outfile);      // Even move sequence for Disk 1-3 for stack game
        void oddMoveSequence(char pegArray[], ofstream &outfile);       // Odd move sequence for Disk 1-3 for stack game


        //Queue Functions
        Disk qcreateDisk(queue<Disk> &stk, queue<Disk> &tmp, int size); // Create starting queue with n = size disks
        void qoddGame();                                                // Queue game for odd n disks
        void qevenGame();                                               // Queue game for even n disks
        bool checkQueue(char peg);                                      // Check if queue is empty
        void qmoveLeft(char &c);                                        // Move queue game disk left
        void qmoveRight(char &c);                                       // Move queue game disk right
        void qmoveDiskLeft(char pegArray[], int d);                     // Move queue game disk left according to location in pegArray
        void qmoveDiskRight(char pegArray[], int d);                    // Move queue game disk right according to location in pegArray
        void qevenMoveSequence(char pegArray[], ofstream &outfile);     // Even move sequence for Disks 1-3 for queue game
        void qoddMoveSequence(char pegArray[], ofstream &outfile);      // Odd move sequence for Disks 1-3 for queue game

    private:
        stack<Disk> start, temp, end;                                   // Pegs for stack game
        queue<Disk> qstart, qtemp, qend;                                // Pegs for queue game
        int disks, lastDisk, totalMoves;                                // Disk, totalMoves counters
        int parity;                                                     // 0 for even, 1 for odd
};

#endif // BOARD_H
