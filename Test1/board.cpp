/*
Title: Towers of Hanoi Iterative Solution with Stack and Queue Options
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include "board.h"
#include "Disk.h"
#include "mystack.h"
#include "myqueue.h"
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Board::Board(int size)                              // Constructor
{
    totalMoves = 0;                                 // Set totalMoves to zero
    parity = size%2;                                // Set parity
    disks = size;                                   // Set disk count
    start = temp = end;                             // Initialize stacks
    qstart = qtemp = qend;                          // Initialize queues
}

void Board::moveLeft(char &c)                       // Move disk left from current location
{                                                   // c (location) to new location
    totalMoves++;                                   // Move disk left
                                                    // Remove disk from peg
    switch(c)
    {
        case 'A': c = 'C';
                  end.push(start.top());
                  start.pop();
                  break;
        case 'B': c = 'A';
                  start.push(temp.top());
                  temp.pop();
                  break;
        case 'C': c = 'B';
                  temp.push(end.top());
                  end.pop();
                  break;
    }
}

void Board::moveRight(char &c)                      // Move disk right from current location
{                                                   // c (location) to new location
    totalMoves++;                                   // Move disk right
                                                    // Remove disk from peg
    switch(c)
    {
        case 'A': c = 'B';
                  temp.push(start.top());
                  start.pop();
                  break;
        case 'B': c = 'C';
                  end.push(temp.top());
                  temp.pop();
                  break;
        case 'C': c = 'A';
                  start.push(end.top());
                  end.pop();
                  break;
    }
}

void Board::displayMove(Disk &d, string &s)         // Display moves
{
    cout << d << " moves to " << s << endl;
}

Disk Board::createDisk(stack<Disk> &stk, stack<Disk> &temp, int size)
{
    Disk newDisk;                                   // Create disk
    temp.push(newDisk);                             // Push first disk
    if(size > 1)                                    // If size > 1, which will always be the case
    {
        newDisk = createDisk(stk,temp,size-1);      // Recursively create disk n-1 through 1
    }
    stk.push(temp.top());                           // Push disks from temp to start to get them in order
    temp.pop();                                     // Pop from temp
}

void Board::startGame(char c)                       // Choose game
{
    switch(c)                                       // S for stack, Q for queue
    {
        case 's':
        case 'S': createDisk(start,end,disks);      // Create stack game
                  if(parity)                        // Choose parity
                    oddGame();
                  else
                    evenGame();
                  break;
        case 'q':
        case 'Q': qcreateDisk(qstart,qend,disks);   // Create queue game
                  if(parity)                        // Choose parity
                    qoddGame();
                  else
                    qevenGame();
                  break;
    }
}

void Board::oddGame()                               // Begin odd stack game
{
    ofstream outfile ("output.txt");                // Create output file
    outfile << "Solving for " << disks << " disks." <<endl <<endl;
    cout << "You chose " << disks << " disks." <<endl;

    char pegArray[disks+1];                         // Create array to track location of disks
    char A = 'A';                                   // Initiate location to A, first peg
    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    oddMoveSequence(pegArray,outfile);              // First odd move sequence
    while(totalMoves < (pow(2.0,disks)-1))          // While the totalMoves are less than required moves for n disks
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {                                           // If there are more than three disks
            for(int i = 1; i <= disks; i++)         // Check where next legal move is located
            {
                if((pegArray[i] != pegArray[1]) && !checkStack(pegArray[i]))
                {
                    if((i%2) == 0 )                 // If disk is even ordinal, move right
                    {
                        location = pegArray[i];
                        moveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else                            // Else move left
                    {
                        location = pegArray[i];
                        moveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        oddMoveSequence(pegArray,outfile);          // Repeat odd move sequence
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");                     // Open output file
    cout << "Total moves were: " << totalMoves <<endl;
}

void Board::evenGame()                              // Begin even stack game
{
    cout << "You chose " << disks << " disks." <<endl;
    ofstream outfile ("output.txt");                // Create output file
    outfile << "Solving for " << disks << " disks." <<endl <<endl;

    char pegArray[disks+1];                         // Create array to track location of disks
    char A = 'A';                                   // Initiate location to A, first peg
    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    evenMoveSequence(pegArray,outfile);             // First even move sequence

    while(totalMoves < (pow(2.0,disks)-1))          // While totalMoves is less than required moves for n disks
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {                                           // If there are more than 3 disks
            for(int i = 1; i <= disks; i++)         // Check where next legal move is located
            {
                if((pegArray[i] != pegArray[1]) && !checkStack(pegArray[i]))
                {
                    if((i%2) == 0 )                 // If disk is even ordinal, move left
                    {
                        location = pegArray[i];
                        moveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else                            // Else move right
                    {
                        location = pegArray[i];
                        moveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        evenMoveSequence(pegArray,outfile);         // Second even move sequence
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");                     // Open output file
    cout << "Total moves were: " << totalMoves <<endl;
}

bool Board::checkStack(char peg)                    // Check if stack is empty
{
    switch(peg)
    {
        case 'A': return start.empty();
        case 'B': return temp.empty();
        case 'C': return end.empty();
    }
}

void Board::oddMoveSequence(char pegArray[], ofstream &outfile)
{
	moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskLeft(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::evenMoveSequence(char pegArray[], ofstream &outfile)
{
	moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskRight(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::moveDiskLeft(char pegArray[], int d)
{
    char location;
	location = pegArray[d];                         // Get location of Disk d
	moveLeft(location);                             // Move disk
	pegArray[d] = location;                         // Set new location of disk
}

void Board::moveDiskRight(char pegArray[], int d)
{
    char location;
	location = pegArray[d];                         // Get location of Disk d
	moveRight(location);                            // Move disk
	pegArray[d] = location;                         // Set new location of disk
}


// Queue Functions
// These are indentical to stack functions, but using queues and queue syntax (enqueue for push, dequeue for pop).


Disk Board::qcreateDisk(queue<Disk> &stk, queue<Disk> &tmp, int size)
{
    Disk newDisk;
    tmp.enqueue(newDisk);
    if(size > 1)
    {
        newDisk = qcreateDisk(stk,tmp,size-1);
    }
    stk.enqueue(tmp.top());
    tmp.dequeue();
}

void Board::qoddGame()
{
    ofstream outfile ("output.txt");
    outfile << "Solving for " << disks << " disks." <<endl <<endl;
    cout << "You chose " << disks << " disks." <<endl;

    char pegArray[disks+1];
    char A = 'A';

    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    qoddMoveSequence(pegArray,outfile);
    while(totalMoves < (pow(2.0,disks)-1))
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {
            for(int i = 1; i <= disks; i++)
            {
                if((pegArray[i] != pegArray[1]) && !checkQueue(pegArray[i]))
                {
                    if((i%2) == 0 )
                    {
                        location = pegArray[i];
                        qmoveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else
                    {
                        location = pegArray[i];
                        qmoveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        qoddMoveSequence(pegArray,outfile);
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");
    cout << "Total moves were: " << totalMoves <<endl;

}

void Board::qevenGame()
{
    cout << "You chose " << disks << " disks." <<endl;
    ofstream outfile ("output.txt");
    outfile << "Solving for " << disks << " disks." <<endl <<endl;

    char pegArray[disks+1];
    char A = 'A';
    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    qevenMoveSequence(pegArray,outfile);

    while(totalMoves < (pow(2.0,disks)-1))
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {
            for(int i = 1; i <= disks; i++)
            {
                if((pegArray[i] != pegArray[1]) && !checkQueue(pegArray[i]))
                {
                    if((i%2) == 0 )
                    {
                        location = pegArray[i];
                        qmoveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else
                    {
                        location = pegArray[i];
                        qmoveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        qevenMoveSequence(pegArray,outfile);
    }
    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");
    cout << "Total moves were: " << totalMoves <<endl;
}

bool Board::checkQueue(char peg)
{
    switch(peg)
    {
        case 'A': return qstart.empty();
        case 'B': return qtemp.empty();
        case 'C': return qend.empty();
    }
}

void Board::qmoveLeft(char &c)
{
    totalMoves++;
    switch(c)
    {
        case 'A': c = 'C';
                  qend.enqueue(qstart.top());
                  qstart.dequeue();
                  break;
        case 'B': c = 'A';
                  qstart.enqueue(qtemp.top());
                  qtemp.dequeue();
                  break;
        case 'C': c = 'B';
                  qtemp.enqueue(qend.top());
                  qend.dequeue();
                  break;
    }
}

void Board::qmoveRight(char &c)
{
    totalMoves++;

    switch(c)
    {
        case 'A': c = 'B';
                  qtemp.enqueue(qstart.top());
                  qstart.dequeue();
                  break;
        case 'B': c = 'C';
                  qend.enqueue(qtemp.top());
                  qtemp.dequeue();
                  break;
        case 'C': c = 'A';
                  qstart.enqueue(qend.top());
                  qend.dequeue();
                  break;
    }
}

void Board::qoddMoveSequence(char pegArray[], ofstream &outfile)
{
	qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskLeft(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::qevenMoveSequence(char pegArray[], ofstream &outfile)
{
	qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskRight(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::qmoveDiskLeft(char pegArray[], int d)
{
    char location;
	location = pegArray[d];
	qmoveLeft(location);
	pegArray[d] = location;
}

void Board::qmoveDiskRight(char pegArray[], int d)
{
    char location;
	location = pegArray[d];
	qmoveRight(location);
	pegArray[d] = location;
}

