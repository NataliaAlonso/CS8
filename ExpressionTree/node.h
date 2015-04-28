#ifndef NODE_H
#define NODE_H
#include <cstdlib>

using namespace std;

template<typename T>
struct node
{
    node();
    node(const T &d);
    ~node();
    node(const node<T>& other);
    node& operator=(const node<T>& other);

    T data;
    node<T> *left;
    node<T> *right;
};

#endif // NODE_H
template<typename T>
node<T>::node()
{
    left = right = NULL;
}

template<typename T>
node<T>::node(const T &d)
{
    data = d;
    left = right = NULL;
}

template<typename T>
node<T>::~node()
{
    left = right = NULL;
}

template<typename T>
node<T>::node(const node<T>& other)
{
    data = other.data;
    left = other.left;
    right = other.right;
}

template<typename T>
node<T>& node<T>::operator=(const node<T>& other)
{
    if(this != &other)
    {
        data = other.data;
        left = other.left;
        right = other.right;
    }
    return *this;
}
