#include <QtCore/QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>

#include "WordMuncher.h"
#include "WordOut.h"

using namespace std;

//Data
bool sorting = true;
bool display = false;
bool working = true;
int chooseNum = 0;
int chooseStruct = 0;
double elapsedTime, elapsedTimeHeap;
string fileName;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "********WordATron 0.01********" <<endl;
//Check if files exists
    fstream fin;
    do
    {
      string fileName;
      cout << "Enter input file name: ";
      cin >> fileName;

      fin.open(fileName.c_str(), ios::in);
      if(!fin.is_open())
      {
          cout << "File Name Does Not Exist!\n";
      }
      else
      {
          cout << "Valid file name.\n";
          fin.close();

          //Functions Declaratons
        WordMuncher wordmunch("\\w[\\w.]\\S+|\\w[\\w.]\\?|\\w[\\w+]", fileName, false);
        //WordOut<string> wordsaver;
        WordOut<string> wordsaver((int)(wordmunch.getTotoalWords()), (int)(wordmunch.getTotoalLines()),wordmunch.getTotalParagraphs());
        //Data Sructs
        tree<string> thetree;
        Heap<AWORD> theHeap;

        if(sorting)
        {
            cout << "\n1: TREE" << endl;
            cout << "2: HEAP" << endl;
            cin >> chooseNum;
            sorting = false;
        }

        if ((sorting == false)&&(chooseNum == 1))
        {
            cout << "--Tree1 Sort" << endl << endl;
            //Start//
            //TREEE
            //Timer Start
            timeval t1, t2;
            gettimeofday(&t1, NULL);

            //create Tree;
            wordmunch.setTreeSructOfWords(thetree);
            thetree.setTraverse(IN);

            // stop timer
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

            wordsaver.fillWithTree(thetree);
            //set timer
            wordsaver.setTime(elapsedTime);

            wordmunch.setMostFrequentWords();

            for(int i = 0; i < wordmunch.getFrequentCount(); i++){
                wordsaver.setMostFrequent(wordmunch.getMostFrequent(i));
            }
            //End///
            display = true;
            chooseStruct = 1;
            chooseNum = 0;
            cout << "WORKING" << endl;
        }
        if ((sorting == false)&&(chooseNum == 2)) {
            cout << "--Heap Sort" << endl << endl;
            //Start//
            timeval t1, t2;
            gettimeofday(&t1, NULL);

            //create Tree;
            wordmunch.setTreeSructOfWords(thetree);
            thetree.setTraverse(IN);

            // stop timer
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
            //cout << elapsedTime << " ms." << endl << endl;
            theHeap.printInOrderToWordOut(wordsaver);
            //set timer
            wordsaver.setTime(elapsedTime);

            wordmunch.setMostFrequentWords();

            for(int i = 0; i < wordmunch.getFrequentCount(); i++){
                wordsaver.setMostFrequent(wordmunch.getMostFrequent(i));
            }
            //End//
            display = true;
            chooseStruct = 2;
            chooseNum = 0;
        }

        //MAIN MENU
        while(working) {
            if (display)
            {
                cout << "1: SHOW INFO" << endl;
                cout << "2: CHOOSE LETTER" << endl;
                cout << "3: SAVE & QUIT" << endl;
                cout << "4: QUIT" << endl;
                cin >> chooseNum;
                display = false;
            }
            if ((display == false)&&(chooseNum == 1)) {
                //SHOW INFO//
                if(chooseStruct == 1) {
                    cout << "Tree Info" << endl;
                    wordsaver.printSummary(cout);
                }
                if(chooseStruct == 2) {
                    cout << "Heap Info" << endl;
                    wordsaver.printSummary(cout);
                }
                cout << endl;
                //End//
                display = true;
                chooseNum = 0;
            }
            if ((display == false)&&(chooseNum == 2)) {
                char chooseChar;
                cout << "--Choose A Letter: ";
                //CHOOSE LETTER//
                cin >> chooseChar;
                stringstream ss;
                string s;
                ss << chooseChar;
                ss >> s;
                if(chooseStruct == 1) {
                    cout << endl << "TREE LETTERS: " << s << endl << endl;
                    wordsaver.printLetters(s);
                }
                if(chooseStruct == 2) {
                    cout << endl << "HEAP LETTERS: " << s << endl << endl;
                    wordsaver.printLetters(s);
                }

                cout << endl;
                //End//
                display = true;
                chooseNum = 0;
            }
            if ((display == false)&&(chooseNum == 3)) {
                cout << "--Save & Quit" << endl << endl;
                //Start//
                if(chooseStruct == 1) {
                    fstream output;
                    output.open(wordsaver.getSummaryFile().c_str(),ios::out | ios::trunc);
                    wordsaver.printSummary(output);
                    output.close();
                    wordsaver.printEverything();
                }
                if(chooseStruct == 2) {
                    cout << "HEAP LETTERS" << endl;
                    fstream output;
                    output.open(wordsaver.getSummaryFile().c_str(),ios::out | ios::trunc);
                    wordsaver.printSummary(output);
                    output.close();
                    wordsaver.printEverything();
                }

                //End//
                display = true;
                working = false;
                chooseNum = 0;
            }
            if ((display == false)&&(chooseNum == 4)) {
                cout << "--Quit" << endl << endl;
                display = true;
                working = false;
                chooseNum = 0;
                wordsaver.deleteFile();
            }
        }

        cout << "********WordATron 0.01********" <<endl;
      }
    }while(!fin.is_open());

    return a.exec();
}