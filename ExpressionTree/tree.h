#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class tree
{
    public:
        tree();
        tree(const T & data);
        ~tree();
        tree(const tree<T>& other);
        tree& operator=(const tree<T>& other);

        void buildTree(string &s);
        void evaluateTree();

        bool empty();

        node<T>* root;
};

template<typename T>
tree<T>::tree()
{
    root = NULL;
}

template<typename T>
tree<T>::tree(const T & data)
{
    node<T> *temp = new node<T>(data);
    root = temp;
}

template<typename T>
tree<T>::~tree()
{
    root = NULL;
}

template<typename T>
tree<T>::tree(const tree& other)
{
    root = other.root;
}

template<typename T>
tree<T>& tree<T>::operator=(const tree& other)
{
    if(this != &other)
	{
        root = other.root;
	}
	return *this;
}


template<typename T>
bool tree<T>::empty()
{
    return !root;
}

template<typename T>
void tree<T>::buildTree(string &s)
{
    vector< node<T>* > nodeVector;
    string op;
    while(s != "")
    {
        int pos = s.find_first_of(' ',0);
        op = s.substr(0,pos);
        s.erase(0,pos+1);
        if(isdigit(op[0]))
        {
            node<T> *newNode = new node<T>(op);
            nodeVector.push_back(newNode);
        }
        else
        {
            node<T> *temp = nodeVector.back();
            nodeVector.pop_back();
            root->right = temp;
            temp = nodeVector.back();
            nodeVector.pop_back();
            root->left = temp;
            nodeVector.push_back(root);
        }
    }
}

template<typename T>
void tree<T>::evaluateTree()
{

}

#endif // TREE_H
