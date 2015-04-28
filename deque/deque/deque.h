#ifndef DEQUE_H
#define DEQUE_H
#include "mynode.h"

template<typename T>
class deque
{
    public:
        deque();
        virtual ~deque();
        deque(const T &d);
        deque(const deque<T>& other);
        deque& operator=(const deque<T>& other);

        void begin();
        void end();
        void rbegin();
        void rend();
        int size();
        void resize();
        bool empty();
        deque& operator[]();
        void  at();
        void front();
        void back();
        void push_back();
        void push_front();
        void pop_back();
        void pop_front();
        void insert(T data);
        void erase();
        void swap();
        void clear(node<T>* &ptr);

    protected:
    private:
        node<T>* back;
        noce<T>* front;
        int position;
        int size;
        void copy(const deque<T> &other);
        node<T>* find(node<T> ptr, T item);
};

template<typename T>
deque::deque()
{
    back = NULL;
    front = NULL;
    size++;
    position = 0;
}

template<typename T>
deque::~deque()
{
    clear(back);
}

template<typename T>
deque::deque(const T &d)
{
    back = new node<T>(d);
    front = back;
    size++;
    position = 0;
}

template<typename T>
deque::deque(const deque<T>& other)
{
    copy(other);
}

template<typename T>
deque& deque::operator=(const deque<T>& other)
{
	if(this != &other)
	{
		clear(back);
		copy(other);
	}
	return *this;
}

template<typename T>
void deque::begin()
{

}

template<typename T>
void deque::end()
{

}

template<typename T>
void deque::rbegin()
{

}

template<typename T>
void deque::rend()
{

}

template<typename T>
int deque::size()
{
    return size;
}

template<typename T>
void deque::resize()
{

}

template<typename T>
bool deque::empty()
{
    return size == 0;
}

template<typename T>
deque& deque::operator[]()
{

}

template<typename T>
void deque::at()
{

}

template<typename T>
deque& deque::front()
{
    return front->data;
}

template<typename T>
deque& deque::back()
{
    return back->data;
}

template<typename T>
void deque::push_back()
{
	node<T> *temp = new node<T>(data);
	back->prev = temp;
	temp->next = back;
	back = temp;
	size++;
	position = 0;
	temp = back;
	for(; temp !=NULL; temp->next)
        temp->position++;
}

template<typename T>
void deque::push_front()
{
	node<T> *temp = new node<T>(data);
	front->next = temp;
	temp->prev = front;
	size++;
	temp->position = size;
}

template<typename T>
void deque::pop_back()
{
    node<T> *temp = back;
	back = back->next;
	delete temp;
	size--;
	temp = back;
	for(; temp !=NULL; temp->next)
        temp->position--;
}

template<typename T>
void deque::pop_front()
{
    node<T> *temp = front;
	front = front->prev;
	delete temp;
	size--;
}

template<typename T>
void deque::insert(T data)
{

}

template<typename T>
void deque::erase()
{

}

template<typename T>
void deque::swap()
{

}

template<typename T>
void deque::clear(node<T>* &ptr)
{

}

template<typename T>
void deque::copy(const deque<T> &other)
{
	node<T> *tmp = other.back;
	for(;tmp != NULL; tmp=tmp->next)
		push_back(tmp->data);
}

template<typename T>
node<T>* deque::find(node<T> ptr, T item)
{

}

#endif // DEQUE_H
