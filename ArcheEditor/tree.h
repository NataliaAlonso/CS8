#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "words.h"
#include <string>
#include <vector>
#include <fstream>

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
        tree(const tree<T> &rhs);
        tree<T> operator=(const tree<T> &rhs);

        void setTraverse(order x);              //Traversal: IN, PRE, POST

        int nodeCount();                        //Unique words
        int totalItems();                       //Total words

        //void insert(T item);                  //insert into tree
        void insert(T word, int paragraph, int line, int syllables);
        void remove(T item);                    //Remove

        void push(T item);                      //Push into vector list
        void pop(T item);                       //Pop from vector list

        void print();                           //Prints tree in specified order
        void inOrder(node<T> *root);            //Inorder traversal
        void preOrder(node<T> *root);           //Pre-order traversal
        void postOrder(node<T> * root);         //Post-order traversal

        node<T>* findNode(T key);               //Find in vector list / tree
        bool isEmpty();                         //If empty returns true
        node<T>* getRoot() const;

    private:
        node<T> *root;
        words<T> backend;
        order orderValue;
        void destroy(node<T> *root);
        void copy(const tree<T> &other);
        void cTraverse(const node<T> *oRoot);   //node<T> *root);
};

template<typename T>
node<T>* tree<T>::getRoot() const
{
    return root;
}

template<typename T>
node<T>* tree<T>::findNode(T key)
{
    node<T> *ptr = root;
       while ( (ptr != NULL) && (back.stoupper(p->word) != back.stoupper(key)) )
         if ( back.stoupper(p->word) > back.stoupper(key) )
           ptr = ptr->less;
         else
           ptr = ptr->greater;
       return ptr;
}

template<typename T>                        //Constructor
tree<T>::tree()
{
    root = NULL;
}

template<typename T>                        //Destructor
tree<T>::~tree()
{
    destroy(root);
}

template<typename T>
void tree<T>::destroy(node<T> *root)        //Destroy
{
    if( root != NULL )
    {
        destroy(root->lt);
        destroy(root->gt);

        delete root;
        root = NULL;
    }
}

template<typename T>
bool tree<T>::isEmpty()                     //Test if root exists
{
    return root == NULL;
}

template<typename T>
tree<T>::tree(const tree<T> &rhs)           //Copy constructor
{
    root = NULL;
    copy(rhs);
}

template<typename T>
tree<T> tree<T>::operator=(const tree<T> &rhs)
{
    if (this != &rhs)
        copy(rhs);
    return *this;
}

template<typename T>
void tree<T>::copy(const tree<T> &other)
{
    cTraverse(other.getRoot());
}

template<typename T>
void tree<T>::cTraverse(const node<T> *oRoot)//const tree<T> &other)//node<T> *root)
{
    if(oRoot)
    {
        for(int i = 0; i < int(oRoot->paragrahsLines.size()); i++)
        {
            if(oRoot->paragrahsLines[i].size() > 0)
            {
                for(int j = 0; j < int(oRoot->paragrahsLines[i].size()); j++)
                {
                    insert(oRoot->word,i,oRoot->paragrahsLines[i][j],oRoot->syllables);
                    //backend.push(oRoot);
                }
            }
        }
        if(oRoot->lt)
            cTraverse(oRoot->lt);
        if(oRoot->gt)
            cTraverse(oRoot->gt);
    }
    else
        return;
}


template<typename T>
void tree<T>::setTraverse(order x)
{
    orderValue = x;
}

template<typename T>
int tree<T>::nodeCount()
{
    return backend.nodeCount();
}

template<typename T>
int tree<T>::totalItems()
{
    return backend.preWordSize();
}

template<typename T>
void tree<T>::insert(T item, int paragraph, int line, int syllable)
{
    node<T> *newNode = new node<T>;
    node<T> *parent;//parent node

    newNode->word = item;
    newNode->wordCounts();
    newNode->update(paragraph,line,syllable);
    newNode->lt = NULL;
    newNode->gt = NULL;
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
            if(backend.stoupper(newNode->word) > backend.stoupper(current->word))
            {
                current = current->gt;
            }
            else
            {
                current = current->lt;
            }
        }
        if(backend.stoupper(newNode->word) < backend.stoupper(parent->word))
            parent->lt = newNode;
        else
            parent->gt = newNode;
    }
    else
    {
        node<T> *current = findNode(item);
        current->update(paragraph,line,syllable);
        current->wordCounts();
    } 
}

template<typename T>
void tree<T>::push(T item)
{
    backend.push(item);
}

template<typename T>
void tree<T>::pop(T item)
{
    /*
    for (vector<string>::iterator i = preWordList.begin(); i != preWordList.end(); ++i)
    {
        if(*i == item)
            preWordList.erase(i);
    }*/
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
            if(backend.stoupper(item) > backend.stoupper(current->word))
                current = current->gt;
            else
                current = current->lt;
        }
    }
    if(!found)
    {
        //word not found in tree
        return;
    }
    //single child
    if( (current->lt == NULL && current->gt != NULL)
       || (current->lt != NULL && current->gt == NULL) )
    {
        if(current->lt == NULL && current->gt != NULL)
        {
            if(parent->lt == current)
            {
                parent->lt = current->gt;
                delete current;
            }
            else
            {
                parent->gt = current->gt;
                delete current;
            }
        }
        else
        {
            //left child and no right child
            if(parent->lt == current)
            {
                parent->lt = current->lt;
                delete current;
            }
            else
            {
                parent->gt = current->lt;
                delete current;
            }
        }
        return;
    }
    //leaf node
    if(current->lt == NULL && current->gt == NULL)
    {
        if(parent->lt == current)
            parent->lt = NULL;
        else
            parent->gt = NULL;
            delete current;
        return;

    }

    //node with two children. replace node with smallest node in right subtree
    if(current->lt != NULL && current->gt != NULL)
    {
        node<T> *temp;
        temp = current->gt;
        if( (temp->lt == NULL) && (temp->gt == NULL) )
        {
            current = temp;
            delete temp;
            current->gt = NULL;
        }
        else
        {//right child has kids. if node's kid has his own child,
            //move to far left and find smallest node
            if( (current->gt)->lt != NULL )
            {
                node<T> *leftCurrent, *leftCurrentParent;
                leftCurrentParent = current->gt;
                leftCurrent = (current->gt)->lt;
                while(leftCurrent->lt != NULL)
                {
                    leftCurrentParent = leftCurrent;
                    leftCurrent = leftCurrent->lt;
                }
                current->word = leftCurrent->word;
                delete leftCurrent;
                leftCurrentParent->lt = NULL;
            }
            else
            {
                node<T> *temp2;
                temp2 = current->gt;
                current->word = temp2->word;
                current->gt = temp2->gt;
                delete temp2;
            }
        }
        return;
    }
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
    default: throw SET_TRAVERSE_ERROR;
    }
}

template<typename T>
void tree<T>::inOrder(node<T> *root)
{
    if(root)
    {
        if(root->lt)
            inOrder(root->lt);
        root->print(cout);//insertion
        if(root->gt)
            inOrder(root->gt);
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
        if(root->lt)
            preOrder(root->lt);
        if(root->gt)
            preOrder(root->gt);
    }
    else
        return;
}

template<typename T>
void tree<T>::postOrder(node<T> * root)
{
    if(root)
    {
        if(root->lt)
            postOrder(root->lt);
        if(root->gt)
            postOrder(root->gt);
        root->print(cout);
    }
    else
        return;
}


#endif // TREE_H
