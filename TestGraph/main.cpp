#include <iostream>

using namespace std;

string roomArray[5];
char gameArray[5][5];
char getInput();
void initializeGameArray();
void initializeRoomArray();
bool searchArray(int &i, char c);

int main()
{
    int current = 0;
    initializeGameArray();
    initializeRoomArray();
    while(char c = getInput())
    {
        c = toupper(c);
        switch(c)
        {
            case 'N': if(searchArray(current,c))
                      {
                          cout << "HEAD NORTH" <<endl
                               << roomArray[current] <<endl;
                      }
                      else
                        cout << "You can't go that way." <<endl;
                      break;
            case 'S': if(searchArray(current,c))
                      {
                          cout << "HEAD SOUTH" <<endl
                             << roomArray[current] <<endl;
                      }
                      else
                        cout << "You can't go that way." <<endl;
                      break;
            case 'E': if(searchArray(current,c))
                      {
                        cout << "HEAD EAST" <<endl
                             << roomArray[current] <<endl;
                      }
                      else
                        cout << "You can't go that way." <<endl;
                      break;
            case 'W': if(searchArray(current,c))
                      {
                          cout << "HEAD WEST" <<endl
                             << roomArray[current] <<endl;
                      }
                      else
                        cout << "You can't go that way." <<endl;
                      break;
            default: cout << "I have no clue where you're trying to go." <<endl;
                      break;
        }
    }
}

char getInput()
{
    char input;
    cout << "Please enter which way you would like to go. N S E W" <<endl;
    cin >> input;
    return input;
}

void initializeGameArray()
{
    for(int i = 0; i <5; i++)
        for(int j = 0; j < 5; j++)
            gameArray[i][j] = NULL;

    gameArray[0][1] = 'N';
    gameArray[0][3] = 'E';
    gameArray[1][0] = 'S';
    gameArray[1][2] = 'E';
    gameArray[1][4] = 'N';
    gameArray[2][1] = 'W';
    gameArray[2][3] = 'S';
    gameArray[3][0] = 'W';
    gameArray[3][2] = 'N';
    gameArray[4][1] = 'S';
}

bool searchArray(int &i, char c)
{
    for(int j = 0; j < 5; j++)
    {
        if(gameArray[i][j] == c)
        {
            i = j;
            return true;
        }
    }
    return false;
}

void initializeRoomArray()
{
    roomArray[0] = "You are in room 0";
    roomArray[1] = "You are in room 1";
    roomArray[2] = "You are in room 2";
    roomArray[3] = "You are in room 3";
    roomArray[4] = "You are in room 4";
}
