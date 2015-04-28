#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef void (*fptr)();

void hello();
void goodbye();
void perform(fptr whatToDo);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    perform(hello);
    perform(goodbye);
    return a.exec();
}

void hello()
{
    cout<<"Hello!"<<endl;
}

void goodbye()
{
    cout<<"Goodbye"<<endl;
}

void perform(fptr whatToDo)
{
    whatToDo();
}
