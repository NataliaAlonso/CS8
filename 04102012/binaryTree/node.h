#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

template<typename T>
struct node
{
    T data;
    int count;
    node<T> *lessThan, *greatThan;

    node();
    node(T input, int qty = 1);
    node(const node<T> &other);
    node& operator=(const node<T>& other);

    template<typename U>
    friend
    bool operator<(node<U> &x, node<U> &y);

    template<typename U>
    friend
    bool operator==(node<U> &x, node<U> &y);


    template<typename U>
    friend
    ostream& operator<<(ostream& out, node<U> &n);

    template<typename U>
    friend
    istream& operator>>(istream& in, node<U> &n);

};

template<typename T>
node<T>::node()
{
    lessThan = greatThan = NULL;
    count = 0;
}

template<typename T>
node<T>::node(T input, int qty)
{
    data = input;
    lessThan = greatThan = NULL;
    count = qty;
}

template<typename T>
node<T>::node(const node<T> &other)
{
     lessThan = greatThan = NULL;
     count = other.count;
     data = other.data;
}

template<typename T>
node<T>& node<T>::operator=(const node& other)
{
    if(this != &other)
    {
        lessThan = greatThan = NULL;
        count = other.count;
        data = other.data;
    }
    return *this;
}

template<typename T>
bool operator<(node<T> &x, node<T> &y)
{
    return x.data < y.data;
}

template<typename T>
ostream& operator<<(ostream& out, node<T> &n)
{
    out<<n.data<<"["<<n.count<<"] ";
    return out;
}

template<typename T>
istream& operator>>(istream& in, node<T> &n)
{
    char junk;
    in>>n.data>>junk>>n.count>>junk;
    return in;
}



template<typename U>
bool operator==(node<U> &x, node<U> &y)
{
    return x.data == y.data;
}


#endif // NODE_H




