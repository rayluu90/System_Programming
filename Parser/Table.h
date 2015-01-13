/*
 * Programmers: Ray Luu
 * Username: masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Due Date: December 9, 2013
 * Table.h
 */

#ifndef Assignment_3_Table_h
#define Assignment_3_Table_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Table {
public:
    static int validateCharacter (char character);
    static int validateInteger (char integer);
    static int validateOperators (string operators);
    static int validateID (string token);
};

#endif
