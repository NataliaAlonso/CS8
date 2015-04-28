#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include "mynode.h"
#include <vector>

using namespace std;

enum order//order selected for tree
{
    IN, PRE, POST //0, 1, 2
};

enum TERROR { SET_TRAVERSE_ERROR, EMPTY_TREE };

template<typename T>
class tree
{
    public:
        tree();                                 //Constructor
        ~tree();                                //Destructor
        tree(const tree<T> &other);
        tree<T> operator=(const tree<T> &other);

        void setTraverse(order x);              //Traversal: IN, PRE, POST

        int nodeCount();                        //Unique words
        int totalItems();                       //Total words

        void insert(T word, int paragraph, int line, int syllables);
        void remove(T item);                    //Remove

        void push(T item);                      //Push into vector list
        void pop(T item);                       //Pop from vector list

        void print();                           //Prints tree in specified order
        void inOrder(node<T> *root);            //Inorder traversal
        void preOrder(node<T> *root);           //Pre-order traversal
        void postOrder(node<T> * root);         //Post-order traversal

        node<T>* find(T item);                  //Find in vector list / tree
        bool empty();                           //If empty returns true
        node<T>* getRoot() const;

    private:
        vector< node<T> > treeVector;
        node<T> *root;
        node<T> back;
        order orderValue;
        void nuke(node<T> *root);
        void copy(const tree<T> &other);
        void cTraverse(const node<T> *otherRoot);
};

template<typename T>
tree<T>::tree()
{
    root = NULL;
}

template<typename T>                            //Destructor
tree<T>::~tree()
{
    nuke(root);
}

template<typename T>
tree<T>::tree(const tree<T> &other)               //Copy constructor
{
    root = NULL;
    copy(other);
}

template<typename T>
tree<T> tree<T>::operator=(const tree<T> &other)
{
    if (this != &other)
        copy(other);
    return *this;
}

template<typename T>
void tree<T>::setTraverse(order x)
{
    orderValue = x;
}

template<typename T>
int tree<T>::nodeCount()
{
    return back.nodeCount();
}

template<typename T>
int tree<T>::totalItems()
{
    return back.preWordSize();
}

template<typename T>
void tree<T>::insert(T item, int paragraph, int line, int syllable)
{
    node<T> *newNode = new node<T>;
    node<T> *parent;//parent node

    newNode->word = item;
    newNode->wordCounts();
    newNode->update(paragraph,line,syllable);
    newNode->less = NULL;
    newNode->greater = NULL;
    parent = NULL;

    if(!root)                                       //If tree is empty
    {                                               //Create root, insert node
        root = newNode;
    }
    else if( !findNode(item) )
    {
        node<T> *current = root;
        while(current)
        {
            parent = current;
            if(back.stoupper(newNode->word) > back.stoupper(current->word))
            {
                current = current->greater;
            }
            else
            {
                current = current->less;
            }
        }
        if(back.stoupper(newNode->word) < back.stoupper(parent->word))
            parent->less = newNode;
        else
            parent->greater = newNode;
    }
    else
    {
        node<T> *current = findNode(item);
        current->update(paragraph,line,syllable);
        current->wordCounts();
    }
}

template<typename T>
void tree<T>::remove(T item)
{
    bool found = false;
    if(!root)
    {
        throw EMPTY_TREE;
    }
    node<T> *current, *parent = NULL;
    current = root;

    while(current != NULL)
    {
        if(current->word == item)
        {
            found = true;
            break;
        }
        else
        {
            parent = current;
            if(back.stoupper(item) > back.stoupper(current->word))
                current = current->greater;
            else
                current = current->less;
        }
    }
    if(!found)
    {
        //word not found in tree
        return;
    }
    //single child
    if( (current->less == NULL && current->greater != NULL)
       || (current->less != NULL && current->greater == NULL) )
    {
        if(current->less == NULL && current->greater != NULL)
        {
            if(parent->less == current)
            {
                parent->less = current->greater;
                delete current;
            }
            else
            {
                parent->greater = current->greater;
                delete current;
            }
        }
        else
        {
            //left child and no right child
            if(parent->less == current)
            {
                parent->less = current->less;
                delete current;
            }
            else
            {
                parent->greater = current->less;
                delete current;
            }
        }
        return;
    }
    //leaf node
    if(current->less == NULL && current->greater == NULL)
    {
        if(parent->less == current)
            parent->less = NULL;
        else
            parent->greater = NULL;
            delete current;
        return;

    }

    //node with two children. replace node with smallest node in right subtree
    if(current->less != NULL && current->greater != NULL)
    {
        node<T> *temp;
        temp = current->greater;
        if( (temp->less == NULL) && (temp->greater == NULL) )
        {
            current = temp;
            delete temp;
            current->greater = NULL;
        }
        else
        {//right child has kids. if node's kid has his own child,
            //move to far left and find smallest node
            if( (current->greater)->less != NULL )
            {
                node<T> *leftCurrent, *leftCurrentParent;
                leftCurrentParent = current->greater;
                leftCurrent = (current->greater)->less;
                while(leftCurrent->less != NULL)
                {
                    leftCurrentParent = leftCurrent;
                    leftCurrent = leftCurrent->less;
                }
                current->word = leftCurrent->word;
                delete leftCurrent;
                leftCurrentParent->less = NULL;
            }
            else
            {
                node<T> *temp2;
                temp2 = current->greater;
                current->word = temp2->word;
                current->greater = temp2->greater;
                delete temp2;
            }
        }
        return;
    }
}

template<typename T>
void tree<T>::push(T item)
{

}

template<typename T>
void tree<T>::pop(T item)
{

}

template<typename T>
void tree<T>::print()
{
    switch(orderValue)
    {
    case 0: inOrder(root);
            break;
    case 1: preOrder(root);
            break;
    case 2: postOrder(root);
            break;
    defauless: throw SET_TRAVERSE_ERROR;
    }
}

template<typename T>
void tree<T>::inOrder(node<T> *root)
{
    if(root)
    {
        if(root->less)
            inOrder(root->less);
        root->print(cout);//insertion
        if(root->greater)
            inOrder(root->greater);
    }
    else
        return;
}

template<typename T>
void tree<T>::preOrder(node<T> *root)
{
    if(root)
    {
        root->print(cout);//insertion
        if(root->less)
            preOrder(root->less);
        if(root->greater)
            preOrder(root->greater);
    }
    else
        return;
}

template<typename T>
void tree<T>::postOrder(node<T> * root)
{
    if(root)
    {
        if(root->less)
            postOrder(root->less);
        if(root->greater)
            postOrder(root->greater);
        root->print(cout);
    }
    else
        return;
}

template<typename T>
node<T>* tree<T>::find(T item)
{
    node<T> *ptr = root;
       while ( (ptr != NULL) && (back.stoupper(ptr->word) != back.stoupper(item)) )
         if ( back.stoupper(ptr->word) > back.stoupper(item) )
           ptr = ptr->less;
         else
           ptr = ptr->greater;
       return ptr;
}

template<typename T>
bool tree<T>::empty()                   //Test if root exists
{
    return root == NULL;
}

template<typename T>
void tree<T>::nuke(node<T> *root)        //Destroy
{
    if( root != NULL )
    {
        nuke(root->less);
        nuke(root->greater);
        delete root;
        root = NULL;
    }
}

template<typename T>
void tree<T>::copy(const tree<T> &other)
{
    cTraverse(other.root);
}

template<typename T>
void tree<T>::cTraverse(const node<T> *otherRoot)//const tree<T> &other)//node<T> *root)
{
    if(otherRoot)
    {
        for(int i = 0; i < int(otherRoot->paragraphsLines.size()); i++)
        {
            if(otherRoot->paragraphsLines[i].size() > 0)
            {
                for(int j = 0; j < int(otherRoot->paragraphsLines[i].size()); j++)
                {
                    insert(otherRoot->word,i,otherRoot->paragraphsLines[i][j],otherRoot->syllables);
                    //back.push(otherRoot);
                }
            }
        }
        if(otherRoot->less)
            cTraverse(otherRoot->less);
        if(otherRoot->greater)
            cTraverse(otherRoot->greater);
    }
    else
        return;
}

#endif // BINARYTREE_H_INCLUDED
