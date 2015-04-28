#include "mixed.h"
#include "fraction.h"
#include <cmath>

mixed::mixed()
{
    whole = 0;
    frac.numerator() = 0;
    frac.denominator() = 1;
}


// Set value of mixed using string input
mixed::mixed(string &token)
{
        unsigned int pos;
        unsigned int pos2;
        int numerator=0;
        int denominator=1;
        int wholeNumber=0;
        pos = token.find_first_of(" ",0);   // Find first space
        pos2 = token.find_first_of("/",0);  // Find first "/"
        string subs;
        if ( pos == pos2)                   // If the positions are equal, then they are not in the line
        {
        wholeNumber = atoi(token.c_str());  // Set whole equal to the string
        }
        else
        {
            if( pos > pos2)                 // If position of space is greater than position of /, then string is a fraction
            {                               // Store fraction

                subs = token.substr(0,pos2);
                numerator = atoi(subs.c_str());
                subs = token.substr(pos2+1,token.length());
                denominator = atoi(subs.c_str());
            }
            else                            // If position of space is less than position of /, then string is a mixed number
            {                               // Store whole number, then store fraction
                subs = token.substr(0,pos);
                wholeNumber = atoi(subs.c_str());
                subs = token.substr(pos+1,pos2);
                numerator = atoi(subs.c_str());
                subs = token.substr(pos2+1,token.length());
                denominator = atoi(subs.c_str());
            }
        }
        if ( denominator > 0 )              // Tests if denominator is negative
        {                                   // If not negative, created mixed number
            whole = wholeNumber;
            fraction newFrac(numerator,denominator);
            frac = newFrac;
            setImproper();
        }
        else                                // If denominator is negative, display error message
        {
            cout << "\nERROR: Negative denominator. Exiting program."<<endl;
            exit(1);
        }
}

mixed::mixed(int w, int n, int d)
{
    whole = w;
    fraction newFrac(n,d);
    frac = newFrac;
    setImproper();
}

mixed::mixed(int w, fraction y)
{
    whole = w;
    fraction newFrac(y.numerator(),y.denominator());
    frac = newFrac;
    setImproper();
}

mixed::~mixed()
{}

mixed::mixed(const mixed &other)
{
    whole = other.whole;
    fraction x = other.frac;
    frac.numerator() = x.numerator();
    frac.denominator() = x.denominator();
    setImproper();
}

mixed::mixed(const fraction &other)
{
    whole = 0;
    frac = other;
    setImproper();
}
/*
mixed& mixed::operator=(mixed &other)
{
    if(this != &other)
    {
        whole = other.whole;
        frac = other.frac;
        setImproper();
    }
    return *this;
}
*/
mixed& mixed::operator=(mixed other)
{
    if(this != &other)
    {
        whole = other.whole;
        frac = other.frac;
        setImproper();
    }
    return *this;
}

mixed& mixed::operator=(fraction &other)
{
    frac = other;
    whole = abs(frac.numerator())/frac.denominator();
    whole *= (frac.numerator() < 0)? -1 : 1;
    frac.numerator() = abs(frac.numerator())%frac.denominator();
    frac.reduce();
    setImproper();
    return *this;
}


void mixed::setValue(int w, int n, int d)
{
    whole = w;
    fraction y(n,d);
    frac = y;
    setImproper();
}

void mixed::setValue(int w, fraction& y)
{
    whole = w;
    frac = y;
    setImproper();
}

void mixed::setValue(string& token)
{
        unsigned int pos;
        unsigned int pos2;
        int numerator=0;
        int denominator=1;
        int wholeNumber=0;
        pos = token.find_first_of(" ",0);   // Find first space
        pos2 = token.find_first_of("/",0);  // Find first "/"
        string subs;
        if ( pos == pos2 )                  // If the positions are equal, then they are not in the line
        {
        wholeNumber = atoi(token.c_str());  // Set whole equal to the string
        }
        else
        {
            if( pos > pos2)                 // If position of space is greater than position of /, then string is a fraction
            {                               // Store fraction
                subs = token.substr(0,pos2);
                numerator = atoi(subs.c_str());
                subs = token.substr(pos2+1,token.length());
                denominator = atoi(subs.c_str());
            }
            else                            // If position of space is less than position of /, then string is a mixed number
            {                               // Store whole number, then store fraction
                subs = token.substr(0,pos);
                wholeNumber = atoi(subs.c_str());
                subs = token.substr(pos+1,pos2);
                numerator = atoi(subs.c_str());
                subs = token.substr(pos2+1,token.length());
                denominator = atoi(subs.c_str());
            }
        }
        if ( denominator > 0 )              // Tests if denominator is negative
        {                                   // If not negative, created mixed number
            whole = wholeNumber;
            fraction newFrac(numerator,denominator);
            frac = newFrac;
            setImproper();
        }
        else                                // If denominator is negative, display error message
        {
            cout << "\nERROR: Negative denominator. Exiting program."<<endl;
            exit(1);
        }
}

fraction& mixed::getFraction()
{
    return improper;
}

void mixed::setImproper()
{
    int num = (abs(whole)*abs(frac.denominator())) + frac.numerator(); // changed from numerator() to num.
    num *= ((whole < 0) ? -1 : 1);
    fraction y(num, frac.denominator());
    improper = y;
}

//I/O friends

istream& operator>>(istream &in, mixed &x)
{
    int w;
    fraction y;
    in>>w>>y;
    x.setValue(w,y);
    return in;
}


ostream& operator<<(ostream &out, mixed x)
{
    out << x.improper;                      // Fraction now displays mixed numbers, fractions, and whole numbers correctly.
	return out;

}

mixed pow(mixed& x, mixed &y)
{
    cout << "Raising to a power!!" <<endl;
    fraction temp(x.improper);
    cout << "Temp is " << temp << endl;
    for(int i = 0; i < y.whole-1; i++)
        temp = temp*x.improper;
    mixed ans(temp);   // Returns mixed number with answer.
    return ans;
}

mixed operator^(mixed& x, mixed &y)
{
    mixed temp(x.improper);
    for(int i = 0; i < y.whole-1; i++)
        temp.improper = temp.improper*x.improper;
    mixed ans(temp.improper);   // Returns mixed number with answer.
    return ans;
}

//Friends that deal with two mixed numbers

mixed operator+(mixed& x, mixed &y)
{
    mixed ans((x.improper + y.improper));   // Returns mixed number with answer.
    return ans;
}


mixed operator/(mixed& x, mixed &y)
{
    mixed ans((x.improper / y.improper));   // Returns mixed number with answer.
   return ans;
}

mixed operator*(mixed& x, mixed &y)
{
    mixed ans((x.improper * y.improper));   // Returns mixed number with answer.
   return ans;
}

mixed operator-(mixed& x, mixed &y)
{
    mixed ans((x.improper - y.improper));   // Returns mixed number with answer.
    return ans;
}

bool operator<(mixed& x, mixed &y)
{
   return x.improper < y.improper;
}

bool operator>(mixed& x, mixed &y)
{
   return x.improper > y.improper;
}

bool operator!=(mixed& x, mixed &y)
{
   return  x.improper != y.improper;
}

bool operator==(mixed& x, mixed &y)
{
   return x.improper == y.improper;
}


bool operator>=(mixed& x, mixed &y)
{
   return x.improper >= y.improper;
}

bool operator<=(mixed& x, mixed &y)
{
   return x.improper <= y.improper;
}
//Friends that deal with a fraction and a mixed number

mixed operator+(fraction &x, mixed &y)
{
    mixed ans((x + y.improper));        // Returns mixed number with answer.
    return ans;
}


mixed operator/(fraction &x, mixed &y)
{
    mixed ans((x / y.improper));        // Returns mixed number with answer.
    return ans;
}

mixed operator*(fraction &x, mixed &y)
{
    mixed ans((x * y.improper));        // Returns mixed number with answer.
    return ans;
}

mixed operator-(fraction &x, mixed &y)
{
    mixed ans((x - y.improper));        // Returns mixed number with answer.
    return ans;
}

bool operator<(fraction &x, mixed &y)
{
    return x < y.improper;
}


bool operator>(fraction &x, mixed &y)
{
    return x > y.improper;
}


bool operator!=(fraction &x, mixed &y)
{
    return x != y.improper;
}


bool operator==(fraction &x, mixed &y)
{
    return x == y.improper;
}



bool operator>=(fraction &x, mixed &y)
{
    return x >= y.improper;
}



bool operator<=(fraction &x, mixed &y)
{
    return x <= y.improper;
}



//Friendss that deal with a mixed and a fraction

mixed operator+(mixed& x, fraction &y)
{
    mixed ans((x.improper + y));        // Returns mixed number with answer.
    return ans;
}


mixed operator/(mixed& x, fraction &y)
{
    mixed ans((x.improper + y));        // Returns mixed number with answer.
    return ans;
}


mixed operator*(mixed& x, fraction &y)
{
    mixed ans((x.improper * y));        // Returns mixed number with answer.
    return ans;
}


mixed operator-(mixed& x, fraction &y)
{
    mixed ans((x.improper + y ));       // Returns mixed number with answer.
    return ans;
}


bool operator<(mixed& x, fraction &y)
{
    return x.improper < y;
}


bool operator>(mixed& x, fraction &y)
{
    return x.improper > y;
}


bool operator!=(mixed& x, fraction &y)
{
    return x.improper != y;
}

bool operator==(mixed& x, fraction &y)
{
    return x.improper == y;
}
bool operator>=(mixed& x, fraction &y)
{
    return x.improper >= y;
}
bool operator<=(mixed& x, fraction &y)
{
    return x.improper <= y;
}
