/*
 * Programmers: Ray Luu
 * Username: masc0720
 * CS530, Fall 2013
 * Instructor: Guy Leonard
 * Assignment 3
 * Due Date: December 9, 2013
 * Parser.cpp
 */

#include "Parser.h"

void Parser::readFile() {
    char *input = new char[MAX_INPUT]();
    char *inputFile = new char[MAX_INPUT]();
    fileName =  new char[MAX_INPUT]();
    string line;
    
    printf("Ray Luu - masc0720\n");
    printf("Expressions Parser\n");
    printf("Enter your text file name: \n");
    
    // Read file name.
    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        sscanf(input, "%s", fileName);
    }
    else {
        printf("Please input file name.\n");
    }

    strcat(inputFile, fileName);
    strcat(inputFile, ".txt");
    
    // Open text file and assign each line to vector textContent.
    ifstream textFile(inputFile);
    if (textFile.is_open()) {
        while (textFile.good()) {
            getline(textFile,line);
            textContent.push_back(line);
        }
        textFile.close();

        // After reading the file successfully. Run program:
        printf("Parsing %s ...\n\n", inputFile);
        
        printf("For more information...Please see out.txt file\n\n");
        
        Parser::run();
        
    } else printf("Unable to open text file.\n");
}

void Parser::run() {
    
    FILE *outFile;
    outFile = fopen("out.txt", "wb");
    
    fprintf(outFile,"Text Content: \n");

    for(it = textContent.begin(); it != textContent.end(); ++it) {
        fprintf(outFile,"%s",it->c_str());
        
        fprintf(outFile,"\n");
    }
    fprintf(outFile,"\n");
    
    fprintf(outFile,"Number of Line is: %lu \n",textContent.size());
    fprintf(outFile,"\n");

    for(int i = 0; i < textContent.size(); i++) {
        // If first character is not space then process
        if(textContent[i][0] != ' ') {
            // Tokenize to string token
            vector<string> token;
            istringstream f(textContent[i]);
            string s;
            while (getline(f, s, ' ')) {
                token.push_back(s);
            }
            
            // Print out each line of token
            for (int j = 0; j < token.size(); j++) {
                fprintf(outFile,"%s ",token[j].c_str());
            }
            fprintf(outFile,"\n");
            // if the line of token is an Expression
            if (validateExp(token, outFile)) {
                // if the line of token is NOT an Assignment
                if (!validateAssg(token,outFile)) {
                    fprintf(outFile,"Line %d is an Expression\n",i+1);
                    fprintf(outFile,"\n");
                }
            }
            // if the line of token is an Assignment
            else if (validateAssg(token,outFile)) {
                // if the line of token is not an expression
                if (!validateExp(token, outFile)) {
                    fprintf(outFile,"Line %d is an Assignment\n",i+1);
                    fprintf(outFile,"\n");
                }
            }
            // the line of token is neither Expression or Assignment
            else {
                fprintf(outFile,"Line %d is either an Expression nor Assignment\n",i+1);
                fprintf(outFile,"\n");
            }
        }
    }
    fclose(outFile);
    EXIT_SUCCESS;
}

bool Parser::validateExp(vector<string> token, FILE *outFile){
    Table *table = new Table();
    int openParen = 0;
    int closeParen = 0;
    
    // if the last token is not an ';'
    if(token[1] != "=" && token[token.size() - 1] != ";") {
        // if the first token of the line of token is an ID
        if(table->validateID(token[0]) == 1) {
            // if the second token is not an operator
            if(table->validateOperators(token[1]) == -1) {
                if(token[1] != "=") {
                    fprintf(outFile,"Invalid statement! The second element is not an operator. The element is '%s'\n",token[1].c_str());
                    return false;
                }
                return false;
            }
            // if the third token is not an ID
            if(table->validateID(token[2]) == -1){
                // if the thirth token is not an '(ID'
                if (!validateParenNoSpace(token[2],outFile)[0]) {
                    if (token[2] != "(") {
                        fprintf(outFile,"Invalid statement! The element is not an 'ID'. The element is '%s'\n",token[2].c_str());
                        return false;
                    }
                }
            }
             // if the last token is an ID
            if (table->validateID(token[token.size()-1]) == 1) {
                // validate pararenthesis and everything in between
                if(validateAllParent(token,outFile)[0]) {
                    openParen = openParen + validateAllParent(token,outFile)[1];
                    closeParen= closeParen + validateAllParent(token,outFile)[2];
                    if (openParen != closeParen) {
                        fprintf(outFile,"Invalid statement! Number of Parenthesises does not matched!\n");
                        fprintf(outFile,"Open Parentheises: %d\nClose Parentheises: %d\n",openParen,closeParen);
                        return false;
                    }
                    return true;
                }
            }
            // if the last token is NOT an 'ID'
            else if(table->validateID(token[token.size()-1]) == -1) {
                // if the last token is ')'
                if(token[token.size() - 1] == ")") {
                    if (validateAllParent(token,outFile)[0]){
                        closeParen++;
                        openParen = openParen + validateAllParent(token,outFile)[1];
                        closeParen= closeParen + validateAllParent(token,outFile)[2];
                        // if open parenthesis != to close Parenthesis
                        if (openParen != closeParen) {
                            fprintf(outFile,"Invalid statement! Number of Parenthesises does not matched!\n");
                            fprintf(outFile,"Open Parentheises: %d\nClose Parentheises: %d\n",openParen,closeParen);
                            return false;
                        }
                    }
                    else {
                        fprintf(outFile,"Invalid statement!\n");
                        return false;
                    }
                    return true;
                }
                // if the last token is 'ID)'
                else if (validateParenNoSpace(token[token.size()-1],outFile)[0]) {
                    openParen = openParen + validateAllParent(token,outFile)[1] + validateParenNoSpace(token[0],outFile)[1] ;
                    closeParen= closeParen + validateAllParent(token,outFile)[2] + validateParenNoSpace(token[token.size()-1],outFile)[2];
                    if (openParen != closeParen) {
                        fprintf(outFile,"Invalid statement! Number of Parenthesises does not matched!\n");
                        fprintf(outFile,"Open Parentheises: %d\nClose Parentheises: %d\n",openParen,closeParen);
                       return false;
                    }
                    return true;
                }
            }
        }
        // if the first token is not an ID
        else if (table->validateID(token[0]) == -1) {
             // if the first token is '(' OR '(ID'
            if (token[0] == "(" || validateParenNoSpace(token[0],outFile)[0]) {
                if(token[0] == "(") {
                    // if the thirst token is not an operator
                    if(table->validateOperators(token[2]) == -1) {
                        fprintf(outFile,"Invalid statement! The third element is not an operator. The element is '%s'\n",token[2].c_str());
                        return false;
                    }
                    // if the fourth token is not an ID
                    if(table->validateID(token[3]) == -1){
                        // if the fourth token is not an '(ID"
                        if (!validateParenNoSpace(token[3],outFile)[0]) {
                            if (token[3] != "(") {
                                fprintf(outFile,"Invalid statement! The fourth element is not an ID. The element is '%s'\n",token[3].c_str());
                                return false;
                            }
                        }
                    }
                }
                // if the token[0] is '(ID'
                else if (validateParenNoSpace(token[0],outFile)[0]) {
                    // if the second token is not an operator
                    if(table->validateOperators(token[1]) == -1) {
                        fprintf(outFile,"Invalid statement! The second element is not an operator. The element is '%s'\n",token[1].c_str());
                        return false;
                    }
                    // if the third token is not an ID
                    if(table->validateID(token[2]) == -1){
                        // if the thirth token is not an '(ID'
                        if (!validateParenNoSpace(token[2],outFile)[0]) {
                            if (token[2] != "(") {
                                fprintf(outFile,"Invalid statement! The third element is not an ID. The element is '%s'\n",token[2].c_str());
                                return false;
                            }
                        }
                    }
                }
                
                // validate all Parenthesis
                if (validateAllParent(token,outFile)[0]){
                    openParen++;
                    openParen = openParen + validateAllParent(token,outFile)[1];
                    closeParen= closeParen + validateAllParent(token,outFile)[2];
                    // if the last token is ')'
                    if (token[token.size() - 1] == ")" )
                        closeParen++;
                    else if (validateParenNoSpace(token[token.size()-1],outFile)[0])
                        closeParen++;
                    // if open parenthesis != to close Parenthesis
                    if (openParen != closeParen) {
                        fprintf(outFile,"Invalid statement! Number of Parenthesises does not matched!\n");
                        fprintf(outFile,"Open Parentheises: %d\nClose Parentheises: %d\n",openParen,closeParen);
                        return false;
                    }
                    return true;
                }
            }
        }
        // if the first token is NOT an ID
        if(table->validateID(token[0]) == -1) {
            if(token[0] != "(") {
                // the first token is not '(ID'
                if(!validateParenNoSpace(token[0],outFile)[0]) {
                    fprintf(outFile,"Invalid statement! The token '%s' is not an ID\n",token[0].c_str());
                    return false;
                }
            }
        }
    }
    return false;
}

// validate everything in between the line of token
vector<int> Parser::validateAllParent(vector<string> token, FILE *outFile) {
    Table *table = new Table();
    vector<int> value(3);
    
    value.clear();

    int openParen = 0;
    int closeParen = 0;
    
    // Starting from second token to the second to the last token
    for (int i = 2; i < token.size()-1; i++) {
        // if token[i] is an ID AND token[i+1] is an NOT OPERATOR
        if ((table->validateID(token[i]) == 1) && (table->validateOperators(token[i+1]) == -1)) {
            // if token[i+1] IS NOT ")"
            if(token[i+1] != ")") {
                 fprintf(outFile,"Invalid statement! The token is '%s' AND the following token is '%s'\n",token[i].c_str(),token[i+1].c_str());
                
                value.push_back(false);
                value.push_back(openParen);
                value.push_back(closeParen);
                return value;
            }
        }
        // if token[i] is an OPERATOR AND token[i+1] is an NOT an ID
        else if ((table->validateOperators(token[i]) != -1) && (table->validateID(token[i+1]) == -1)) {
            // if token[i+1] is NOT'(ID'
            if(!validateParenNoSpace(token[i+1],outFile)[0]){
                // if token[i+1] is NOT "("
                if(token[i+1] != "(") {
                    fprintf(outFile,"Invalid statement! The token is '%s' AND the following token is '%s'\n",token[i].c_str(),token[i+1].c_str());
                    
                    value.push_back(false);
                    value.push_back(openParen);
                    value.push_back(closeParen);
                    return value;
                }
            }
        }
        
        // if token[i] is '('
        else if(token[i] == "("){
            openParen++;
            // if token[i+1] is '('
            if(token[i+1][0] == '(')
                continue;
            // if token[i+1] is an ID
            else if(table->validateID(token[i+1]) == 1)
                continue;
            else {
                fprintf(outFile,"Invalid statement! The token is '%s' AND the following token is '%s'\n",token[i].c_str(),token[i+1].c_str());
                
                value.push_back(false);
                value.push_back(openParen);
                value.push_back(closeParen);
                return value;
            }
        }
        // if token[i] is ')'
        else if(token[i] == ")"){
            closeParen++;
            // if token[i+1] is ')'
            if(token[i+1] == ")")
                continue;
            // if token[i+1] is an OPERATOR
            else if(table->validateOperators(token[i+1]) != -1)
                continue;
            else {
                fprintf(outFile,"Invalid statement! The token is '%s' AND the following token is '%s'\n",token[i].c_str(),token[i+1].c_str());
                
                value.push_back(false);
                value.push_back(openParen);
                value.push_back(closeParen);
                return value;
            }
        }
        // token[i] is '(ID'
        else if (validateParenNoSpace(token[i],outFile)[0]) {
            // if token[+1] is not an operator
            if(table->validateOperators(token[i+1]) == -1){
                fprintf(outFile,"Invalid statement! The token is '%s' AND the following token is '%s'\n",token[i].c_str(),token[i+1].c_str());
                
                value.push_back(false);
                value.push_back(openParen);
                value.push_back(closeParen);
                return value;
            }
            openParen = openParen + validateParenNoSpace(token[i],outFile)[1];
            closeParen = closeParen + validateParenNoSpace(token[i],outFile)[2];
        }
    }
    value.push_back(true);
    value.push_back(openParen);
    value.push_back(closeParen);
    return value;
}

bool Parser::validateAssg(vector<string> token, FILE *outFile){
    Table *table = new Table();
    if (table->validateID(token[0]) == 1) {
        //if (token[1] == "=" && token[token.size() - 1] == ";") {
        if (token[1] == "=") {
            if (token[token.size() - 1] == ";") {
                vector<string> theRest;
                for (int i = 2; i < token.size()-1; i++) {
                    theRest.push_back(token[i]);
                }
                if (validateExp(theRest,outFile)) {
                    return true;
                }
            }
            else if (token[token.size() - 1] != ";") {
                fprintf(outFile,"Invalid statement! Missing a ';' at the end\n");
                return false;
            }
        }
    }
    return false;
}

vector<int> Parser::validateParenNoSpace(string eachToken, FILE *outFile) {
    Table *table = new Table();

    vector<int> value(3);
    value.clear();
    
    int openParen = 0;
    int closeParen = 0;
    
    //if the token is NOT an ID && the token[0] is a CHARACTER
    if(table->validateID(eachToken) == -1 && (table->validateCharacter(eachToken[0]) != -1)) {
        // if the last token is ')'
        if(eachToken[eachToken.length() -1] == ')'){
            closeParen++;
            // for token to size - 2
            for(int i = 1; i < eachToken.length()-1;i++) {
                // if token[i] is NOT a CHARACTER
                if(table->validateCharacter(eachToken[i]) == -1) {
                    // if token[i] is NOT an INTEGER
                    if(table->validateInteger(eachToken[i]) == -1) {
                        // if the token is ')' AND token[i+1] is NOT ')'
                        if(eachToken[i] == ')' && eachToken[i+1] != ')') {
                            value.push_back(false);
                            value.push_back(openParen);
                            value.push_back(closeParen);
                            
                            fprintf(outFile,"Invalid statement! The token is '%hhd' AND the following token is '%hhd'\n",eachToken[i],eachToken[i+1]);
                            
                            return value;
                        }
                        // if token[i] is NOT ')'
                        else if (eachToken[i] != ')') {
                            value.push_back(false);
                            value.push_back(openParen);
                            value.push_back(closeParen);
                            
                            fprintf(outFile,"Invalid statement! The token is '%hhd' AND the following token is '%hhd'\n",eachToken[i],eachToken[i+1]);
                            
                            return value;
                        }
                         closeParen++;
                    }
                }
            }
            value.push_back(true);
            value.push_back(openParen);
            value.push_back(closeParen);
            return value;
        }
    }
    // if the token is not an ID
    else if(table->validateID(eachToken) == -1) {
        // for each char of the token
        for(int i = 0; i < eachToken.length(); i++) {
            // if the token[i] is NOT '('
            if(eachToken[i] != '(') {
                // if the token[i] is not a CHARACTER
                if(table->validateCharacter(eachToken[i]) == -1) {
                    value.push_back(false);
                    value.push_back(openParen);
                    value.push_back(closeParen);
                    return value;
                }
                string elementAfterParentheise = eachToken.substr(i,eachToken.length()-i);
                
                // if the string after the parenthesis is an ID
                if(table->validateID(elementAfterParentheise) == 1) {
                    value.push_back(true);
                    value.push_back(openParen);
                    value.push_back(closeParen);
                    return value;
                }
                value.push_back(false);
                value.push_back(openParen);
                value.push_back(closeParen);
                return value;
            }
            openParen++;
        }
    }
    return value;
}

