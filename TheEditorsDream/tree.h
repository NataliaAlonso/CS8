/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "mynode.h"
#include <vector>
#include <fstream>

template<typename T>
class tree
{
    public:
        tree();                                             // Default constructor
        tree(T &data);                                      // Constructor with data
        ~tree();                                            // Destructor
        tree(const tree<T> &other);                         // Copy constructor
        tree<T>& operator=(const tree<T> &other);           // Assignment operator

        int height(int i);                                  // Returns height of node
        int sizeOf();                                       // Return size
        bool empty();                                       // Return if empty
        void push(T &data);                                 // Push data into tree
        void insert(T &data, int &nodeRoot, int &parent);   // Insert data
        void remove(T data, int nodeRoot, int parent);      // Remove data
        bool contains(T data, int root);                    // Return if contains an element
        void display(ofstream& outFile, int i);             // Display
        void print(ofstream& outFile);                      // Print to file
        void rotateWithLeftChild(int &k2);
        void rotateWithRightChild(int &k1);
        void doubleWithLeftChild(int &k3);
        void doubleWithRightChild(int &k3);

        friend
        ostream& operator<<(ostream& out, tree<T>& x);

    private:
        vector< node<T> > treeVector;                       // Vector for data
        int root;                                           // Index of root
        int size;                                           // Size of tree
        void copy(const tree<T> &other);                    // Copy tree
        void nuke(int nodeRoot);                            // Delete tree
        int findMin(int nodeRoot);                          // Find min value
        int findMax(int nodeRoot);                          // Find max value
};

template<typename T>
tree<T>::tree()
{
    root = -1;
    size = 0;
}

template<typename T>
tree<T>::tree(T &data)
{
    node<T> newNode(data);
    treeVector.resize(256);
    treeVector[0]=newNode;
    root = 0;
    size++;
    newNode.left = -1;
    newNode.right = -1;
}

template<typename T>
tree<T>::~tree()
{
    nuke(root);
}

template<typename T>
tree<T>::tree(const tree<T> &other)
{
    root = -1;
    copy(other);
}

template<typename T>
tree<T>& tree<T>::operator=(const tree<T> &other)
{
    if (this != &other)
        copy(other);
    return *this;
}

template<typename T>
int tree<T>::height(int i)
{
    return i == -1 ? -1 : treeVector[i].height;
}



template<typename T>
int tree<T>::sizeOf()
{
    return size;
}

template<typename T>
bool tree<T>::contains(T data, int nodeRoot)                            // Check if tree contains data
{
    if(data == NULL)                                                    // If data is NULL return false
        return false;
    else if(data < treeVector[nodeRoot].data)                           // If data is less than root
        return contains(data,treeVector[treeVector[root].left]);        // Recurse left
    else if(data > treeVector[nodeRoot].data)                           // If data is greater than root
        return contains(data,treeVector[treeVector[nodeRoot].right]);   // Recurse right
    else                                                                // Eventually either data does not exist FALSE
        return true;                                                    // Or it does, TRUE
}

template<typename T>                                                    // Return if empty
bool tree<T>::empty()
{
    return size == 0;
}

template<typename T>
void tree<T>::push(T &data)                                             // Start with parent = -1
{                                                                       // Insert data from root
    int negOne = -1;
    insert(data,root,negOne);
}

template<typename T>
void tree<T>::insert(T &data, int &nodeRoot, int &parent)               // Insert with root, parent
{
    if((unsigned)parent > (treeVector.capacity()-1)/2)                  // If needed, resize vector
        treeVector.resize(2*treeVector.capacity());
    if(nodeRoot == -1)                                                  // If root is -1 (either empty tree,
    {                                                                   // or at a leaf
        node<T> newNode(data);                                          // Create new node
        if(parent == -1 || data <= treeVector[parent].data)             // If data is first node or less than parent
        {
            int index = 2*parent+1;                                     // Index = left child
            if(parent == -1)                                            // But if first node
            {                                                           // Set index and root to 0
                index = 0;
                root = 0;
            }
            treeVector[index] = newNode;                                // Insert node to vector
            if(parent != -1)                                            // Set parent left child to new node index
                treeVector[parent].left = index;
            if( height(treeVector[parent].left) - height(treeVector[parent].right) == 2)
            {
                if(data < treeVector[treeVector[parent].left].data)
                    {rotateWithLeftChild(parent);}
                else
                    {doubleWithLeftChild(parent);}
            }
        }
        else                                                            // Other wise index = right child
        {
            int index = 2*parent+2;                                     // Insert node to vector
            treeVector[index] = newNode;                                // Set parent right child to new node index
            treeVector[parent].right = index;
            if( height(treeVector[parent].right) - height(treeVector[parent].left) == 2)
            {
                if(data > treeVector[treeVector[parent].right].data)
                    {rotateWithRightChild(parent);}
                else
                    {doubleWithRightChild(parent);}
            }
        }
        size++;                                                         // Increment size
        treeVector[parent].height = max(height(treeVector[parent].left), height(treeVector[parent].right)) + 1;
        return;
    }
    if(data <= treeVector[nodeRoot].data)                               // If not an empty tree or at a leaf
        insert(data,treeVector[nodeRoot].left, nodeRoot);               // If data less than nodeRoot, recurse left
    else if(data > treeVector[nodeRoot].data)                           // Else
        insert(data,treeVector[nodeRoot].right, nodeRoot);              // Recurse right
}

template<typename T>
void tree<T>::remove(T data, int nodeRoot, int parent)
{
    vector< node<T> > shiftemp(treeVector.size);
    if(nodeRoot == -1)                                                  // Item not found
        return;
    if(data < treeVector[nodeRoot].data)                                // If data less than nodeRoot, recurse left
        remove(data,treeVector[treeVector[nodeRoot].left], nodeRoot);
    else if(data > treeVector[nodeRoot].data)                           // Else
        remove(data,treeVector[treeVector[nodeRoot].right], nodeRoot);  // Recurse right
    else if(treeVector[treeVector[nodeRoot].left] != -1 && treeVector[treeVector[nodeRoot].right] != -1)
    {                                                                   // If no children
        treeVector[nodeRoot].data = treeVector[findMin(treeVector[nodeRoot].right)].data;
        remove(data,treeVector[nodeRoot].right, nodeRoot);
    }
    else
    {
        treeVector[nodeRoot] = (treeVector[nodeRoot].left != -1) ? treeVector[nodeRoot*2]:treeVector[(nodeRoot*2)+1];
    }
}

template<typename T>                                                    // Delete tree
void tree<T>::nuke(int nodeRoot)
{
    if( nodeRoot != -1 )                                                // If nodeRoot is not a leaf
    {
        nuke(treeVector[nodeRoot].left);                                // Recurse left
        nuke(treeVector[nodeRoot].right);                               // Then recurse right
        nodeRoot = -1;                                                  // Set all indexes to point to -1
    }
}

template<typename T>
int tree<T>::findMin(int nodeRoot)
{
    if(nodeRoot == -1)                                                  // If root is -1, tree is empty
        return NULL;                                                    // Return NULL
    if(treeVector[nodeRoot].left == -1)                                 // Otherwise, if left child is leaf
        return nodeRoot;                                                // Return nodeRoot
    return findMin(treeVector[nodeRoot].left);                          // Other wise recurse left
}

template<typename T>
int tree<T>::findMax(int nodeRoot)
{
    if(nodeRoot != -1)                                                  // If not a leaf
        while(treeVector[nodeRoot].right != -1)                         // While not a leaf
            nodeRoot = treeVector[nodeRoot].right;                      // Iterate right
    return nodeRoot;                                                    // Return nodeRoot
}

template<typename T>
void tree<T>::display(ofstream& outFile, int root)
{
    if(treeVector[root].left != -1)                                     // If not a leaf
        display(outFile,treeVector[root].left);                         // Recurse left

    outFile << "Data " << treeVector[root].data << endl;                // Display data

    if(treeVector[root].right != -1)                                    // If not a leaf
        display(outFile,treeVector[root].right);                        // Recurse right
}

template<typename T>
void tree<T>::print(ofstream& outFile)
{
    display(outFile, root);                                             // Display to file
}

template<typename T>
void tree<T>::rotateWithLeftChild(int &k2)
{
    int k1 = treeVector[k2].left;
    treeVector[k2].left = treeVector[k1].right;
    treeVector[k1].right = k2;
    treeVector[k2].height = max( height( treeVector[k2].left ), height( treeVector[k2].right ) ) + 1;
    treeVector[k1].height = max( height( treeVector[k1].left ), treeVector[k2].height ) + 1;
    treeVector[k2] = treeVector[k1];
}

template<typename T>
void tree<T>::rotateWithRightChild(int &k1)
{
    int k2 = treeVector[k1].right;
    treeVector[k1].right = treeVector[k2].left;
    treeVector[k2].left = k1;
    treeVector[k1].height = max( height( treeVector[k1].right ), height( treeVector[k1].left ) ) + 1;
    treeVector[k2].height = max( height( treeVector[k2].right ), treeVector[k1].height ) + 1;
    treeVector[k1] = treeVector[k2];
}

template<typename T>
void tree<T>::doubleWithLeftChild(int &k3)
{
    rotateWithRightChild( treeVector[k3].left );
    rotateWithLeftChild( k3 );
}

template<typename T>
void tree<T>::doubleWithRightChild(int &k3)
{
    rotateWithLeftChild( treeVector[k3].right );
    rotateWithRightChild( k3 );
}

#endif // TREE_H_INCLUDED
