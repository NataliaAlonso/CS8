#include "codebreaker.h"
#include "codemaker.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

codemaker::codemaker()
{
    initializeScoreArray();                             // Initialize score array in constructor
}

codemaker::~codemaker()
{
    delete[] code;
    delete[] guess;
    delete &scoreArray;
    delete &score;
    delete &convertedScore;
    delete &peg;
    delete &color;
}

char codemaker::returnColor(int i)                      // Returns color char
{
    char color = '\0';                                  // Initialize color to empty
    switch(i)
    {
        case 1: color = 'R';                            // If 1, return R for RED
                break;
        case 2: color = 'G';                            // If 2, return G for GREEN
                break;
        case 3: color = 'B';                            // If 3, return B for BLUE
                break;
        case 4: color = 'Y';                            // If 4, return Y for YELLOW
                break;
        case 5: color = 'O';                            // If 5, return O for ORANGE
                break;
        case 6: color = 'P';                            // If 6, return P for PURPLE
                break;
    }
    return color;
}

void codemaker::generateCode()                          // Generates code for user player
{
    srand(time(NULL));                                  // Seed for rand()
    for ( int i = 0; i < 4; i++)                        // Create 4 random numbers between
    {                                                   // 1 and 6, pass through returncolor()
        int temp = (rand()%6)+1;                        // Assign one to each code element 1-4
        code[i] = returnColor(temp);
    }
}

bool codemaker::evaluate()                              // Evaluates guess and returns bool value
{                                                       // true if correct, false if incorrect
    int correctPeg = 0;                                 // Correct peg counter
    int correctColor = 0;                               // Correct color counter
    int select = 0;                                     // Select an element
    bool ignore[4];                                     // Bool array to store which elements are correct
    bool ignoreColor[4];                                // Bool array to store which have correct color
    bool inList = false;
    for (int i = 0; i < 4; i++)                         // Set all bool array elements to false
    {
        ignore[i] = false;
        ignoreColor[i] = false;
    }
    for (int i = 0; i < 4; i++)
    {
        if (guess[i] == code[i])                        // If the peg at n is correct
        {
            correctPeg++;                               // Increment correct peg counter
            ignore[i] = true;                           // Change ignore[n] to true
        }
    }
    for (int i = 0; i < 4; i++)                         // Checking if peg is in the code
    {                                                   // but in the wrong position
        if (!ignore[i])
        {
            for (int j = 0; j < 4; j++)
            {
                if (!ignore[j] && i != j)
                {                                       // If guess at n is in code
                    if ((guess[i] == code[j]) && !ignoreColor[j])
                    {
                    inList = true;                      // Set inList to true
                    select = j;                         // Set select to position of peg in code
                    }
                }
            }
            if (inList)                                 // If it is in the list
            {
                correctColor++;                         // Increment correct color counter
                inList = false;                         // Reset inList
                ignoreColor[select] = true;             // Set color array at n to true
            }
        }
    }
    score = convertScore(correctPeg, correctColor);     // Convert score from [n,m] to x
    if ( score == 13)                                   // If the score is 13 ( [4,0] )
    {                                                   // User has won!
        cout << "The score is: [ " << correctPeg << ", " << correctColor << " ]"<< endl << endl;
        return true;                                    // Return true
    }
    else                                                // Otherwise, user has not won :(
    {
        cout << "The score is: [ " << correctPeg << ", " << correctColor<< " ]"<< endl << endl;
        return false;                                   // Return false
    }
}

void codemaker::prompt(int n)                           // Prompt human player for guess
{
    do{
        cout << "\n" << n << " guesses left!! Enter guess:";
        cin >> guess[0] >> guess[1] >> guess [2] >> guess [3];
        for(int i = 0; i < 4; i++)                          // Get guess and convert to uppercase
        {
            guess[i] = toupper(guess[i]);
        }
    }while(!isGuessValid());
}

int codemaker::convertScore(int i, int j)               // Convert score from [n,m] to x
{
    peg = i;
    color = j;
    convertedScore = scoreArray[i][j];                  // Get score value from scoreArray
    return convertedScore;                              // Return converted score
}

void codemaker::userResult( bool b )                    // Display win or lose for player
{
    if(b)
        cout << "You win! The correct sequence was " << code[0] << " " << code[1]
             << " " << code[2] << " " << code[3] << endl;
    else
        cout << "You lost! :( The correct sequence was " << code[0] << " " << code[1]
             << " " << code[2] << " " << code[3] << endl;
}

void codemaker::computerResult( bool b )                // Display win or lose for computer
{
    if(b)
        cout << "Computer wins!" <<endl;
    else
        cout << "Computer lost! :( " <<endl;            // How sad, the computer is not that bright. :(
}

void codemaker::getUserInput()                          // Prompt user for code
{
    do{
    cout << "Please enter your code and the computer will try to break it:";
    cin >> code[0] >> code[1] >> code[2] >> code[3];
    for(int i = 0; i < 4; i++)                          // Get code and convert to uppercase
    {
        code[i] = toupper(code[i]);
    }
    }while(!isValid());                                 // Do while input is valid
}

void codemaker::computerPrompt(int n)                   //
{
    cout <<"\n"<< n << " guesses left!!" << guess[0] << " " << guess[1] << " " << guess[2] << " " << guess[3] << "\n";
}

int codemaker::getScore()                               // Gets score
{
    return score;
}

void codemaker::setGuess(char c, int i)                 // Set guess
{
    guess[i] = c;
}

void codemaker::initializeScoreArray()                  // Initialize score array for
{                                                       // converting score from pair
    scoreArray.resize(14);                              // to int
    for (int i = 0; i < 14; ++i)
    {
        scoreArray[i].resize(2);
    }
    scoreArray[0][0] = 0;
    scoreArray[0][1] = 1;
    scoreArray[1][0] = 2;
    scoreArray[0][2] = 3;
    scoreArray[1][1] = 4;
    scoreArray[2][0] = 5;
    scoreArray[0][3] = 6;
    scoreArray[1][2] = 7;
    scoreArray[2][1] = 8;
    scoreArray[3][0] = 9;
    scoreArray[0][4] = 10;
    scoreArray[1][3] = 11;
    scoreArray[2][2] = 12;
    scoreArray[4][0] = 13;
}

bool codemaker::isValid()                               // Check if input is valid
{
    bool result;                                        // Bool variable for return
    string codeString;                                  // String to store code for comparison
    for( unsigned int i = 0; i < 4; i++)
    {
        codeString.push_back(code[i]);
    }
    for( unsigned int i = 0; i < 6; i++)                // Search for valid chars
    {
        int pos = codeString.find_first_not_of("RGBYOP",0);
        if ( codeString.length()!= 4 || pos!=-1)       // If all are not valid, display error
        {                                               // and return false
            cout << "Invalid code. Please re-enter." << endl;
            result = false;
            break;
        }
        else                                            // Otherwise return true
            result = true;
    }
    return result;
}

bool codemaker::isGuessValid()                               // Check if input is valid
{
    bool result;                                        // Bool variable for return
    string codeString;                                  // String to store code for comparison
    for( unsigned int i = 0; i < 4; i++)
    {
        codeString.push_back(guess[i]);
    }
    for( unsigned int i = 0; i < 6; i++)                // Search for valid chars
    {
        int pos = codeString.find_first_not_of("RGBYOP",0);
        if ( codeString.length()!= 4 || pos!=-1)       // If all are not valid, display error
        {                                               // and return false
            cout << "Invalid code. Please re-enter." << endl;
            result = false;
            break;
        }
        else                                            // Otherwise return true
            result = true;
    }
    return result;
}

void codemaker::displayGuess()
{
    cout << guess[0] << " " << guess[1] << " " << guess[2] << " " << guess[3] << "\n";
}
