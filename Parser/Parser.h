/*
 * Programmers: Ray Luu
 * Username: masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Due Date: December 9, 2013
 * Parser.h
 */

#ifndef Assignment_3_Parser_h
#define Assignment_3_Parser_h

#include "Table.h"

class Parser{
    
public:
    void readFile();
    void run();
    bool validateExp(vector<string> token, FILE *outFile);
    bool validateAssg(vector<string> token, FILE *outFile);
    vector<int>validateParenNoSpace(string eachToken, FILE *outFile);
    vector<int> validateAllParent(vector<string>token,FILE *outFile);
    
private:
    char *fileName;
    vector<string> textContent;
    vector<string>::iterator it;
};

#endif
