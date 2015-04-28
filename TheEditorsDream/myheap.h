/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef MYHEAP_H_INCLUDED
#define MYHEAP_H_INCLUDED
#include "mynode.h"
#include <vector>
#include <fstream>

template<typename T>
class myheap
{
    public:
        myheap();                                           //Default constructor
        myheap(const T &data);                              //Constructor with data
        ~myheap();                                          //Destructor
        myheap(const myheap<T> &other);                     //Copy constructor
        myheap<T>& operator=(const myheap<T> &other);       //Assignment operator
        int sizeOf();                                       //Return size
        bool findMin(T &data);                              //Find min
        bool empty();                                       //Return if empty
        void push(T data);                                  //Push data
        void insert(T &data, int &nodeRoot, int &parent);   //Insert data
        void remove(T &data, int &nodeRoot, int &parent);   //Remove data
        void swap(int &i,int &c);                           //Swap up
        void display(ofstream& outFile, int root);          //Display
        void print(ofstream& outFile);                      //Print to file

    private:
        vector< node<T> > myheapVector;                     //Data vector
        int root;                                           //Root index
        int current;                                        //Current index
        void copy(const myheap<T> &other);                  //Copy heap
        void nuke(int &root);                               //Delete heap
};

template<typename T>
myheap<T>::myheap()
{
    root = -1;
    current = -1;
}

template<typename T>
myheap<T>::myheap(const T &data)
{
    node<T> newNode(data);
    myheapVector.resize(256);
    myheapVector[0]=newNode;
    root = 0;
    current = 0;
    newNode.left = -1;
    newNode.right = -1;
}

template<typename T>
myheap<T>::~myheap()
{
    nuke(root);
}

template<typename T>
myheap<T>::myheap(const myheap<T> &other)
{
    root = -1;
    copy(other);
}

template<typename T>
myheap<T>& myheap<T>::operator=(const myheap<T>& other)
{
    if (this != &other)
        copy(other);
    return *this;
}

template<typename T>
int myheap<T>::sizeOf()
{
    return current;
}

template<typename T>
bool myheap<T>::empty()
{
    return root == NULL;
}

template<typename T>
void myheap<T>::push(T data)
{
    int negOne = -1;
    insert(data,root,negOne);
}

template<typename T>
void myheap<T>::insert(T &data, int &nodeRoot, int &parent)
{
    node<T> newNode(data);                                      //Create new node with data
    myheapVector.push_back(newNode);                            //Push back to vector
    current++;                                                  //Increment current
    if(current > 0)                                             //If current is greater than 0
    {
        int parent = (current-1)/2;                             //Parent is (current-1)/2
        swap(current,parent);                                   //Check for swap of parent and child
    }
}

template<typename T>
void myheap<T>::remove(T &data, int &nodeRoot, int &parent)
{
    //Remove
}

template<typename T>
void myheap<T>::copy(const myheap<T> &other)
{
    current = other.current;
    root = other.root;
    myheapVector = other.myheapVector;
}

template<typename T>
void myheap<T>::nuke(int &root)
{
    if( root != -1 )
    {
        nuke(myheapVector[root].left);
        nuke(myheapVector[root].right);
        root = -1;
    }
}

template<typename T>
void myheap<T>::swap(int &child, int &parent)
{
    if(myheapVector[child] < myheapVector[parent])                  //Check if parent is greater than child
    {
        //cout << "Swapping!" <<endl
        //cout << myheapVector[i].data <<endl;
        node<T> temp(myheapVector[child].data);                     //If so, create temp
        myheapVector[child] = myheapVector[parent].data;            //Swap data from parent to child
        myheapVector[parent] = temp;                                //Swap data from child to parent
        if(child%2)                                                 //If current is odd
            myheapVector[parent].left = child;                      //Child becomes parent's left child
        else                                                        //Else
            myheapVector[parent].right = child;                     //Child become parent's right child
        int grandpa = (parent-1)/2;                                 //Assign parent's parent
        swap(parent, grandpa);                                      //Check from swap up
    }
}

template<typename T>
void myheap<T>::display(ofstream& outFile, int root)
{
    if(myheapVector[root].left != -1)                               //If not a leaf
        display(outFile,myheapVector[root].left);                   //Recurse left

    outFile << "Data " << myheapVector[root].data << endl;          //Display data

    if(myheapVector[root].right != -1)                              //If not a leaf
        display(outFile,myheapVector[root].right);                  //Recurse right
}

template<typename T>
void myheap<T>::print(ofstream& outFile)
{
    display(outFile, root);                                         //Display file
}


#endif // MYHEAP_H_INCLUDED
