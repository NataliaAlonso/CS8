#include "stackParser.h"

stackParser::stackParser()            // Default constructor
{
}

stackParser::~stackParser()           // Destructor
{
    items.erase();
}

stackParser::stackParser(string &data)        // Constructor from string
{
    line = data;
}

stackParser::stackParser(const stackParser& other)     // Copy constructor
{
    line = other.line;
//    items = other.items;
}

stackParser& stackParser::operator=(const stackParser& other)          // Assignment operator
{
    if(this != &other)
    {
        line = other.line;
        items.erase();
//        items = other.items;
    }
    return *this;
}

stackParser& stackParser::operator<<(string& data)        // Get line from data string, parse it
{
    line = data;
    parse();
    return *this;
}//Insertion operator

void stackParser::input(string& data)
{
    line = data;
    parse();
}

void stackParser::parse()
{
    int counter = 0;
    unsigned int pos;           // Position of character
    bool redo;                  // Tests whether to redo search loop
    string temp;
    items.erase();              // Clear items stack
    ops.erase();                // Clear operator stack
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
                    case '(' : ops.push(line.substr(pos,1));                   // If the character is a (, push it onto operator stack
                               line.erase(pos,2);                                   // Erase the character
                               counter++;                                           // Increment counter for left parentheses
                               break;
                    case '*' :
                    case '/' :
                    case '-' :
                    case '^' :
                    case '+' : binaryOp(pos,redo);

                                break;
                    case ')' : items.push(line.substr(0,pos));                 // If the character is a ), push the line up to the ) (a number) onto the output stack
                               if (counter == 0)                                    // If counter = 0 (no left parentheses), display error and exit program
                               {
                                    cout << "ERROR: Missing left parenthesis. Exiting program." << endl;
                                    exit(1);
                               }
                               else{
                                   while( ops.top() != "(")                        // While the top of the operator stack is not (
                                   {                                                // Pop the top of the operator stack and push onto the output stack
                                       items.push(ops.top());                 // When the top of the stack
                                       ops.pop();
                                   }                                                // Once the top of the stack is (, the loop will exit
                                   ops.pop();                                  // Pop the ( from the stack, do not store (discard)
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
                {
                    cout << " FINAL " <<line <<endl;                                                           // If not, do this
                    items.push(line);
                    cout << items.top() <<endl;                                           // Pushes final number onto output stack
                    line = "";
                    counter = 0;                                                     // Clears the line
                    while ( !ops.empty() )                                           // Pops all operators off the operator stack onto the output stack
                    {
                        items.push(ops.top());
                        cout << items.top() <<endl;
                        ops.pop();
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

void stackParser::binaryOp(unsigned int &pos, bool &redo)
{
    if(line[pos-1] == ' ' && line[pos+1] == ' ')    // If there is a space on either side of the character, it is an operator
    {
                                                    // Push the line up to the character (a number) onto the output stack
        items.push(line.substr(0,pos));
        line.erase(0,pos);                          // Erase the line up to the operator
        cout << "LINE" <<line <<endl;
        pos = 0;                                    // The character should now be in pos 0, so reset pos = 0
        if ( !ops.empty() && (ops.top() == "*" || ops.top() == "/") )
                                                    // If the top of the operator stack is * or /
        {                                           // Pop the top of the stack, push onto the output stack
            items.push(ops.top());            // Push the new operator onto the operator stack
            ops.pop();
            ops.push(line.substr(pos,1));
        }
        else                                        // If the top of the operator stack is not * or /
        {                                           // Push the new operator onto the operator stack
            ops.push(line.substr(pos,1));
        }
        line.erase(0,2);                            // Erase the character and the space after it (for aesthetics)
    }
    else
    {
      pos++;
      redo = true;
    }
}

stackParser& stackParser::operator>>(string &result)
{
    result = rpnLine;
    return *this;
}//Extraction operator

stackParser& stackParser::operator>>(mystack<string> &result)
{
    putResult(result);
    return *this;
}//Extraction operator

void stackParser::result(mystack<string> &data)
{
    putResult(data);
}

void stackParser::putResult(mystack<string> &data)
{
    data.erase();
    rpnLine = "";
    int size = items.sizeOf();
    mystack<string> temp;
    for(int i = 0; i < size; i++)
    {
        temp.push(items.top());
        data.push(items.top());
        items.pop();
    }
    for(int i = 0; i < size; i++)
    {
        rpnLine += temp.top() + " ";
        temp.pop();
    }
}

