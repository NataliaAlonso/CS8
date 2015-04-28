/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef UNIQUE_H
#define UNIQUE_H
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "tree.h"
#include "word.h"
#include "myheap.h"

using namespace std;

template <typename T>
class unique
{
    public:
        unique();
        ~unique();

        unique(const unique<T> &other);
        unique<T>& operator=(const unique<T> &other);

        void addVector(T &x);                               // Adds new value to vector
        void addTree(T &x);                                 // Adds new value to tree
        void addHeap(T &x);                                 // Adds new value to heap
        void addMap(T &x);                                  // Adds new value to map
        void addNumberOfWords(char &x, int y);              // Adds letters to map
        void addWordCounts(string &x, int y);               // Adds words to map
        void displayVector();                               // Display vector
        void displayTree();                                 // Display Tree
        void displayHeap();                                 // Display Heap
        void displayMap();                                  // Display Map
        void displayTopTen();                               // Display top ten used words
        void computeReadingLevel();                         // Compute reading level

        int syllables, words, sentences, paragraphs;
        double readingLevel;
        map<char,int> numberOfWords;                        // Map to count number of words with each letter
        map<string,int> wordCounts;                         // Map to count number of occurrences of words
        vector<T> indexVector;                              // Index vector
        tree<T> indexTree;                                  // Index Tree
        multimap<T,int> indexMap;
        myheap<T> indexHeap;
        vector<T> elements;                                 // Template vector elements (string, char, int, double)
        vector<int> totals;                                 // Int vector for tallies
};

#endif // UNIQUE_H

template <typename T>
unique<T>::unique()
{
    syllables = words = paragraphs = 0;
    sentences = 1;
    readingLevel = 0.0;
}

template <typename T>
unique<T>::~unique()
{

}

template <typename T>
unique<T>::unique(const unique<T> &other)                   // Copy constructor
{
    indexVector = other.indexVector;
}

template <typename T>
unique<T>& unique<T>::operator=(const unique<T> &other)     // Assignment operator
{
    indexVector = other.indexVector;
    return *this;
}


template <typename T>
void unique<T>::addVector(T &x)                             // Function: add element to vector
{
    indexVector.push_back(x);
}

template<typename R>
istream& operator>>(istream &in, unique<R> &uniqueText)     // Input
{
    R index;
    while(in>>index)
    {
        uniqueText.index(index);
    }
    return in;
}

template<typename T>
void unique<T>::displayVector()                             // Display vector
{
    ofstream outfile ("output.txt");                        // Create ouput file
    outfile << "Approximate reading level: Grade " << readingLevel << endl
            << "Number of words: " << words << endl
            << "Number of sentences: " << sentences << endl
            << "Number of paragraphs: " << paragraphs <<endl
            << endl;

    for(unsigned int i = 0; i < indexVector.size(); i++)
    {
        outfile << indexVector[i] << indexVector[i].name << " appears " << wordCounts[indexVector[i].name] << " times." <<endl<<endl;
    }
    outfile.close();                                        // Close file
    system("start output.txt");                             // Open file for user
}

template<typename T>
void unique<T>::computeReadingLevel()                       //Uses Flesch–Kincaid Grade Level Algorithm
{
    readingLevel = (.39*(double)words/sentences) + (11.8*(double)syllables/words) - 15.59;
}

template<typename T>
void unique<T>::addNumberOfWords(char &x, int y)            // Adds letters to map
{
    typename map<char,int>::iterator it;
    pair<typename map<char,int>::iterator,bool> ret;
    ret = numberOfWords.insert( pair<char,int>(x,y) );
    if ( ret.second == false )                              // Check if element is already in map
    {                                                       // If yes, increment value
        int count = numberOfWords[x];
        count++;
        numberOfWords[x] = count;
    }
}

template<typename T>
void unique<T>::addWordCounts(string &x, int y)             // Adds words to map
{
    typename map<string,int>::iterator it;
    pair<typename map<string,int>::iterator,bool> ret;
    ret = wordCounts.insert( pair<string,int>(x,y) );
    if ( ret.second == false )                              // Check if element is already in map
    {                                                       // If yes, increment value
        int count = wordCounts[x];
        count++;
        wordCounts[x] = count;
    }
}

template<typename T>
void unique<T>::displayTopTen()                             // Display top ten used words
{                                                           // and counts for words of each letter of the alphabet
    map<int,string> newMap;
    typename map<string,int>::iterator it;                  // Create iterator
    for(it = wordCounts.begin(); it != wordCounts.end(); it++)
    {                                                       // Map for top ten words
        newMap.insert( pair<int,string>(it->second,it->first) );
    }

    ofstream outfile ("topTen.txt");                        // Create output file
    outfile << "Top Ten Words Used" << endl << endl
            << setw(15) << "Word" << ": " << "Quantity" << endl << endl;

    typename map<int,string>::reverse_iterator rit;         // Create iterator
    rit = newMap.rbegin();
    for(int i = 0; i < 10; i++)                             // Iterate through map
    {
        outfile << setw(15) <<  rit->second << ": " << rit->first <<  endl << endl;
        rit++;
    }
    outfile << "Number of words beginning with each letter of the alphabet: " <<endl<<endl;
    outfile << setw(15) << "Letter" << ": " << "Quantity" << endl << endl;

    typename map<char,int>::iterator cit;
    for(cit = numberOfWords.begin(); cit !=numberOfWords.end(); cit++)
    {
        outfile << setw(15) <<  cit->first << ": " << cit->second <<endl;
    }

    outfile.close();                                        // Close file
    system("start topTen.txt");                             // Open file for user
}

template<typename T>
void unique<T>::addTree(T &x)
{
    indexTree.push(x);
}

template<typename T>
void unique<T>::addHeap(T &x)
{
    //indexHeap.push(x);
}

template<typename T>
void unique<T>::displayTree()                               // Display tree
{
    ofstream outfile ("output.txt");                        // Create ouput file
    outfile << "Approximate reading level: Grade " << readingLevel << endl
            << "Number of words: " << words << endl
            << "Number of sentences: " << sentences << endl
            << "Number of paragraphs: " << paragraphs <<endl
            << endl;
    outfile.close();                                        // Close file
    system("start output.txt");                             // Open file for user
}

template<typename T>
void unique<T>::displayHeap()                               // Display heap
{
    ofstream outfile ("output.txt");                        // Create ouput file
    outfile << "Approximate reading level: Grade " << readingLevel << endl
            << "Number of words: " << words << endl
            << "Number of sentences: " << sentences << endl
            << "Number of paragraphs: " << paragraphs <<endl
            << endl;
    outfile.close();                                        // Close file
    system("start output.txt");                             // Open file for user
}

template<typename T>
void unique<T>::addMap(T &x)
{
    indexMap.insert( pair<T,int>(x,1) );
}

template<typename T>
void unique<T>::displayMap()
{
    ofstream outfile ("output.txt");                        // Create ouput file
    outfile << "Approximate reading level: Grade " << readingLevel << endl
            << "Number of words: " << words << endl
            << "Number of sentences: " << sentences << endl
            << "Number of paragraphs: " << paragraphs <<endl
            << endl;

    typename multimap<T,int>::iterator it;
    for(it = indexMap.begin(); it !=indexMap.end(); it++)
    {
        word temp = it->first;
        outfile << temp << temp.name << " appears " << wordCounts[temp.name] << " times." <<endl<<endl;
    }
    outfile.close();                                        // Close file
    system("start output.txt");                             // Open file for user
}
