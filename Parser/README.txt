/*
 * Programmers: Ray Luu
 * Username: masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Due Date: December 9, 2013
 * README.txt
 */

Files in this assignment: Parser.cpp, Parser.h, Table.cpp, Table.h,
main.cpp, Makefile, README.txt and all will be in “a3” directory on Rohan masc0720’s account

Compile Instruction: 
-  Type "make" on the command line. It will automatically compile the source code file using g++ 
compiler and create a “bnf” executable file (which is an "a.out" file). By typing “bnf” on the console, 
it will run the program. After typing “bnf” to run the program, the program will display a message 
to prompt the user for input. Put your desired text file in the same directory, type the name of your text
file and the program will start parsing the text file. The program will also create out.txt file
to write out all of the outputs and place it in the same directory.

In the program
- In the program, main will call Parser.cpp, and Parser.cpp will do most of work. 
Therefore, it will call Table.cpp to help with the parsing. 

Table.cpp will include the following four methods: 
    static int validateCharacter (char character);
    static int validateInteger (char integer);
    static int validateOperators (string operators);
    static int validateID (string token);

Parser.cpp will include the following methods:
    void readFile();
    void run();
    bool validateExp(vector<string> token, FILE *outFile);
    bool validateAssg(vector<string> token, FILE *outFile);
    vector<int>validateParenNoSpace(string eachToken, FILE *outFile);
    vector<int> validateAllParent(vector<string>token,FILE *outFile);
    char *fileName;
    vector<string> textContent;
    vector<string>::iterator it;

- The grammar
A digit is one of:
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 

A char is one of:
	a, b, c, d, e, f, g, h, i, j, k, l m, n, o, p, q, r, s, t, u, v, w, x, y, z, 
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z 

An operator is one of: 
	+, -, *, /, % 

In the program, it will recognize the following as valid statements: 
	assignment 
	expression

An Assignment shall have the form: 
	id = exp ; 

An expression shall have the form: 
	id op id {op id}

An id shall be made up of any combination of digits and char. The first position of the identifier 
must contain a char 

- Program inputs and program outputs 

If the program encounters an invalid statement, it will try its best to identify what the error is and
print out the error message in the the out.txt file and terminate that line, and continue onto the next line
if the following valid input is:
	first = one1 + two2 - three3 / four4 ;

the program will write to the out.txt 
	first = one1 + two2 - three3 / four4 ;
	Line 1 is an Assignment

if the following invalid input is: 
	first = one1 + two2 - three3 / four4

the program will write to the out.txt
	Invalid statement! Missing a ';' at the end
- In this project, I have learned how to program the right way. I first start with writing 
the algorithm down, then I write down the pseudocode for each method in the algorithm. The difficult part is to come up with the algorithm and break the problem into sub-problems, 
and analyze the methods needed each individually. The only thing with programming part is finding the bugs about what is the error it supposed to print out. In addition, another hard part about this program is get it to work on Rohan. I have spent more than 8 hours trying to get my completed program work on Rohan.
