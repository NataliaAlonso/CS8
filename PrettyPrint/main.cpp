#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

string fileSelection();

int main()
{
    int bracketCount = 0;
    int loopCount = 0;
    int classCount = 0;
    int loopFlag = 0;
    int bracketFlag = 0;
    int pos = 0;
    string file = fileSelection();
    ofstream outfile ("NoWhiteSpace.txt");
    ifstream myfile;                                    // Create ifstream for input
    if (file == "")                                    // If s is empty (default), open demo file string.txt
        myfile.open("test.txt");
    else
        myfile.open(file.c_str());                      // Else open user defined file
    char cstring[131072];
    while ( myfile.good() )
    {

        myfile.getline(cstring,131072);
        string line = cstring;
        pos  = line.find_first_not_of(" ");
        line.erase(0,pos);
        pos  = line.find_first_not_of("\t");
        line.erase(0,pos);
        if((line[0] == 'i' && line[1] == 'f' && (line[2] == ' ' || line[2] == '(') ) || (line[0] == 'f' && line[1] == 'o' && line[2] == 'r' ) || (line[0] == 'e' && line[1] == 'l' && line[2] == 's' && line[3] =='e' ) || (line[0] == 'w' && line[1] == 'h' && line[2] == 'i' && line[3] =='l' && line[4] == 'e' ))
        {
            line.insert(0,"                                        ",(4*loopCount));
            loopCount++;
            line.insert(0,"                                        ",(4*bracketCount));
            loopFlag = 1;
        }
        else
        {
            if(line[0] == '{' || line[0] == '}')
            {
                if(line[0] == '{')
                {
                    bracketFlag=1;
                    line.insert(0,"                                        ",(4*bracketCount));
                    if(loopFlag)
                        line.insert(0,"                                        ",(4*(loopCount-1)));
                    else
                        line.insert(0,"                                        ",(4*(loopCount)));
                    if(line[1] != '}')
                        bracketCount++;
                }
                else
                {
                    bracketCount--;
                    classCount = 0;
                    line.insert(0,"                                        ",(4*bracketCount));
                    line.insert(0,"                                        ",(4*loopCount));
                    if(loopCount)
                    {
                        loopCount--;
                    }
                }
            }
            else
            {
                if(line == "public:" || line == "private:" || line == "protected:")
                {
                    line.insert(0,"                                        ",(4*bracketCount));
                    line.insert(0,"                                        ",(4*loopCount));
                    if(!classCount)
                        classCount++;
                }
                else
                {
                    if(loopCount)
                    {
                        line.insert(0,"                                        ",(4*bracketCount));
                        if(bracketFlag && (bracketCount!=1))
                        {
                             loopCount--;
                             loopFlag=0;
                             bracketFlag=0;
                        }

                        line.insert(0,"                                        ",(4*loopCount));

                        if(loopFlag)
                        {

                            loopCount--;
                            loopFlag=0;
                        }
                    }
                    else
                    {
                        line.insert(0,"                                        ",(4*classCount));
                        line.insert(0,"                                        ",(4*bracketCount));
                    }
                }
            }
        }
        outfile << line << endl;

    }
    outfile.close();
    system ("start NoWhiteSpace.txt");
}

string fileSelection()
{
    string fileName;                                    // String variable to hold user input
    int bad = 0;                                        // Integer for exception handling
    char b;                                             // Character for exception handling
    try
    {
    cout << endl                                        // Prompt user for input file name or default demo file selection
         << "Please enter the name of the file you would like to sort," << endl
         << "or enter demo for the demo file." << endl;
         cin >> fileName;
         if (fileName == "demo")                        // If user selected file, throw b
            throw b;
         ifstream myfile;                               // Create ifstream for user file
         myfile.open(fileName.c_str());                 // Open user file
         if ( !myfile.good() )                          // Check if user file exists
            throw bad;                                  // If not, throw bad
         else                                           // If yes, use file
         {
            cout << "Using file " << fileName << endl;
            return fileName;
         }
    }

    catch(int e)                                        // Exception for non-existant file
    {
        string newFileName;
        cout << "File does not exist. Please re-enter." << endl;
        newFileName = fileSelection();
        return newFileName;
    }

    catch(char c)                                       // Exception for user selection of default demo file
    {
        cout << "You have elected to use the demo files." << endl;
        fileName = "";
        return fileName;
    }
}
