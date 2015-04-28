#include "parser.h"

parser::parser()            // Default constructor
{
}

parser::~parser()           // Destructor
{
    for(;items.size();)
        items.erase(items.begin());
}

parser::parser(string &data)        // Constructor from string
{
    line = data;
}

parser::parser(const parser& other)     // Copy constructor
{
    line = other.line;
    for(unsigned int i = 0; i < other.items.size(); i++)
        items.push_back(other.items[i]);
}

parser& parser::operator=(const parser& other)          // Assignment operator
{
    if(this != &other)
    {
        line = other.line;
        items.clear();
        for(unsigned int i = 0; i < other.items.size(); i++)
            items.push_back(other.items[i]);
    }
    return *this;
}

parser& parser::operator<<(string& data)        // Get line from data string, parse it
{
    line = data;
    parse();
    return *this;
}//Insertion operator

void parser::input(string& data)
{
    line = data;
    parse();
}

void parser::parse()
{
    int counter = 0;
    unsigned int pos;           // Position of character
    bool redo;                  // Tests whether to redo search loop
    string temp;
    items.clear();              // Clear items stack
    ops.clear();                // Clear operator stack
    while(line.size())
    {
        pos = 0;                // Set position to 0
        redo = true;            // Set testing variable redo to true
        while(redo)
        {
            redo = false;
            pos = line.find_first_not_of("0123456789 ", pos);                       // Find first non-digit character
            if(pos < string::npos)
            {
                switch(line[pos])
                {
                    case '(' : ops.push_back(line.substr(pos,1));                   // If the character is a (, push it onto operator stack
                               line.erase(pos,2);                                   // Erase the character
                               counter++;                                           // Increment counter for left parentheses
                               break;
                    case '*' :
                    case '/' :
                    case '-' :
                    case '^' :
                    case '+' : binaryOp(pos,redo);

                                break;
                    case ')' : items.push_back(line.substr(0,pos));                 // If the character is a ), push the line up to the ) (a number) onto the output stack
                               if (counter == 0)                                    // If counter = 0 (no left parentheses), display error and exit program
                               {
                                    cout << "ERROR: Missing left parenthesis. Exiting program." << endl;
                                    exit(1);
                               }
                               else{
                                   while( ops.back() != "(")                        // While the top of the operator stack is not (
                                   {                                                // Pop the top of the operator stack and push onto the output stack
                                       items.push_back(ops.back());                 // When the top of the stack
                                       ops.pop_back();
                                   }                                                // Once the top of the stack is (, the loop will exit
                                   ops.pop_back();                                  // Pop the ( from the stack, do not store (discard)
                                   line.erase(0,pos+1);
                                   counter--;
                                   }
                                break;
                    default: cout << "ERROR: Illegal operation. Exiting program." << endl; // Default is error message of none of the operator characters are found.
                               exit(1);
                }
            }
            else
            {
                if ( counter == 0 )                                              // Check if there is a left parenthesis left over
                {                                                                // If not, do this
                items.push_back(line);                                           // Pushes final number onto output stack
                line = "";
                counter = 0;                                                     // Clears the line
                while ( !ops.empty() )                                           // Pops all operators off the operator stack onto the output stack
                      {
                      items.push_back(ops.back());
                      ops.pop_back();
                      }
                }
                else                                                             // If there is a left parenthesis left over, then exit with error.
                {
                    cout << "ERROR: Missing right parenthesis. Exiting program. " << endl;
                    exit(1);
                }

            }
        }
    }
}

void parser::binaryOp(unsigned int &pos, bool &redo)
{
    if(line[pos-1] == ' ' && line[pos+1] == ' ')    // If there is a space on either side of the character, it is an operator
    {                                               // Push the line up to the character (a number) onto the output stack
        items.push_back(line.substr(0,pos));
        line.erase(0,pos);                          // Erase the line up to the operator
        pos = 0;                                    // The character should now be in pos 0, so reset pos = 0
        if ( !ops.empty() && (ops.back() == "*" || ops.back() == "/") )
                                                    // If the top of the operator stack is * or /
        {                                           // Pop the top of the stack, push onto the output stack
            items.push_back(ops.back());            // Push the new operator onto the operator stack
            ops.pop_back();
            ops.push_back(line.substr(pos,1));
        }
        else                                        // If the top of the operator stack is not * or /
        {                                           // Push the new operator onto the operator stack
            ops.push_back(line.substr(pos,1));
        }
        line.erase(0,2);                            // Erase the character and the space after it (for aesthetics)
    }
    else
    {
      pos++;
      redo = true;
    }
}

parser& parser::operator>>(string &result)
{
    result = rpnLine;
    return *this;
}//Extraction operator

parser& parser::operator>>(vector<string> &result)
{
    putResult(result);
    return *this;
}//Extraction operator

void parser::result(vector<string> &data)
{
    putResult(data);
}

void parser::putResult(vector<string> &data)
{
    data.clear();
    rpnLine = "";
    for(unsigned int i = 0; i < items.size(); i++)
    {
        rpnLine += items[i] + " ";
        data.push_back(items[i]);
    }
}

