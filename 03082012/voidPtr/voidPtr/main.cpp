//#include <QtCore/QCoreApplication>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "derived.h"

using namespace std;

void print(string title, derived& list, int size);
void sort(derived& list, int size);
void print2(string title, derived2& list, int size);
void sort2(derived2& list, int size);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    cout<<"Starting program"<<endl;
    derived list(10);
    derived2 list2(10);
    for(int i=0; i<10; i++)
       cout<<"assigning "<<(list[i] =65 + rand()%26)<<" to list["<<i<<"]\n";
    sort(list,10);
    print("The sorted list is: ",list,10);
    
    for(int i=0; i<10; i++)
       cout<<"assigning "<<(list2[i] = rand()%256)<<" to list["<<i<<"]\n";
    sort2(list2,10);
    print2("The sorted list is: ",list2,10);
    
    
    system("pause");
    return 0;
}

void sort(derived& list, int size)
{
     for(int i=0; i<size; i++)
       for(int j=0; j<size; j++)
         if(list[i] < list[j])
         {
            char temp = list[i];
            list[i] = list[j];
            list[j] = temp;
         }
}

void print(string title, derived& list, int size)
{    
    cout<<title<<endl;
    for(int i=0; i<size; i++)
        cout<<list[i]<<" ";
    cout<<endl;
}

void sort2(derived2& list, int size)
{
     for(int i=0; i<size; i++)
       for(int j=0; j<size; j++)
         if(list[i] < list[j])
         {
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
         }
}

void print2(string title, derived2& list, int size)
{    
    cout<<title<<endl;
    for(int i=0; i<size; i++)
        cout<<list[i]<<" ";
    cout<<endl;
}
