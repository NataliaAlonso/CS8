#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>

using namespace std;

void swap(int &a, int &b);
void swap2(int *a, int *b);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int x = 2, y = 3;
    cout<<"Before swap x = "<<x<<" y = "<<y<<endl;
    swap(x,y);
    cout<<"After swap and before swap2 x = "<<x<<" y = "<<y<<endl;
    swap2(&x,&y);
    cout<<"After swap2 x = "<<x<<" y = "<<y<<endl;
    return a.exec();
}


void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
