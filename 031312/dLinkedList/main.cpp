#include <QtCore/QCoreApplication>
#include "driver.h"

using namespace std;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  dLinkedList<char> one, two;
  char ans;
  int list = 1;
  system("cls");
/*  try
  {
    checkArgs(argc, argv, one, two, list);
  }
  catch(int e)
  {
     cout<<"Error "<<e<<". Program terminating"<<endl;
     exit(e);
  }*/
  do
  {
     ans = menu();
     perform(ans, list,  one, two);
  }while(toupper(ans) != 'Q');
  return a.exec();
}
