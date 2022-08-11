//
// Created by Iulia on 28/03/2022.
//

#include "../headers/LexicalAnalyzer.h"
#include<string.h>



int LexicalAnalyzer::getNextToken(){
    int state=0;
    char ch;
    char *pStartCh;

    while(1) {
        ch=*text;
        switch (state) {
            case 0:
                if (ch == ' ' || ch == '\r' || ch == '\t') {
                    text++; // consume the character and remains in state 0
                } else if (ch == '\n') { // handled separately in order to update the current line
                    line++;
                    text++;
                    state = 0;
                } else if (ch == EOF || ch == '\0') { // the end of the input string
                    Token tk{-1, line};
                    tk_list.push(tk);
                    return END;
                } else if (ch == ')') {
                    Token tk{23,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return RPAR;
                } else if (ch == '(') {
                    Token tk{24,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return LPAR;
                } else if (ch == '[') {
                    Token tk{25,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return LBRACKET;
                } else if (ch == ']') {
                    Token tk{26,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return RBRACKET;
                } else if (ch == '{') {
                    Token tk{27,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return LACC;
                } else if (ch == '}') {
                    Token tk{28,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return RACC;
                } else if (ch == ',') {
                    Token tk{29,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return COMMA;
                } else if (ch == ';') {
                    Token tk{30,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new stat
                    return SEMICOLON;
                } else if (ch == '.') {
                    Token tk{31,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return DOT;
                } else if (ch == '-') {
                    Token tk{32,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return SUB;
                } else if (ch == '+') {
                    Token tk{33,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return ADD;
                } else if (ch == '*') {
                    Token tk{34,"\0", line};
                    tk_list.push(tk);
                    text++; // consume the character
                    state = 0; // set the new state
                    return MUL;
                }else if (ch == '!') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '=') {
                        text++;
                        Token tk{43,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return NOTEQ;
                    } else {
                        Token tk{42,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return NOT;
                    }
                } else if (ch == '<') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '=') {
                        text++;
                        Token tk{46,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return LESSEQ;
                    } else {
                        Token tk{45,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return LESS;
                    }
                } else if (ch == '>') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '=') {
                        text++;
                        Token tk{50,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return GREATEREQ;
                    } else {
                        Token tk{48,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return GREATER;
                    }
                } else if (ch == '|') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '|') {
                        text++;
                        Token tk{52,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return OR;
                    } else {
                        state = 0;
                        return 0;
                    }
                } else if (ch == '&') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '&') {
                        text++;
                        Token tk{54,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return AND;
                    } else {
                        state = 0;
                        return 0;
                    }
                }else if (ch == '=') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '=') {
                        text++;
                        Token tk{44,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return EQUAL;
                    } else {
                        Token tk{47,"\0", line};
                        tk_list.push(tk);
                        state = 0;
                        return ASSIGN;
                    }
                }else if (isalpha(ch) || ch == '_') {
                    pStartCh = text; // memorizes the beginning of the ID
                    text++; // consume the character
                    state = 1; // set the new state
                } else if (ch == '\'') {
                    pStartCh = text;
                    text++; // consume the character
                    state = 3; // set the new state
                } else if (ch == '"') {
                    pStartCh = text;
                    text++; // consume the character
                    state = 6; // set the new state
                } else if (ch == '0') {
                    pStartCh = text;
                    text++; // consume the character
                    state = 131; // set the new state
                } else if (ch >= '1' && ch <= '9') {
                    pStartCh = text;
                    text++; // consume the character
                    state = 132; // set the new state
                } else if (ch == '/'){
                    pStartCh = text;
                    text++; // consume the character
                    state = 35; // set the new state
                }
                break;
            case 1:
                if (isalpha(ch) || ch == '_') {
                    text++;
                } else {
                    char *str = extract(pStartCh,text);
                    if(strcasecmp(str,"BREAK") == 0){
                        Token tk{60,"BREAK", line};
                        tk_list.push(tk);
                        state = 0;
                        free(str);
                        return BREAK;
                    }
                    else if(strcasecmp(str,"CHAR") == 0){
                        Token tk{61,"CHAR", line};
                        tk_list.push(tk);
                        state = 0;
                        return CHAR;
                    }
                    else if(strcasecmp(str,"DOUBLE") == 0){
                        Token tk{62,"DOUBLE", line};
                        tk_list.push(tk);
                        state = 0;
                        return DOUBLE;
                    }
                    else if(strcasecmp(str,"ELSE") == 0){
                        Token tk{63,"ELSE", line};
                        tk_list.push(tk);
                        state = 0;
                        return ELSE;
                    }
                    else if(strcasecmp(str,"FOR") == 0){
                        Token tk{64,"FOR", line};
                        tk_list.push(tk);
                        state = 0;
                        return FOR;
                    }
                    else if(strcasecmp(str,"INT") == 0){
                        Token tk{65,"INT", line};
                        tk_list.push(tk);
                        state = 0;
                        return INT;
                    }
                    else if(strcasecmp(str,"IF") == 0){
                        Token tk{66,"IF", line};
                        tk_list.push(tk);
                        state = 0;
                        return IF;
                    }
                    else if(strcasecmp(str,"RETURN") == 0){
                        Token tk{67,"RETURN", line};
                        tk_list.push(tk);
                        state = 0;
                        return RETURN;
                    }
                    else if(strcasecmp(str,"STRUCT") == 0){
                        Token tk{68,"STRUCT", line};
                        tk_list.push(tk);
                        state = 0;
                        return STRUCT;
                    }
                    else if(strcasecmp(str,"VOID") == 0){
                        Token tk{69,"VOID", line};
                        tk_list.push(tk);
                        state = 0;
                        return VOID;
                    }
                    else if(strcasecmp(str,"WHILE") == 0){
                        Token tk{70,"WHILE", line};
                        tk_list.push(tk);
                        state = 0;
                        return WHILE;
                    }
                    else {
                        Token tk{2,str, line};
                        tk_list.push(tk);
                        state = 0;
                        return ID;
                    }
                }
                break;
            case 3:
                if (ch != '\'') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '\'') {
                        text++;
                        char *str = extract(pStartCh,text);
                        Token tk{5,str, line};
                        tk_list.push(tk);
                        state = 0;
                        free(str);
                        return CT_CHAR;
                    } else {
                        state = 0;
                        return 0;
                    }
                } else {
                    state = 0;
                    return 0;
                }break;
            case 6:
                if (ch != '"') {
                    text++; // consume the character
                    ch = *text;
                    if (ch == '"') {
                        text++;
                        char *str = extract(pStartCh,text);
                        Token tk{8,str, line};
                        tk_list.push(tk);
                        state = 0;
                        free(str);
                        return CT_STRING;
                    } else {
                        state = 6;
                    }
                } else {
                    state = 0;
                    return 0;
                }break;
            case 35:
                if(ch == '/'){
                    pStartCh = text;
                    text++; // consume the character
                    state = 36; // set the new state

                }else if (ch != '*') {
                    Token tk{37,"\0", line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    return DIV;
                } else {
                    pStartCh = text;
                    text++; // consume the character
                    state = 39; // set the new state

                }
                break;

            case 36:
                if(ch != '\n' && ch != '\r' && ch != '\0'){
                    text++;
                }
                else{
                    text++;
                    state = 0;
                }
                break;

            case 39:
                if(ch != '*'){
                    text++;
                }
                else{
                    text++;
                    ch = *text;
                    if( ch != '/'){
                        text++;
                    } else{
                        text++;
                        state = 0;
                    }
                }break;
            case 131:
                if((ch == '8') || (ch == '9') ){
                    text++;
                    state = 137;
                } else if(ch == '.'){
                    text++;
                    state = 138;
                }else if((ch == 'x') || (ch == 'X')){
                    text++;
                    state = 134;
                }else if((ch >= '0') && (ch <= '7')){
                    text++;
                    state = 133;
                }else{
                    char *str = extract(pStartCh,text);
                    Token tk{10,atol(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_INT;
                }break;
            case 132:
                if(ch == '.'){
                    text++;
                    state = 138;
                }else if((ch == 'e') || (ch == 'E')){
                    text++;
                    state = 140;
                }else if((ch >= '0') && (ch <= '9')){
                    text++;
                }else{
                    char *str = extract(pStartCh,text);
                    Token tk{10,atol(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_INT;
                }break;
            case 133:
                if(ch == '.'){
                    text++;
                    state = 138;
                }else if((ch >= '0') && (ch <= '7')){
                    text++;
                }else if((ch == 'e') || (ch == 'E')){
                    text++;
                    state = 140;
                }else{
                    char *str = extract(pStartCh,text);
                    Token tk{10,atol(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_INT;
                }break;
            case 134:
                if(isalpha(ch)){
                    text++;
                    state = 135;
                }break;
            case 135:
                if(isalpha(ch)){
                    text++;
                }else{
                    char *str = extract(pStartCh,text);
                    Token tk{10,atol(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_INT;
                }break;
            case 137:
                if(ch == '.'){
                    text++;
                    state = 138;
                }else if((ch >= '0') && (ch <= '9')){
                    text++;
                }else if((ch == 'e') || (ch == 'E')){
                    text++;
                    state = 140;
                }break;
            case 138:
                if((ch >= '0') && (ch <= '9')){
                    text++;
                    state = 139;
                }break;
            case 139:
                if((ch >= '0') && (ch <= '9')){
                    text++;
                }else if((ch == 'e') || (ch == 'E')){
                    text++;
                    state = 140;
                }else{
                    char *str = extract(pStartCh,text);
                    Token tk{22,atof(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_REAL;
                }break;
            case 140:
                if((ch >= '0') && (ch <= '9')){
                    text++;
                    state = 141;
                }else if((ch == '+') || (ch == '-')){
                    text++;
                    state = 142;
                }break;
            case 141:
                if((ch >= '0') && (ch <= '9')){
                    text++;
                }else{
                    char *str = extract(pStartCh,text);
                    Token tk{22,atof(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_REAL;
                }break;
            case 142:
                if((ch >= '0') && (ch <= '9')){
                    text++;
                    state = 143;
                }break;
            case 143:
                if((ch >= '0') && (ch <= '9')){
                    text++;
                } else{
                    char *str = extract(pStartCh,text);
                    Token tk{22,atof(str), line};
                    tk_list.push(tk); // consume the character
                    state = 0;
                    free(str);
                    return CT_REAL;
                }break;

            default:
                std::cout<<"BOOM!!";
                exit(1);
        }

    }
    free(pStartCh);
}

LexicalAnalyzer::LexicalAnalyzer(char* text)
: text(text)
{}

void LexicalAnalyzer::get_all_tokens() {
    int i = getNextToken();
//    std::cout<<" "<<i<<" ";
    while(i != EOF){
        i = getNextToken();
//        std::cout<<" "<<i<<" ";
//        std::cout<<std::endl;
    }

}

char *LexicalAnalyzer::extract(char *start, const char *end) {
    char *itr = start;
    char *str =(char*) malloc(50);
    int i=0;
    while (itr != end){
        str[i] = *itr;
        i++;
        itr++;
    }
    str[i]='\0';
    return str;
}
