/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#include "unique.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <cstring>
#include "word.h"
#include "tree.h"
#include "myheap.h"

using namespace std;

string fileSelection();                                 // Select file to sort
char typeSelection();                                   // Select element type to sort
void perform(char c, string s);                         // Perform sort
void uniqueVector(string s);                            // Using vectors
void uniqueTree(string s);                              // Using trees
void uniqueHeap(string s);                              // Using heaps
void uniqueMap(string s);                               // Using maps

int main()
{
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl
         << "|               The Editor's Dream                |" << endl
         << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl
         << "     Thank you for using The Editor's Dream!!!     " << endl
         << "   Please select what kind of data structure you   " << endl
         << " would like to use. Then, the program will compute " << endl
         << " the reading level for you and print out a list of " << endl
         << " sorted words from the text, along with paragraph  " << endl
         << "           and line information. Cheers!           " << endl
         << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
     while(1)
    {
        char quit;                                      // Character for exception handling
        try
        {
            char type = typeSelection();
            if (type == 'Q')                            // If user selects quit, throw quit
                throw quit;
            string file = fileSelection();
            perform(type, file);                        // Perform
        }
        catch(char c)                                   // If user selected quit, exit program.
        {
            cout << "Exiting program." << endl;
            return(0);
        }
    }
}

string fileSelection()
{
    string fileName;                                    // String variable to hold user input
    int bad = 0;                                        // Integer for exception handling
    char b;                                             // Character for exception handling
    try
    {
    cout << endl                                        // Prompt user for input file name or default demo file selection
         << "Please enter the name of the file you would like to sort," << endl
         << "or enter demo for the demo file." << endl;
         cin >> fileName;
         if (fileName == "demo")                        // If user selected file, throw b
            throw b;
         ifstream myfile;                               // Create ifstream for user file
         myfile.open(fileName.c_str());                 // Open user file
         if ( !myfile.good() )                          // Check if user file exists
            throw bad;                                  // If not, throw bad
         else                                           // If yes, use file
         {
            cout << "Using file " << fileName << endl;
            return fileName;
         }
    }

    catch(int e)                                        // Exception for non-existant file
    {
        string newFileName;
        cout << "File does not exist. Please re-enter." << endl;
        newFileName = fileSelection();
        return newFileName;
    }

    catch(char c)                                       // Exception for user selection of default demo file
    {
        cout << "You have elected to use the demo files." << endl;
        fileName = "";
        return fileName;
    }
}

char typeSelection()                                    // Prompt user to select what kind of elements will be sorted
{                                                       // User can also choose to exit program
        char type;
        cout << "Please how you would like to sort: " << endl
             << "V: Vector" << endl
             << "M: Map" << endl
             << "H: Heap" << endl
             << "T: Tree" << endl
             << "Q: Quit" <<endl;
             cin >> type;                               // Get user input
             type = toupper(type);                      // Convert to uppercase for ease of handling
            return type;                                // Return user selection
}

void perform(char c, string s)                          // Function performs user selected sort
{
    switch(c)
    {
        case 'V': uniqueVector(s);                      // Perform using vector
                  break;
        case 'M': uniqueMap(s);                         // Perform using tree
                  break;
        case 'H': uniqueHeap(s);                        // Perform using heap
                  break;
        case 'T': uniqueTree(s);                        // Perform using tree
                  break;
    }
}

void uniqueVector(string s)
{
    unique<word> ustring;                               // Create string type unique item for input elements
    ifstream myfile;                                    // Create ifstream for input
    if ( s == "")                                       // If s is empty (default), open demo file string.txt
         myfile.open("string.txt");
    else
        myfile.open(s.c_str());                         // Else open user defined file
    char paragraph[131072];
    char line[256];
    while ( myfile.good() )
    {
                                                        // PARAGRAPHS
        myfile.getline(paragraph,131072);
        ofstream outfile ("formatted.txt");
        if(isalpha(paragraph[0]))
            ustring.paragraphs++;
        outfile << paragraph;
        outfile.close();
                                                        //WORDS
        ifstream newfile;
        newfile.open("formatted.txt");
        while(newfile.good())
        {
            newfile.getline(line,256,' ');              // Space delimmited
            int i = 0;
            line[0] = toupper(line[0]);
            int currentSentence = ustring.sentences;
            int currentPara = ustring.paragraphs;
            while( line[i] )                            // Remove punctuation
            {
                if(line[i]=='.')
                    ++ustring.sentences;
                if ((isspace(line[i]) || ispunct(line[i])) && line[i] != '-' && !isdigit(line[i+1])  && line[i] != '(' && line[i] != ')')
                {
                    line[i] = '\0';
                    break;
                }
                i++;
            }
            if((strlen(line)/3)== 0)                    // Detemine syllables
                ustring.syllables++;
            else
                ustring.syllables += (strlen(line)/3);
            int length = strlen(line);
            string newS = line;
            if(isalpha(line[0]))
            {
                ustring.addNumberOfWords(line[0],1);
                ustring.addWordCounts(newS,1);
                word newWord(newS,currentPara,currentSentence,length);
                ustring.addVector(newWord);
                ustring.words++;
            }
        }
    }
    ustring.computeReadingLevel();
    ustring.displayVector();
    ustring.displayTopTen();
}

void uniqueTree(string s)
{
    unique<word> ustring;
    ifstream myfile;                                    // Create ifstream for input
    if ( s == "")                                       // If s is empty (default), open demo file string.txt
         myfile.open("string.txt");
    else
        myfile.open(s.c_str());                         // Else open user defined file
    char line[256];
    while ( myfile.good() )
    {
        myfile.getline(line,256,' ');                   // Space delimmited
        int i = 0;
        line[0] = toupper(line[0]);
        int currentSentence = ustring.sentences;
        int currentPara = ustring.paragraphs;
        while( line[i] )                                // Remove punctuation
        {
            if(line[i]=='.')
                ++ustring.sentences;
            if ((isspace(line[i]) || ispunct(line[i])) && line[i] != '-' && !isdigit(line[i+1])  && line[i] != '(' && line[i] != ')')
            {
                line[i] = '\0';
                break;
            }
            i++;
        }
        if((strlen(line)/3)== 0)
            ustring.syllables++;
        else
            ustring.syllables += (strlen(line)/3);
        int length = strlen(line);
        string newS = line;
        ustring.addNumberOfWords(line[0],1);
        ustring.addWordCounts(newS,1);
        word newWord(newS,currentPara,currentSentence,length);
        //ustring.addTree(newWord);
        ustring.words++;
    }
    ustring.computeReadingLevel();
    //ustring.displayTree();
    //
    ustring.displayTopTen();
}

void uniqueHeap(string s)
{
    unique<word> ustring;
    ifstream myfile;                                    // Create ifstream for input
    if ( s == "")                                       // If s is empty (default), open demo file string.txt
         myfile.open("string.txt");
    else
        myfile.open(s.c_str());                         // Else open user defined file
    char line[256];
    while ( myfile.good() )
    {
        myfile.getline(line,256,' ');                   // Space delimmited
        int i = 0;
        line[0] = toupper(line[0]);
        int currentSentence = ustring.sentences;
        int currentPara = ustring.paragraphs;
        while( line[i] )                                // Remove punctuation
        {
            if(line[i]=='.')
                ++ustring.sentences;
            if ((isspace(line[i]) || ispunct(line[i])) && line[i] != '-' && !isdigit(line[i+1])  && line[i] != '(' && line[i] != ')')
            {
                line[i] = '\0';
                break;
            }
            i++;
        }
        if((strlen(line)/3)== 0)
            ustring.syllables++;
        else
            ustring.syllables += (strlen(line)/3);
        int length = strlen(line);
        string newS = line;
        ustring.addNumberOfWords(line[0],1);
        ustring.addWordCounts(newS,1);
        word newWord(newS,currentPara,currentSentence,length);
       // ustring.addHeap(newWord);
        ustring.words++;
    }
    ustring.computeReadingLevel();
    //ustring.displayHeap();
    //ustring.displayTopTen();
}

void uniqueMap(string s)
{
    unique<word> ustring;                               // Create string type unique item for input elements
    ifstream myfile;                                    // Create ifstream for input
    if ( s == "")                                       // If s is empty (default), open demo file string.txt
         myfile.open("string.txt");
    else
        myfile.open(s.c_str());                         // Else open user defined file
    char paragraph[131072];
    char line[256];
    while ( myfile.good() )
    {
                                                        // PARAGRAPHS
        myfile.getline(paragraph,131072);
        ofstream outfile ("formatted.txt");
        if(isalpha(paragraph[0]))
            ustring.paragraphs++;
        outfile << paragraph;
        outfile.close();
                                                        // WORDS
        ifstream newfile;
        newfile.open("formatted.txt");
        while(newfile.good())
        {
            newfile.getline(line,256,' ');              // Space delimmited
            int i = 0;
            line[0] = toupper(line[0]);
            int currentSentence = ustring.sentences;
            int currentPara = ustring.paragraphs;
            while( line[i] )                            // Remove punctuation
            {
                if(line[i]=='.')
                    ++ustring.sentences;
                if ((isspace(line[i]) || ispunct(line[i])) && line[i] != '-' && !isdigit(line[i+1])  && line[i] != '(' && line[i] != ')')
                {
                    line[i] = '\0';
                    break;
                }
                i++;
            }
            if((strlen(line)/3)== 0)                    // Detemine syllables
                ustring.syllables++;
            else
                ustring.syllables += (strlen(line)/3);
            int length = strlen(line);
            string newS = line;
            if(isalpha(line[0]))
            {
                ustring.addNumberOfWords(line[0],1);
                ustring.addWordCounts(newS,1);
                word newWord(newS,currentPara,currentSentence,length);
                ustring.addMap(newWord);
                ustring.words++;
            }
        }
    }
    ustring.computeReadingLevel();
    ustring.displayMap();
    ustring.displayTopTen();
}
