#ifndef STACKPARSER_H
#define STACKPARSER_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "mystack.h"

using namespace std;

class stackParser
{
    public:
      stackParser();
      ~stackParser();
      stackParser(string &data);
      stackParser(const stackParser& other);
      stackParser& operator=(const stackParser& other);

      stackParser& operator<<(string& data); //Insertion operator
      void input(string& data);

      stackParser& operator>>(string &rpn);

      stackParser& operator>>(mystack<string> &result); //Extraction operator
      void result(mystack<string> &data);


    private:
      mystack<string> items;
      string line, rpnLine;
      mystack<string> ops;

      void putResult(mystack<string> &data);
      void parse();
      void binaryOp(unsigned int &pos, bool &redo);
};


#endif // STACKPARSER_H
