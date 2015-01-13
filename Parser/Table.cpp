/*
 * Programmers: Ray Luu
 * Username: masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Due Date: December 9, 2013
 * Table.cpp
 */

#include "Table.h"

struct characters {
    char character_aToZ;
};

const struct characters characterTable [] = {
    { 'a' },   { 'b' },    { 'c' },    { 'd' },
    { 'e' },   { 'f' },    { 'g' },    { 'h' },
    { 'i' },   { 'j' },    { 'k' },    { 'l' },
    { 'm' },   { 'n' },    { 'o' },    { 'p' },
    { 'q' },   { 'r' },    { 's' },    { 't' },
    { 'u' },   { 'v' },    { 'w' },    { 'x' },
    { 'y' },   { 'z' },    { 'A' },    { 'B' },
    { 'C' },   { 'D' },    { 'E' },    { 'F' },
    { 'G' },   { 'H' },    { 'I' },    { 'J' },
    { 'K' },   { 'L' },    { 'M' },    { 'N' },
    { 'O' },   { 'P' },    { 'Q' },    { 'R' },
    { 'S' },   { 'T' },    { 'U' },    { 'V' },
    { 'W' },   { 'X' },    { 'Y' },    { 'Z' },
};

struct charInteger {
    char charIntegerZeroToNine;
};

const struct charInteger charIntegerTable[] = {
    { '0' },   { '1' },
    { '2' },   { '3' },
    { '4' },   { '5' },
    { '6' },   { '7' },
    { '8' },   { '9' },
};

struct operators {
    string charOperators;
};

const struct operators charOperatorsTable [] = {
    { "+" },   { "-" },
    { "*" },   { "/" },
    { "%" },
};

int Table::validateCharacter(char character) {
    for(int i = 0; i < 52; i++) {
        if(characterTable[i].character_aToZ == character)
            return i;
    }
     return -1;
}

int Table::validateInteger (char integer){
    for(int i = 0; i < 10; i++){
        if(charIntegerTable[i].charIntegerZeroToNine == integer)
            return i;
    }
    return -1;
}

int Table::validateOperators (string operators){
    for(int i = 0; i < 5; i++){
        if(charOperatorsTable[i].charOperators == operators)
            return i;
    }
    return -1;
}

int Table::validateID (string token) {
    // if token[0] is character
    if(validateCharacter(token[0]) != -1 ) {
        for(int i = 1; i < token.length(); i++) {
            // if token[i] is character
            if(validateCharacter(token[i]) != -1)
                continue;
            // if token[i] is an integer
            else if(validateInteger(token[i]) != -1)
                continue;
            // if token[i] is neither
            else {
                return -1;
            }
        }
        // if token is an ID
        return 1;
    }
    // if token is not an ID
    return -1;
}



