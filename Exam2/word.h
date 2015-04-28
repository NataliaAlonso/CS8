/*
Title: The Editor's Dream
Author: Natalia Alonso
Class: CS8, Spring 2012
*/

#ifndef WORD_H
#define WORD_H
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class word
{
    public:
        word();
         word(string &w, int &p, int &l, int &size);
                                                    /** Default destructor */
        ~word();
                                                    /** Copy constructor
                                                     *  \param other Object to copy from
                                                     */
        word(const word& other);
                                                    /** Assignment operator
                                                     *  \param other Object to assign from
                                                     *  \return A reference to this
                                                     */
        word& operator=(const word& rhs);
                                                    /** Access paragraph
                                                     * \return The current value of paragraph
                                                     */
        int getParagraph() { return paragraph; }
                                                    /** Access line
                                                     * \return The current value of line
                                                     */
        int getSentence() { return sentence; }
                                                    /** Access length
                                                     * \return The current value of length
                                                     */
        int getLength() { return length; }

        void copy(const word& other);
        void display();
        void setParagraph(int s);
        void setSentence(int s);
        void setLength(int s);

        friend
        ostream& operator<<(ostream& out, word& x);

        friend
        bool operator==(word x, word y)
        {
            return x.name == y.name;
        }

        friend
        bool operator>(word x, word y)
        {
                return x.name > y.name;
        }

        friend
        bool operator<(word x, word y)
        {
                return x.name < y.name;
        }

        friend
        bool operator!=(word x, word y)
        {
                return x.name != y.name;
        }

        friend
        bool operator>=(word x, word y)
        {
                return x.name >= y.name;
        }

        friend
        bool operator<=(word x, word y)
        {
                return x.name <= y.name;
        }

        string name;

    private:
        int paragraph;                              //!< Member variable "paragraph"
        int sentence;                               //!< Member variable "line"
        int length;                                 //!< Member variable "length"

};

#endif // WORD_H
