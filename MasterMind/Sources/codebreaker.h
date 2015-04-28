#ifndef CODEBREAKER_H
#define CODEBREAKER_H
#include "codemaker.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;


class codebreaker
{
    public:
        codebreaker();
        virtual ~codebreaker();
        codebreaker(const codebreaker& other);
        codebreaker& operator=(const codebreaker& other);

        char returnColor(int i);        // Returns color
        void createFirstGuess();        // Create first guess
        void createGuess();             // Create subsequent guesses
        void assignCFG();               // Assign CFG
        void assignGuess();             // Assign guess
        void getScore(int score);       // Get score
        void storeGuess();              // Store current guess
        bool compareScore(int s);       // Compare new score to high score
        bool compareGuess();            // Compare new guess to previous guesses
        void removeColor();             // Remove color from color array
        void setActions();              // Set actions
        bool checkGuessElement(int i);  // Check if guess element is in color array
        void performActions();          // Perform actions
        char getBreakerGuess(int i);    // Get guess
        void initializeColorArray();    // Reset color array
        void displayGuess();            // Display guess
        char guess[4];                  // Guess member variable
        void initializeBreakerScoreArray();     // Initialize score array
        void setKeep(int i);            // Set keep
        void setMove(int i);            // Set move

    private:
        char CFG[4];                    // Current favorite guess
        int keep, move;                 // Keep, move vars
        int score, tempScore;           // Score, tempScore vars
        vector<char> colorArray;        // Color array
        vector<string> guessArray;      // Guess array for previous guesses
        vector < vector<int> > breakerScoreArray;   // Score array to convert score to int
};

#endif // CODEBREAKER_H
