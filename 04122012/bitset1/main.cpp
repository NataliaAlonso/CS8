#include <QtCore/QCoreApplication>
// bitset::operator[]
#include <iostream>
#include <bitset>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

  bitset<4> mybits;

  mybits[1]=1;             // 0010
  mybits[2]=mybits[1];     // 0110

  cout << "mybits: " << mybits << endl;

  return a.exec();
}
