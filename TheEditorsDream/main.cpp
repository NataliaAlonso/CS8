/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include <fstream>
#include <string>
#include <iostream>
#include "tree.h"
#include "myheap.h"
#include "word.h"
#include <cstdlib>

using namespace std;

int main()
{
    int p = 1;
    int l = 2;
    int s = 3;

    tree<int> newTree;
    newTree.push(p);
    newTree.push(l);
    newTree.push(s);


/*
    myheap<int> newHeap;
    newHeap.push(s);
    newHeap.push(p);
    newHeap.push(l);

    ofstream outfile ("output.txt");
    newHeap.print(outfile);
    outfile.close();                                    // Close file
    system("start output.txt");
    */
}
