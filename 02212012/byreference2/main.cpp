#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>

using namespace std;

void swap(int* &x, int* & y);
void swap2(int**x, int** y);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int b, c;
    int* pb = &b, *pc = &c;
    cout<<"Before swap, pb = "<<pb<<" pc = "<<pc<<endl;
    swap(pb,pc);
    cout<<"After swap and before swap2, pb = "<<pb<<" pc = "<<pc<<endl;
    swap2(&pb,&pc);
    cout<<"After swap2, pb = "<<pb<<" pc = "<<pc<<endl;
    return a.exec();
}


void swap(int* &x, int* & y)
{
    int* temp = x;
    x = y;
    y = temp;
}

void swap2(int** x, int** y)
{
    int* temp = *x;
    *x = *y;
    *y = temp;
}
