/*
Title: Zork!
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef GAME_H
#define GAME_H
#include <cstdlib>
#include <string>
#include <vector>

#include "room.h"

using namespace std;

class game
{
    public:
        game();                                         // Constructor
        ~game();                                        // Destructor
        void initializeTables();                        // Initialize all tables
        void initializeBelowTables();                   // Initialize below adjacency table
        void initializeAboveTables();                   // Initialize above adjacency table
        void initializeMazeTables();                    // Initialize maze adjacency table
        bool searchArray(int &i, char c);               // Search array
        string getInput();                              // Get user input
        void getRoomInfo(int i);                        // Get room information
        void initializeRoomScripts();                   // Initialize room scripts
        void move(char c);                              // Move along graph
        void action(string s);                          // Action to be performed
        void checkSwitch();                             // Check if necessary to switch graphs(levels)
        bool inventorySpace(int &index);                // Test if inventory has space and return index
        bool findInventory(string &val, int &index);    // Find item in inventory
        void removeInventory(int i);                    // Remove item from inventory
        void hadesInstance();                           // Entrance to Hades instance
        void checkTrophy();                             // Check trophy case for win
        void checkCheat(string s);                      // Check for cheat code -> uuddlrlrbas
        int currentRoom, currentLevel;                  // Current room and level numbers
        int getHealth();                                // Return player health
        void checkLantern();                            // Check if room requires lantern

    protected:
    private:
        char below[35][35];                             // Below adjacency table
        char above[21][21];                             // Above adjacency table
        char maze[24][24];                              // Maze adjacency table

        room rbelowRooms[35];                           // Table of below rooms
        room raboveRooms[21];                           // Table of above rooms
        room rmazeRooms[24];                            // Table of maze rooms
        vector<string> trophyCase;                      // Trophy case vector

        string inventory[6];                            // Inventory vector
        int health;                                     // Player health
        bool lantern;                                   // True if lantern is on, false if lantern is off
};

#endif // GAME_H
