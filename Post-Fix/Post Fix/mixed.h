#ifndef MIXED_H
#define MIXED_H
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "fraction.h"

using namespace std;


class mixed
{
  public:
    mixed();
    mixed(string &x);
    mixed(int w, int n=0, int d=1);
    mixed(int w, fraction y);
    ~mixed();
    mixed(const mixed &other);
    mixed(const fraction &other);
    //mixed& operator=(mixed &other);
    mixed& operator=(mixed other);
    mixed& operator=(fraction &other);
    void setValue(int w, int n, int d);
    void setValue(int w, fraction& y);
    void setValue(string &s);
    fraction& getFraction();


//I/O friends
    friend
    istream& operator>>(istream &in, mixed &x);

    friend
    ostream& operator<<(ostream &out, mixed x);

    friend
    mixed pow(mixed& x, mixed &y);

    friend
    mixed operator^(mixed& x, mixed &y);

//Friends that deal with two mixed numbers
    friend
    mixed operator+(mixed& x, mixed &y); // Corrected "&" reference error/warning

    friend
    mixed operator/(mixed& x, mixed &y); // Corrected "&" reference error/warning

    friend
    mixed operator*(mixed& x, mixed &y); // Corrected "&" reference error/warning

    friend
    mixed operator-(mixed& x, mixed &y); // Corrected "&" reference error/warning

    friend
    bool operator<(mixed& x, mixed &y);

    friend
    bool operator>(mixed& x, mixed &y);

    friend
    bool operator!=(mixed& x, mixed &y);

    friend
    bool operator==(mixed& x, mixed &y);

    friend
    bool operator>=(mixed& x, mixed &y);

    friend
    bool operator<=(mixed& x, mixed &y);


//Friends that deal with a fraction and a mixed number
        friend
        mixed operator+(fraction &x, mixed &y); // Corrected "&" reference error/warning

        friend
        mixed operator/(fraction &x, mixed &y); // Corrected "&" reference error/warning

        friend
        mixed operator*(fraction &x, mixed &y); // Corrected "&" reference error/warning

        friend
        mixed operator-(fraction &x, mixed &y); // Corrected "&" reference error/warning

        friend
        bool operator<(fraction &x, mixed &y);

        friend
        bool operator>(fraction &x, mixed &y);

        friend
        bool operator!=(fraction &x, mixed &y);

        friend
        bool operator==(fraction &x, mixed &y);

        friend
        bool operator>=(fraction &x, mixed &y);

        friend
        bool operator<=(fraction &x, mixed &y);


//Friends that deal with a mixed and a fraction
    friend
    mixed operator+(mixed& x, fraction &y); // Corrected "&" reference error/warning

    friend
    mixed operator/(mixed& x, fraction &y); // Corrected "&" reference error/warning

    friend
    mixed operator*(mixed& x, fraction &y); // Corrected "&" reference error/warning

    friend
    mixed operator-(mixed& x, fraction &y); // Corrected "&" reference error/warning

    friend
    bool operator<(mixed& x, fraction &y);

    friend
    bool operator>(mixed& x, fraction &y);

    friend
    bool operator!=(mixed& x, fraction &y);

    friend
    bool operator==(mixed& x, fraction &y);

    friend
    bool operator>=(mixed& x, fraction &y);

    friend
    bool operator<=(mixed& x, fraction &y);

  private:
    int whole;
    fraction frac, improper;

    void setImproper();
    void convertImproper();
};

#endif // MIXED_H
