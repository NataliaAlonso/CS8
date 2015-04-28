#include "word.h"

word::word()
{

}

word::word(string &w, int &p, int &l, int &size)
{
    name = w;
    paragraph = p;
    sentence = l;
    length = size;
}

word::~word()
{
    //dtor
}

word::word(const word& other)
{
    copy(other);
}

word& word::operator=(const word& rhs)
{
    if (this == &rhs)
        return *this;                               // handle self assignment
    copy(rhs);                                       //assignment operator
    return *this;
}

void word::copy(const word& other)
{
    name = other.name;
    paragraph = other.paragraph;
    sentence = other.sentence;
    length = other.length;
}

void word::display()
{
    cout << "Word: " << name << endl
         << "Paragraph: " << paragraph <<endl
         << "Sentence: " << sentence << endl;
}

void word::setParagraph(int s)
{
    paragraph = s;
}

void word::setSentence(int s)
{
    sentence = s;
}

void word::setLength(int s)
{
    length = s;
}

ostream& operator<<(ostream& out, word& x)
{
    out << "Word: " << x.name << endl
        << "Paragraph: " << x.paragraph <<endl
        << "Sentence: " << x.sentence << "\n" << endl;
    return out;
}

bool operator==(word& x, word &y)
{
    return x.name == y.name;
}

bool operator>(word& x, word &y)
{
        return x.name > y.name;
}


bool operator<(word& x, word &y)
{
        return x.name < y.name;
}

bool operator!=(word& x, word &y)
{
        return x.name != y.name;
}

bool operator>=(word& x, word &y)
{
        return x.name >= y.name;
}

bool operator<=(word& x, word &y)
{
        return x.name <= y.name;
}
