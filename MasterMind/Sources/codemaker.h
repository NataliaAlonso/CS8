#ifndef CODEMAKER_H
#define CODEMAKER_H
#include "codebreaker.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class codemaker
{
    public:
        codemaker();
        virtual ~codemaker();
        codemaker(const codemaker& other);
        codemaker& operator=(const codemaker& other);

        char returnColor(int i);        // Return color
        void generateCode();            // Generate new code
        bool evaluate();                // Evaluate guess
        void prompt(int n);             // Prompt user
        int convertScore(int i, int j); // Convert score to integer
        void userResult(bool b);        // Return user result
        void computerResult( bool b );  // Return computer result
        void getUserInput();            // Get user input
        void computerPrompt(int n);     // Prompt for computer
        int getScore();                 // Get Score
        char guess[4];                  // Guess member variable
        void setGuess(char c,int i);    // Set guess
        void initializeScoreArray();    // Initialize score array
        bool isValid();                 // Check if entry is valid
        bool isGuessValid();                 // Check if entry is valid
        void displayGuess();            // Display guess

    private:
        char code[4];                   // Code member variable
        int score;                      // Score var
        int convertedScore;             // Converted score var
        int peg, color;                 // Peg, color var
        vector < vector<int> > scoreArray;  // Score array to convert score to int
};

#endif // CODEMAKER_H
