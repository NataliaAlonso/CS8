#ifndef PLAYER_H
#define PLAYER_H
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>


using namespace std;

class player
{
    public:
        player();
        virtual ~player();
        void displayInventory();
        void addInventory(string s);
        void deleteInventory(string s);

    protected:
    private:
        string inventory[6];
        int health;
};

#endif // PLAYER_H
