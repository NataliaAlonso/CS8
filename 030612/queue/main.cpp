#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "queue.h"


using namespace std;


bool again();
void menu(myQueue<char> queue[]);
void perform(myQueue<char> queue[], char selection, int &current);

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   int size;
   bool repeat;
   do
   {
     do
     {
        repeat = true;
        try
        {
            cout<<"What size of queue do you want: ";
            cin>>size;
            myQueue<char> sample[2];
            sample[0].resize(size);
            sample[1].resize(size);
            menu(sample);
            repeat = false;
        }
        catch(errorCodes e)
        {
            if(e == ILLEGAL_QUEUE_SIZE) cout<<"Illegal queue size, please try again";
            else exit(e);
        }
     }while (repeat);
   }while(again());

   return a.exec();
}

bool again()
{
   char ans;
   cout<<"Do you want to do this again? ";
   cin >> ans;
   return toupper(ans) == 'Y';
}


void perform(myQueue<char> queue[], char selection, int &current)
{
   char value;
   char name[30];
   switch(toupper(selection))
   {

     case '+' : cout<<"What value do you want to enqueue? ";
                cin>> value;
                try
                {
                      queue[current]<<value;
                      cout<<value<<" placed in the queue successfully"<<endl;
                }
                catch(errorCodes e)
                {
                    if(e == FULL) cout<<"The queue was full"<<endl;
                    else exit(e);
                }
                catch(...)
                {
                   cout<<"Unknown error occurred... program terminating..."<<endl;
                   exit(1);
                }
                break;


     case '-' : try
                {
                   queue[current]>>value;
                   cout<<value<<" dequeued successfully"<<endl;
                }
                catch(errorCodes e)
                {
                   if(e == EMPTY) cout<<"queue was empty"<<endl;
                   else exit(e);
                }
                catch(...)
                {
                   cout<<"Unknown error occurred... program terminating..."<<endl;
                   exit(1);
                }
                break;

     case 'D' :{
                  char ans;
                  cout<<"The current queue is "<<current
                      <<"Duplicate queue "<<current<<" into queue "<<(current+1)%2<<"? ";
                  cin>>ans;
                  if(toupper(ans) == 'Y')
                     queue[(current+1)%2] = queue[current];
                  else
                    if(toupper(ans) == 'N')
                    {
                       cout<<"Duplicate queue "<<(current+1)%2<<" into queue "<<current<<"? ";
                       cin>>ans;
                       if(toupper(ans) == 'Y')
                             queue[current] = queue[(current+1)%2];
                    }
                  break;
                }

     case 'P' : cout<<queue[current]<<endl;
                break;

     case 'F' : if(queue[current].full())
                     cout<<"The queue is full"<<endl;
                else
                    cout<<"The queue is not full"<<endl;
                break;

     case 'M' : if(queue[current].empty())
                     cout<<"The queue is empty"<<endl;
                else
                    cout<<"The queue is not empty"<<endl;
                break;

     case 'C' : cout<<"There are "<<queue[current].size()<<" items in the queue "<<endl;
                break;

     case 'N' : cout<<"There were "<<queue[current].size()<<" items in the queue you just disposed"<<endl;
                queue[current].clear();
                break;

     case 'W' : {
                  ofstream out;
                  cout<<"What is the name of the file you want to write to: ";
                  cin>>name;
                  out.open(name);
                  out<<queue[current];
                  out.close();
                  break;
                }

     case 'H' : cout<<"There are "<<queue[current].size()<<" items in queue "<<current<<endl;
                break;

     case 'S' : current = (current+1)%2;
                cout<<"Now using queue "<<current<<endl;
                break;

     case 'R' : {
                  ifstream in;
                  cout<<"What is the name of the file you want to read from: ";
                  cin>>name;
                  in.open(name);
                  in>>queue[current];
                  in.close();
                  break;
                }
     case 'Q' : cout<<"Goodbye"<<endl;
   }
}


void menu(myQueue<char> queue[])
{
  int current = 0;
  char selection;
  do
  {
     cout<<endl
         <<"Please make a choice: "<< endl
         <<" +. Enqueue a value"<<endl
         <<" -. Dequeue a value"<<endl
         <<" S. Select the queue to use"<<endl
         <<" D. Duplicate (copy) a queue"<<endl
         <<" P. Print the queue"<<endl
         <<" F. Is the queue full"<<endl
         <<" M. Is the queue empty"<<endl
         <<" C. What is the count of the items in the queue"<<endl
         <<" N. Dispose of the queue"<<endl
         <<" W. Write to a file"<<endl
         <<" R. Read from a file"<<endl
         <<" H. How many items are in the queue"<<endl
         <<" Q. Quit"<<endl
         <<"What is your selection: ";
     cin>>selection;
     perform(queue, selection, current);
  }while(toupper(selection) != 'Q');
}


