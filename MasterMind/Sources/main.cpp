// CS3A Winter 2012 - Final Project - Mastermind Simulation with Simple "A.I."
// Created by Natalia Alonso
// Notes written in comments of source files

#include "codebreaker.h"
#include "codemaker.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

char displayInstructions();                     // Display instructions for game
char gameSelection();                           // Choose to be codemaker or codebreaker
void playGameB(codemaker &game);                // Create codebreaker game
void playGameM(codemaker &game, codebreaker &newGame);  // Create codemaker game
void getGuess(codebreaker &cb, codemaker &g);   // Get guess from computer player

int main()
{
    while(1)
    {
        codemaker * gameptr;                    // Create pointer for new codemaker
        gameptr = new codemaker();
        codebreaker * newGameptr;               // Create pointer for new codebreaker
        newGameptr = new codebreaker();
        char userChoice = displayInstructions();// Display instructions for game, return user choice
        switch(userChoice)                      // Use userchoice to start game
        {
            case 'B': playGameB(*gameptr);
                      break;
            case 'M': playGameM(*gameptr, *newGameptr);
                      break;
            case 'Q': exit(0);
                      break;
        }
        delete &gameptr;                        // Delete pointers
        delete &newGameptr;
    }
}

char displayInstructions()
{
    char selection;
    try{
    cout << endl;
    cout<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=MASTERMIND=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl
        << "The goal is to use logic to correctly guess a four color combination" << endl
        << "   based on previous guesses. Everytime a guess is submitted, the   " << endl
        << "  player receives a score. The first number in the score tells how  " << endl
        << "  many pegs are in the right place. The second number will tell how " << endl
        << "      many pegs are the correct color, but in the wrong place.      " << endl
        << "  Guesses are submitted by entering the first letter of each color. " << endl
        << "    The colors are: Red, Green, Blue, Purple, Yellow, and Orange.   " << endl
        << "      For example, a sample guess will look like this: R G B Y      " << endl
        << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
        selection = gameSelection();                                    // Select game
        if ( selection != 'B' && selection !='M' && selection !='Q' )   // Exception for invalid entry
            throw selection;                                            // If error, then throw exception
        else
            return selection;                                           // If no error, return selection
    }
    catch(char c)                                                       // Error message
    {
        char selection;
        cout << "Your selection is invalid. Please choose again." << endl;
        selection = gameSelection();
        return selection;
    }
}

char gameSelection()                                                    // Game selection
{
    char selection;
    cout << "\nPlease select if you would like to be the codebreaker or the codemaker,"<<endl
         << "or choose Q to quit." << endl
         << " B: Codebreaker"<< endl
         << " M: Codemaker" << endl
         << " Q: Quit" << endl;
        cin >> selection;
        selection = toupper(selection);
        return selection;
}

void playGameB(codemaker &game)                                         // Codebreaker game
{
    bool win;                                                           // Boolean to detemine win
    int guesses;                                                        // Guess counter
    cout << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=MASTERMIND=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl
         << "     You have ten tries to correctly guess my code. Goodluck!       " << endl
         << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    win = false;                                                        // Set win bool to false
    guesses = 10;                                                       // Initiate guess counter to 10
    game.generateCode();
    while( !win && guesses > 0)                                         // While there are guesses left
    {                                                                   // and win is false
        game.prompt(guesses);                                           // Prompt user for guess
        win = game.evaluate();                                          // Evaluate guess to detemine win
        guesses--;                                                      // Decrement guess counter
    }                                                                   // Repeat if win==false && guess > 0
    game.userResult(win);                                               // Else, display user result
}

void playGameM(codemaker &game, codebreaker &newGame)                   // Codemaker game
{                                                                       // Computer codebreaker
    bool win;                                                           // Boolean to detemine win
    int guesses;                                                        // Guess counter
    cout << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=MASTERMIND=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl
         << "     The computer has ten tries to correctly guess your code!       " << endl
         << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    game.getUserInput();                                                // Get user-generated code
    newGame.createFirstGuess();                                         // Create first computer guess
    win = false;                                                        // Set win bool to false
    guesses = 10;                                                       // Initiate guess counter to 10
    while( !win && guesses > 0)                                         // While there are guesses left
    {
        newGame.storeGuess();                                           // Store computer's guess
        cout<< "Computer has " << guesses << " guesses left. New guess: ";
        getGuess(newGame,game);                                         // Get computer's guess
        game.displayGuess();                                            // Display computer's guess
        win = game.evaluate();                                          // Evaluate guess to detemine wine
        if ( win == true )                                              // If win==true, then exit loop
        {
            break;
        }
        newGame.getScore(game.getScore());                              // Else, display score
        newGame.createGuess();                                          // Create new computer guess
        guesses--;                                                      // Decrement guess
    }                                                                   // Repeat if win==false && guess > 0
    game.computerResult(win);                                           // Else, display computer result
}

void getGuess(codebreaker &cb, codemaker &g)                            // Get guess function takes two parameters
{                                                                       // Codebreaker and codemaker (evaluator)
    for(int i = 0; i < 4; i++)                                          // Copy codebreaker guess member variable
    {                                                                   // to codemaker guess member variable
        g.setGuess(cb.getBreakerGuess(i), i);
    }
}
