#ifndef QUEUEPARSER_H
#define QUEUEPARSER_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "myqueue.h"

using namespace std;


class queueParser
{
    public:
      queueParser();
      ~queueParser();
      queueParser(string &data);
      queueParser(const queueParser& other);
      queueParser& operator=(const queueParser& other);

      queueParser& operator<<(string& data); //Insertion operator
      void input(string& data);

      queueParser& operator>>(string &rpn);

      queueParser& operator>>(queue<string> &result); //Extraction operator
      void result(queue<string> &data);


    private:
      queue<string> items;
      string line, rpnLine;
      queue<string> ops;

      void putResult(queue<string> &data);
      void parse();
      void binaryOp(unsigned int &pos, bool &redo);
};


#endif // QUEUEPARSER_H
