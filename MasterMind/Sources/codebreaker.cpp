#include "codebreaker.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

codebreaker::codebreaker()
{
    initializeBreakerScoreArray();                          // Initialize score array in constructor
}

codebreaker::~codebreaker()
{
    delete []CFG;
    delete []guess;
    delete &breakerScoreArray;
    delete &colorArray;
    delete &guessArray;
}

codebreaker::codebreaker(const codebreaker& other)
{
    for(int i = 0; i <4; i++)
    {
        guess[i] = other.guess[i];
    }
    tempScore = other.tempScore;
    score = other.score;
    colorArray = other.colorArray;
    guessArray = other.guessArray;
}

codebreaker& codebreaker::operator=(const codebreaker& other)
{
    if (this == &other) return *this;
    for(int i = 0; i <4; i++)
    {
        guess[i] = other.guess[i];
    }
    colorArray = other.colorArray;
    guessArray = other.guessArray;
    initializeColorArray();
    return *this;
}


char codebreaker::returnColor(int i)                    // Returns color char
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

void codebreaker::createFirstGuess()                    // Create first computer guess
{
    srand(time(NULL));                                  // Seed for rand()
    score = 0;                                          // Set all member vars to 0
    keep = 0;
    move = 0;
    for(int i = 0; i <4; i++)                           // Set all guess arrays to empty
    {
        guess[i] = '\0';
        CFG[i] = '\0';
    }
    initializeColorArray();                             // Initialize color array back to all colors
    for ( int i = 0; i < 4; i++)                        // Create random guess
    {
        int temp = (rand()%6)+1;                        // Select a random int from 1 to 6
        guess[i] = returnColor(temp);                   // Pass through returnColor()
    }
    assignCFG();                                        // Assign code to CFG
 }

void codebreaker::createGuess()                         // Create a guess
{
    bool repeat = true;                                 // Set bool repeat to true
    int count=0;
    while(repeat)                                       // While repeat is true
    {
        count++;
        repeat = false;                                 // Set repeat to false
        if(compareScore(tempScore))                     // Compare new score to previous score
        {                                               // If new score is higher
            assignCFG();                                // Assign new CFG
        }
        else                                            // Else use CFG
        {
            assignGuess();
        }
        setActions();                                   // Set actions to perform
        performActions();                               // Perform actions
        repeat = compareGuess();                        // Compare guess to previous guesses
    }                                                   // If reused, set repeat to true
}                                                       // Else, submit new guess

void codebreaker::assignCFG()                           // Make current guess the new CFG
{
    for( int i = 0; i < 4; i++ )
        {
            CFG[i] = guess[i];
        }
}

void codebreaker::assignGuess()                         // Put CFG back into guess for processing
{
    for( int i = 0; i < 4; i++ )
    {
        guess[i] = CFG[i];
    }
}

void codebreaker::getScore(int s)                       // Get new score
{
    tempScore = s;
}

void codebreaker::storeGuess()                          // Store guess to check for duplicates
{
    string code;
    for( unsigned int i = 0; i < 4; i++ )               // Create string from guess
    {
        code.push_back(guess[i]);
    }
    guessArray.push_back(code);                         // Push back string to array
}

bool codebreaker::compareScore( int s )                 // Compare new score to previous high score
{
    bool compare;
    compare = ( (s>=score) && s!=0 );                   // Compare scores
    if( s == 0 )                                        // If new score is 0
        {                                               // Remove colors from color array
            removeColor();
        }
    if( compare )                                       // If new score is higher than previous
        {                                               // Set new score as high score
            score = s;
        }
    return compare;                                     // Return new score > high score
}

bool codebreaker::compareGuess()                        // Search guess array for duplicates
{
    bool same = false;                                  // Set bool same to false
    string code;
    for( unsigned int i = 0; i < 4; i++)                // Create string from guess
    {
        code.push_back(guess[i]);
    }
    for( unsigned int j = 0; j < guessArray.size(); j++)
    {                                                   // Compare string to guess array
        if( guessArray[j] == code )                     // If string is present, set same to true
        {
            same = true;
        }
    }
    return same;                                        // Return same
}

 void codebreaker::removeColor()                        // Remove color from color array
 {
    for(unsigned int i=0; i < 4; i++)
    {
        for(unsigned int j = 0; j < colorArray.size(); j++)
        {
            if( guess[i] == colorArray[j] )
            {
                colorArray.erase(colorArray.begin()+j);
            }
        }
    }
 }

 void codebreaker::setActions()                         // Set actions based on new score
 {                                                      // Set number of pegs to keep
    switch(score)                                       // Set number of pegs to move
    {
    case 0: keep = 0;
            move = 0;
            break;
    case 1: keep = 0;
            move = 1;
            break;
    case 2: keep = 1;
            move = 0;
            break;
    case 3: keep = 0;
            move = 2;
            break;
    case 4: keep = 1;
            move = 1;
            break;
    case 5: keep = 2;
            move = 0;
            break;
    case 6: keep = 0;
            move = 3;
            break;
    case 7: keep = 1;
            move = 2;
            break;
    case 8: keep = 2;
            move = 1;
            break;
    case 9: keep = 3;
            move = 0;
            break;
    case 10: keep = 0;
            move = 4;
            break;
    case 11: keep = 1;
            move = 3;
            break;
    case 12: keep = 2;
            move = 2;
            break;
    case 13: keep = 4;
            move = 0;
            break;
    }
 }

bool codebreaker::checkGuessElement(int i)              // Check if guess element is in color array
{
    bool result;
    for( unsigned int j = 0; j < colorArray.size(); j++ )
    {
        if( (guess[i] == colorArray[j]) )               // If element is in color array
        {                                               // Set result to true
            result= true;
            break;
        }
        else                                            // Else set result to false
        {
            result= false;
        }
    }
    return result;                                      // Return result
}


void codebreaker::performActions()                      // Perform actions to create new guess
{
    srand(time(NULL));
    bool ignore[4];                                     // Bool array of elements to ignore
    bool swapArray[4];                                  // Bool array of elements already swapped
    for ( int i = 0; i < 4; i++ )                       // Set all bool array elements to false
    {
        ignore[i] = false;
        swapArray[i] = false;
    }
    if( move == 4 )                                     // If move is 4, all pegs are kept, all pegs are move
    {
        int select = 0;                                 // Set variables to 0
        int swap = 0;
        int swap2 = 0;
        char tempSelect;
        while( ignore[select] == true )                 // While element at select has not been changed
        {
            select = rand()%4;                          // Select number from 1-4
        }
        while( ignore[swap] == true || swap == select ) // If ignore at the swap choice has been change or if
        {                                               // swap choice is equal to element selected
            swap = rand()%4;                            // choose new number from 1-4 and repeat until valid
        }
        while( ignore[swap2] == true || swap2 == select || swap2 == swap )
        {                                               // Same as above, this time for a third selection
            swap2 = rand()%4;
        }
        tempSelect = guess[select];                     // Temp var gets element at select
        guess[select] = guess[swap2];                   // Guess at select gets guess at swap2
        guess[swap2] = guess[swap];                     // Guess at swap2 gets guess at swap
        guess[swap] = tempSelect;                       // Guess at swap gets guess at select
        ignore[select] = true;                          // Set all changed elements in ignore array to trye
        ignore[swap] = true;
        ignore[swap2] = true;
        for ( int i = 0; i < 4; i++ )                   // Set all bool array elements to true
        {
            ignore[i] = true;
        }
    }
    if ( move == 3 )                                    // Same as above for 3 move elements
    {
        int select = 0;
        int swap = 0;
        int swap2 = 0;
        char tempSelect;
        while( ignore[select] == true )
        {
            select = rand()%4;
        }
        while( ignore[swap] == true || swap == select )
        {
            swap = rand()%4;
        }
        while( ignore[swap2] == true || swap2 == select || swap2 == swap )
        {
            swap2 = rand()%4;
        }
        tempSelect = guess[select];
        guess[select] = guess[swap2];
        guess[swap2] = guess[swap];
        guess[swap] = tempSelect;
        ignore[select] = true;
        ignore[swap] = true;
        ignore[swap2] = true;
        for ( int i = 0; i < keep; i++ )                // If keep is 1
        {
            int select = 0;
            select = rand()%4;
            while ( ignore[select] == true )            // Select last unignored element
            {                                           // Set to true
                select = rand()%4;
            }
            ignore[select] = true;
        }
    }
    if ( move == 2 )                                    // Same as above for 2 move elements
    {
        int select = 0;
        int swap = 0;
        char tempSelect;
        while( ignore[select] == true )
        {
            select = rand()%4;
        }
        while( ignore[swap] == true || swap == select )
        {
            swap = rand()%4;
        }
        tempSelect = guess[select];
        guess[select] = guess[swap];
        guess[swap] = tempSelect;
        ignore[select] = true;
        ignore[swap] = true;

        for ( int i = 0; i < keep; i++ )
        {
            int select = 0;
            select = rand()%4;
            while ( ignore[select] == true )
            {
                select = rand()%4;
            }
            ignore[select] = true;
        }
    }
    if( move < 2 )                                      // Same as above if move is 0 or 1
    {
        for ( int i = 0; i < keep; i++ )
        {
            int select = 0;
            select = rand()%4;
            while ( ignore[select] == true )
            {
                select = rand()%4;
            }
            ignore[select] = true;
        }
        if ( move == 1 )
        {
            int select = 0;
            int swap = 0;
            while( ignore[select] == true )
            {
                select = rand()%4;
            }
            while( ignore[swap] == true || swap == select )
            {
                swap = rand()%4;
            }
            guess[select] = guess[swap];
            ignore[select] = true;
        }
    }
    for(int k = 0; k < 4; k++)                          // Check if kept elements are in color array
    {
        if ( ignore[k] == true )
        {
            ignore[k] = checkGuessElement(k);
        }
    }
    for (int m = 0; m < 4; m++)                         // Change element to new random color
    {
        if ( ignore[m] == false )
        {
            int temp = (rand()%colorArray.size());      // Create random number between 1 and size
            if ( guess[m] != colorArray[temp] )         // of color array
            {                                           // As long as guess is different from selected
                 guess[m] = colorArray[temp];           // value, assign new value to guess
            }
            else                                        // Otherwise, assign one element over in colorarray
            {
                int tempCA;
                tempCA = colorArray.size()-1;
                guess[m] = colorArray[tempCA-temp];
            }
        }
    }
}

void codebreaker::initializeColorArray()                // Initialize colorarray with color chars
{
    for(unsigned int i = 0; i < colorArray.size(); i++)
        colorArray.pop_back();
    colorArray.push_back('P');
    colorArray.push_back('R');
    colorArray.push_back('G');
    colorArray.push_back('B');
    colorArray.push_back('Y');
    colorArray.push_back('O');
}

char codebreaker::getBreakerGuess(int i)                // Return codebreaker guess
{
    char c = guess[i];
    return c;
}

void codebreaker::displayGuess()                        // Displays guess
{
    cout << guess[0] << " " << guess[1] << " " << guess[2] << " " << guess[3] << "\n";
}

void codebreaker::initializeBreakerScoreArray()         // Initialize score array for
{                                                       // for converting score to
    breakerScoreArray.resize(14);                       // int
    for (int i = 0; i < 14; ++i)
    {
        breakerScoreArray[i].resize(2);
    }
    breakerScoreArray[0][0] = 0;
    breakerScoreArray[0][1] = 1;
    breakerScoreArray[1][0] = 2;
    breakerScoreArray[0][2] = 3;
    breakerScoreArray[1][1] = 4;
    breakerScoreArray[2][0] = 5;
    breakerScoreArray[0][3] = 6;
    breakerScoreArray[1][2] = 7;
    breakerScoreArray[2][1] = 8;
    breakerScoreArray[3][0] = 9;
    breakerScoreArray[0][4] = 10;
    breakerScoreArray[1][3] = 11;
    breakerScoreArray[2][2] = 12;
    breakerScoreArray[4][0] = 13;
}

void codebreaker::setKeep(int i)                        // Set keep value
{
    keep=i;
}
void codebreaker::setMove(int i)                        // Set move value
{
    move=i;
}
