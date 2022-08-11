//
// Created by Iulia on 26/03/2022.
//

#ifndef LEXICAL_ANALIZER_TOKEN_H
#define LEXICAL_ANALIZER_TOKEN_H

#include <iostream>
#include <memory>
#include<variant>

class Token {
public:
    int code;
    std::variant<char *, long int, double> text;
    int line;
    std::shared_ptr<Token> next;

    Token(const int& code, char *text, const int& line);
    Token(const int& code, const long int& text, const int& line);
    Token(const int& code, const double& text, const int& line);
    Token(const int& code,const int& line);
    Token(const Token& token);

    void print_tk();
};

class Tk_list{
public:
    std::shared_ptr<Token> head, last;
    void push(Token& token);
};



#endif //LEXICAL_ANALIZER_TOKEN_H
