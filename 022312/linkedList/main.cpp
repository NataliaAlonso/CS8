
#include <QtCore/QCoreApplication>
#include "linkedList.h"


void perform(char ans, linkList<char> &object);
void menu(char &ans);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    linkList<char> pez;
    char ans;
    do
    {
       menu(ans);
       perform(toupper(ans), pez);
    }while(toupper(ans) != 'Q');
    return a.exec();
}

void menu(char &ans)
{
    cout<<endl<<endl
        <<"Here are your options:"<<endl
        <<"  A. Add data"<<endl
        <<"  +. Add data"<<endl
        <<"  D. Remove data"<<endl
        <<"  -. Remove data"<<endl
        <<"  P. Print the linked list"<<endl
        <<"  N. Dispose of the linked list"<<endl
        <<"  C. Display a count of how many items are in the linked list"<<endl
        <<"  E. Is the linked list empty"<<endl
        <<"  F. Enquire if a data element is in the list"<<endl
        <<"  Q. Quit this program"<<endl
        <<"Please make a selection: ";
    cin>>ans;
}


void perform(char ans, linkList<char> &object)
{
    char data;
    string isnot;
    switch(ans)
    {

      case 'A' :
      case '+' : cout<<"Please enter your data: ";
                 cin>>data;
                 object<<data;
                 break;

       case 'D' :
       case '-' : cout<<"Please enter your data to remove: ";
                 cin>>data;
                 try
                 {
                        object >> data;
                  }
                  catch(...)
                  {
                        cout<<"Error occurred"<<endl;
                        break;
                  }
                  break;

       case 'P' : cout<<"The contents of the linked list are:"<<endl
                      <<object
                      <<endl;
                  break;

       case 'F' :{
                   cout<<"Which data element do you wish to find? ";
                   cin>>data;
                   int count = object.find(data);
                   if(count)
                      cout<<data<<" occurs "<<count<<" times in the list"<<endl;
                    else
                      cout<<data<<" is not in the list"<<endl;
                    break;
                  }

       case 'N' : object.removeAll();
                  cout<<"List is now empty"<<endl;
                  break;

       case 'C' : cout<<"There are "<<object.quantity()<<" nodes in your list that contain "
                      <<object.dataQty()<<" data items"<<endl<<endl;
                  break;


       case 'E' : isnot = object.empty() ? " is ": " is not ";
                  cout<<"The linked list"<<isnot<<"empty"<<endl;
                  break;

       case 'Q' : cout<<"Thank you for using this program"<<endl;
                  break;

       default  : cout<<"Not a valid selection. Please try again."<<endl;
    }
}

