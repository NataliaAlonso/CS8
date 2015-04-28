#ifndef PARSER_H
#define PARSER_H


struct parser
{

    parser();

    void getInput();
    void removeWhitespace();
    void addWhitespace();
    void checkIf();
    void checkFor();

    int bracketCount();
};

parser()
{

}


#endif // PARSER_H
