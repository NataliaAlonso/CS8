#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

template<typename T>
class myQueue
{
    public:
        myQueue(int qty = 5);
        ~myQueue();
        myQueue(const myQueue<T> &other);
        myQueue<T>& operator=(const myQueue<T> &other);

        T& operator[](int index);
        T& front();
        T& dequeue();
        void enqueue(const T &data);
        int size();
        void resize(int qty);
        void clear();
        bool empty();
        bool full();

        myQueue<T>& operator<<(const T & data);
        myQueue<T>& operator>>(T &data);

        template<typename U>
        friend
        ostream& operator<<(ostream& out, myQueue<T> &Queue);


    private:
        int mySize, boq, eoq;
        T* theQueue;

        void copy(const myQueue<T> &other);
    };


template<typename T>
myQueue<T>::myQueue(int qty)
{
    theQueue = new T[mySize = qty];
    boq = eoq = 0;
}

template<typename T>
myQueue<T>::~myQueue()
{
    delete [] theQueue;
}

template<typename T>
myQueue<T>::myQueue(const myQueue<T> &other)
{
    copy(other);
}

template<typename T>
myQueue<T>& myQueue<T>::operator=(const myQueue<T> &other)
{
    if(this != &other)
    {
        delete [] theQueue;
        copy(other);
    }
    return *this;
}


template<typename T>
T& myQueue<T>::operator[](int index)
{
    //MAJOR ERROR HERE
    if(index < 0 || index >= mySize)
        throw OUT_OF_BOUNDS;
    return theQueue[(boq + index) % mySize];
}

template<typename T>
T& myQueue<T>::top()
{
    return theQueue[boq];
}

template<typename T>
T& myQueue<T>::dequeue()
{
    if(empty())
        throw EMPTY;
    T temp = theQueue[boq];
    boq = (++boq % mySize);
    return temp;
}

template<typename T>
void myQueue<T>::enqueue(const T &data)
{
    if(full())
        throw FULL;
    theQueue[eoq] = data;
    eoq = (++eoq % mySize);
}

template<typename T>
int myQueue<T>::size()
{
    return mySize;
}

template<typename T>
void myQueue<T>::resize(int qty)
{
    delete [] theQueue;
    theQueue = new T[mySize = qty];
}


template<typename T>
void  myQueue<T>::clear()
{
    boq = eoq = 0;
}


template<typename T>
bool myQueue<T>::empty()
{
    return boq == eoq;
}

template<typename T>
bool myQueue<T>::full()
{
    return boq == (eoq+1)%mySize;
}


template<typename T>
myQueue<T>& myQueue<T>::operator<<(const T & data)
{
    enqueue(data);
    return *this;
}


template<typename T>
myQueue<T>& myQueue<T>::operator>>(T &data)
{
    data = dequeue();
    return *this;
}

template<typename U>
ostream& operator<<(ostream& out, myQueue<U> &queue)
{
    out<<"Queue size = "<<queue.size()<<endl
       <<"Current beginning of Queue = "<<queue.tos<<endl
       <<"Current end of Queue = "<<queue.eoq<<endl;

    for(int i = 0; i < queue.mySize; i++)
        out<<queue.theQueue[i]<<endl;
    return out;
}


template<typename U>
istream& operator>>(istream& in, myQueue<U> &Queue)
{

    //LIKE SAM SAID, there is an error here
    stringstream ss;
    string line;
    int intVal;
    U data;
    if(in>>line)
    {
        ss<<line.substr(line.find("=")+1, string::npos);
        ss>>intVal;
        Queue.resize(intVal);
        in>>line;
        ss<<line.substr(line.find("=")+1, string::npos);
        ss>>intVal;
        Queue.boq = intVal;
        in>>line;
        ss<<line.substr(line.find("=")+1, string::npos);
        ss>>intVal;
        Queue.eoq = intVal;
        while(in>>data)
            Queue.push(data);
    }
    return in;
}

template<typename T>
void myQueue<T>::copy(const myQueue<T> &other)
{
    theQueue = new T[mySize = other.mySize];
    for(int i =0; i < mySize; i++)
        theQueue[i] = other.theQueue[i];
    boq = other.boq;
    eoq = other.eoq;
}

#endif // QUEUE_H
