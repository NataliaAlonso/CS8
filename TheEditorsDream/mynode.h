/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef MYNODE_H
#define MYNODE_H
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

template<typename T>
struct node
{
    T data;

    node();
    node(T &d);

    node(const node<T> &other);
    node(const T &d);
    ~node();

    node<T>& operator=(const node<T> &other);

    void copy(const node<T> &other);

    int left, right, height;

    friend
    bool operator==(node<T> &x, node<T> &y)
    {
        return x.data == y.data;
    }

    friend
    bool operator>(node<T> &x, node<T> &y)
    {
        return x.data > y.data;
    }

    friend
    bool operator<(node<T> &x, node<T> &y)
    {
        return x.data < y.data;
    }

    friend
    bool operator!=(node<T> &x, node<T> &y)
    {
        return x.data != y.data;
    }

    friend
    bool operator>=(node<T> &x, node<T> &y)
    {
        return x.data >= y.data;
    }

    friend
    bool operator<=(node<T> &x, node<T> &y)
    {
        return x.data <= y.data;
    }
};

template<typename T>
node<T>::node()
{
    left = -1;
    right = -1;
    height = 0;
}

template<typename T>
node<T>::node(T &d)
{
    data = d;
    left = -1;
    right = -1;
    height = 0;
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}

template<typename T>
node<T>::~node()
{
    left = -1;
    right = -1;
    height = 0;
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

template<typename T>
void node<T>::copy(const node<T> &other)
{
    data = other.data;
    right = other.right;
    left = other.left;
    height = other.height;
}


#endif // MYNODE_H
