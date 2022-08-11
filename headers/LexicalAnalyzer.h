//
// Created by Iulia on 28/03/2022.
//

#ifndef LA_LEXICALANALYZER_H
#define LA_LEXICALANALYZER_H

#include<iostream>
#include<string>

#include "Token.h"

class LexicalAnalyzer {
public:
    enum {  END = -1, ID = 2, CT_CHAR = 5, CT_STRING = 8,CT_INT = 10,
            CT_REAL = 22, RPAR = 23, LPAR = 24,  LBRACKET = 25, RBRACKET = 26,
            LACC = 27, RACC = 28, COMMA = 29, SEMICOLON = 30, DOT = 31,  SUB = 32,
            ADD = 33, MUL = 34, DIV = 37, NOT = 42, NOTEQ = 43, EQUAL = 44,
            LESS = 45, LESSEQ = 46, ASSIGN = 47, GREATER = 48, GREATEREQ = 50,
            OR = 52, AND = 54, BREAK = 60, CHAR = 61, DOUBLE = 62, ELSE = 63, FOR = 64,
            INT = 65, IF = 66, RETURN = 67, STRUCT = 68, VOID = 69, WHILE = 70}; // tokens codes



    Tk_list tk_list;
    char *text;
    int line =0;
    int getNextToken();
    void get_all_tokens();
    char *extract(char  *start, const char *end);

    explicit LexicalAnalyzer(char* text);
};

#endif //LA_LEXICALANALYZER_H
