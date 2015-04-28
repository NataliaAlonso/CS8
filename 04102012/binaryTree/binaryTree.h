#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include "node.h"
using namespace std;

enum ORDER {INORDER, PREORDER, POSTORDER};
template<typename T>
class tree
{
    public:
        tree();
        ~tree();
        tree(const tree<T>& other);
        tree<T>& operator=(const tree<T>& other);

        void insert(const T &item);
        int clear();
        bool empty();
        bool remove(const T &item);
        bool find(const T &item);
        int depth();
        ORDER& printOrder();
        void display();
        int count();


        tree<T>& operator<<(const T& data);
        tree<T>& operator<<(node<T>& n);

        template<typename U>
        friend
        ostream& operator <<(ostream& out, tree<T>& t);

        template<typename U>
        friend
        istream& operator >>(istream& in, tree<T>& t);

    private:
        node<T> *root;
        ORDER print;

 //       void insert(node<T>& ptr, node<T> &newNode);
        void insert(node<T>* &ptr, node<T>* &newNode);
 //       void copy(const tree<T> &t);
        void copy(node<T> *ptr);
        void initialize();
        void nukem(node<T>* &ptr);
        int depth(node<T> *ptr);
        node<T>* find(node<T> *current, node<T> *item);
        void display(ostream& out, node<T>*ptr);
        int count(node<T> *ptr);

};


template<typename T>
tree<T>::tree()
{
    initialize();
}

template<typename T>
tree<T>::~tree()
{
    nukem(root);
}

template<typename T>
tree<T>::tree(const tree<T>& other)
{
    copy(other.root);
}

template<typename T>
tree<T>& tree<T>::operator=(const tree<T>& other)
{
    if(this != &other)
    {
        nukem(root);
        copy(other.root);
    }
    return *this;
}

template<typename T>
void tree<T>::nukem(node<T> *&ptr)
{
    if(ptr->lessThan)
        nukem(ptr->lessThan);
    if(ptr->greatThan)
        nukem(ptr->greatThan);
    delete ptr;
    ptr = NULL;
}

template<typename T>
void tree<T>::insert(const T &item)
{
    node<T> *ptr = new node<T>(item);
    insert(root, ptr);
}

template<typename T>
int tree<T>::clear()
{
    int qty = count(root);
    nukem(root);
    return qty;
}

template<typename T>
bool tree<T>::empty()
{
    return !root;
}

template<typename T>
int tree<T>::count()
{
    return count(root);
}


template<typename T>
int tree<T>::count(node<T> *ptr)
{
    return !ptr ? 0 : 1 + count(ptr->lessThan) + count(ptr->greatThan);
}

template<typename T>
bool tree<T>::remove(const T &item)
{
    node<T> *nukedNode;
    node<T> *masterParent = new node<T>;
    masterParent->lessThan = masterParent->greatThan = root;
    node<T> *toFind = new node<T>(item);
    node<T> *parent =  find(masterParent, toFind);

    if(parent->lessThan->data == item)
    {
        parent->lessThan->count--;
        if(parent->lessThan->count <= 0)
        {
           nukedNode = parent->lessThan;
           if(!nukedNode->lessThan && !nukedNode->greatThan)
           {
                //The one being blown away has no kids.
                parent->lessThan = NULL;
                delete nukedNode;
           }
           else
           {
                //Kids exist on one or both sides of the node that is being nuked
                if(!nukedNode->greatThan)
                {
                    parent->lessThan = nukedNode->lessThan;
                    delete nukedNode;
                }
                else
                  if(!nukedNode->lessThan)
                  {
                    parent->lessThan = nukedNode->greatThan;
                    delete nukedNode;
                  }
                  else
                  {
                      parent->lessThan = nukedNode->greatThan;
                      node<T> *greaterThanLessThan = nukedNode->greatThan;
                      for(;greaterThanLessThan->lessThan; greaterThanLessThan = greaterThanLessThan->lessThan);
                      greaterThanLessThan->lessThan = nukedNode->lessThan;
                      delete nukedNode;
                  }
           }
        }

    }
    else
    {
                parent->greatThan->count--;
                if(parent->greatThan->count <= 0)
                {
                   nukedNode = parent->greatThan;
                   if(!nukedNode->lessThan && !nukedNode->greatThan)
                   {
                        //The one being blown away has no kids.
                        parent->greatThan = NULL;
                        delete nukedNode;
                   }
                   else
                   {
                        //Kids exist on one or both sides of the node that is being nuked
                        if(!nukedNode->greatThan)
                        {
                            parent->greatThan = nukedNode->lessThan;
                            delete nukedNode;
                        }
                        else
                          if(!nukedNode->lessThan)
                          {
                            parent->greatThan = nukedNode->greatThan;
                            delete nukedNode;
                          }
                          else
                          {
                              parent->greatThan = nukedNode->greatThan;
                              node<T> *greaterThanLessThan = nukedNode->greatThan;
                              for(;greaterThanLessThan->lessThan; greaterThanLessThan = greaterThanLessThan->lessThan);
                              greaterThanLessThan->lessThan = nukedNode->lessThan;
                              delete nukedNode;
                          }
                   }
                }

    }
    root = masterParent->lessThan;
    delete  masterParent;
    delete toFind;
    return parent;
}


template<typename T>
bool tree<T>::find(const T &item)
{
    node<T> *ptr = new node<T>(item),
            *ans = find(root, ptr);
    delete ptr;
    return ans;
}

template<typename T>
node<T>* tree<T>::find(node<T> *current, node<T> *item)
{
 //Recursive Solution
    if(!current)
        return NULL;
    if((*current->lessThan == *item) ||
       (*current->greatThan == *item))
        return current;
    return (current->data < item->data) ?
                find(current->lessThan, item) :
                find(current->greatThan, item);

/*
  Iterative Solution

    while(current && (current->data != item->data))
       current = current->data < item->data ?
                 current->lessThan :
                 current->greaterThan;
    return current;
*/
}

template<typename T>
int tree<T>::depth()
{
    return depth(root);
}

template<typename T>
int tree<T>::depth(node<T> *ptr)
{
    return ptr ? 1 + max(depth(ptr->lessThan, ptr->greatThan)) : 0;
}

template<typename T>
ORDER& tree<T>::printOrder()
{
    return print;
}

template<typename T>
tree<T>& tree<T>::operator<<(const T& data)
{
    insert(data);
    return *this;
}

template<typename T>
tree<T>& tree<T>::operator<<(node<T>& n)
{
    insert(n);
    return *this;
}

template<typename T>
ostream& operator<<(ostream& out, tree<T>& t)
{
    t.display(out,t.root);
    return out;
}

template<typename T>
istream& operator>>(istream& in, tree<T>& t)
{

    node<T> newNode;
    while(in>>newNode)
    {
        node<T> *ptr = new node<T>(newNode);
        t.insert(t.root, ptr);
    }
    return in;

}

template<typename T>
void tree<T>::insert(node<T>* &ptr, node<T>* &newNode)
{
    if(!ptr)
        ptr = newNode;
    else
      if(*ptr == *newNode)
      {
          ptr->count += newNode->count;
          delete newNode;
      }
      else
          if(*newNode < *ptr)
              insert(ptr->lessThan,newNode);
          else
              insert(ptr->greatThan, newNode);
}

template<typename T>
void tree<T>::copy(node<T>*ptr)
{
    if(ptr)
    {
        node<T>* newNode = new node(*ptr);
        insert(root, newNode)
    }
    if(ptr->lessThsn)
        copy(ptr->lessThan);
    if(ptr->greatThan)
        copy(ptr->greatThan);
}

template<typename T>
void tree<T>::initialize()
{
    root = NULL;
    print = INORDER;
}



template<typename T>
void tree<T>::display()
{
    display(cout, root);
}

template<typename T>
void tree<T>::display(ostream& out, node<T>*ptr)
{
    if(ptr && print == PREORDER)
        out<<*ptr<<" ";
    if(ptr && ptr->lessThan)
        display(out, ptr->lessThan);
    if(ptr && print == INORDER)
        out<<*ptr<<" ";
    if(ptr && ptr->greatThan)
          display(out,ptr->greatThan);
    if(ptr && print == POSTORDER)
        out<<*ptr<<" ";
}

#endif // BINARYTREE_H
