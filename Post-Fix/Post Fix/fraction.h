#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class fraction
{
  public:
//      fraction();
      fraction(int n = 0, int d = 1);
      ~fraction();
      fraction(const fraction& other);
      fraction& operator=(const fraction &other);
      void getValue();
      fraction setValue(int n, int d);
      int& numerator();
      int& denominator();

      void display();
      void add(fraction &x, fraction &y);
      void addToMe(fraction &other);
      void operator+=(fraction &other);//x.addToMe(y);
      fraction operator-();

      friend
      istream& operator>>(istream &in, fraction& x);

      friend
      ostream& operator<<(ostream& out, fraction& x);

      friend
      fraction operator+(fraction& x, fraction &y); // Corrected "&" reference error/warning

      friend
      fraction operator-(fraction& x, fraction &y); // Corrected "&" reference error/warning

      friend
      fraction operator*(fraction& x, fraction &y); // Corrected "&" reference error/warning

      friend
      fraction operator/(fraction& x, fraction &y); // Corrected "&" reference error/warning

      friend
      bool operator==(fraction& x, fraction &y);

      friend
      bool operator>(fraction& x, fraction &y);

      friend
      bool operator<(fraction& x, fraction &y);

      friend
      bool operator!=(fraction& x, fraction &y);

      friend
      bool operator>=(fraction& x, fraction &y);

      friend
      bool operator<=(fraction& x, fraction &y);

      void reduce();

protected:

private:
      int num, denom;
      int gcd(int p, int q);
};

#endif // FRACTION_H
