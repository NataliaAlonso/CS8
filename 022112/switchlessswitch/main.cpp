#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef void (*fptr)();

void nothing();
void up();
void down();
void left();
void right();
void quit();

void load(fptr whatToDo[]);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char choice;
    fptr whatToDo[128];
    load(whatToDo);
    while(1)
    {
        cout<<"What do you want to do? "<<endl;
        cin>>choice;
        whatToDo[choice]();
    }
    return a.exec();
}


void nothing()
{

}

void up()
{
    cout<<"UP!!!"<<endl;
}

void down()
{
    cout<<"DOWN!!!"<<endl;
}

void left()
{
    cout<<"LEFT!!!"<<endl;
}

void right()
{
    cout<<"RIGHT!!!"<<endl;
}

void quit()
{
    exit(0);
}

void load(fptr whatToDo[])
{
    for(int i = 0; i < 128; i++)
        whatToDo[i] = nothing;
    whatToDo['U'] = whatToDo['u'] = up;
    whatToDo['D'] = whatToDo['d'] = down;
    whatToDo['L'] = whatToDo['l'] = left;
    whatToDo['R'] = whatToDo['r'] = right;
    whatToDo['Q'] = whatToDo['q'] = quit;
}
