#include <QtCore/QCoreApplication>
// bitset::operator[]
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

  int node;
  cout<<"What node number: ";
  cin>>node;
  int where = (int)log10(node*1.)/log10(2*1.);
  bitset<32> mybits(node);

 // mybits[1]=1;             // 0010
 // mybits[2]=mybits[1];     // 0110

  cout << "mybits: ";
  for(int i = where -1; i > -1; i--)
      cout<<mybits[i];
  cout<< endl;

  return a.exec();
}
