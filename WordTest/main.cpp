#include <iostream>
#include "word.h"
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    vector<word> wordVector(256);
    string apple = "Apple";
    string banana = "Banana";
    string orange = "Orange";
    int para = 1;
    int sentence = 1;
    int length = 5;
    word newWord(apple,para,sentence,length);
    wordVector[0] = newWord;
    cout << "First element: " << wordVector[0];
}
