#include "player.h"

player::player()
{
    health = 3;
}

player::~player()
{
    //dtor
}

void player::displayInventory()
{
    cout << "Your inventory: " <<endl;
//    for(int i = 0; i < inventory.size(); i++)
//    {
//        cout << "/t" << inventory[i] << endl;
//    }
}

void player::addInventory(string s)
{

}

void player::deleteInventory(string s)
{

}
