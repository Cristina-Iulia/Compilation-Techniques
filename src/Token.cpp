//
// Created by Iulia on 26/03/2022.
//

#include "../headers/Token.h"

void Tk_list::push(Token& token){
    auto tmp{std::make_shared<Token>(std::move(token))};
//    std::cout<<"Code: "<<tmp->code<<" line: "<<tmp->line<<"\n";
    if(last){
        last->next = tmp;
    }else if(!last){
        head = tmp;
    }
    last = std::move(tmp);
}

//void Tk_list::print_tk_list() {
////    auto tmp = head;
////    while(tmp){
////        std::cout<<"Code: "<<tmp->code<<" line: "<<tmp->line<<"\n";
////        tmp = tmp->next;
////    }
//    auto copy = head;
//    while(copy) {
//        int line = copy->line;
//        int code = copy->code;
//        std::cout<<" Code: ";
//        copy->print_tk();
//        std::cout<<" line: "<<line;
//        try {
//            char *text = std::get<char *> (copy->text);
//            std::cout<<" Text: "<<text<<"\n";
//        }
//        catch(...) {
//            try {
//                long int integer = std::get<long int> (copy->text);
//                std::cout<<" Text: "<<integer<<"\n";
//            }
//            catch(...) {
//                try {
//                    double dbl = std::get<double> (copy->text);
//                    std::cout<<" Text: "<<dbl<<"\n";
//                }
//                catch(...) {
//                    std::cout<< "Error while printing the list of tokens!\n";
//                }
//            }
//        }
//        copy = copy->next;
//    }
//}

Token::Token(const int &code, char *text, const int &line)
:code(code),
text(text),
line(line)
{
}

Token::Token(const int &code, const long &text, const int &line)
:code(code),
 text(text),
 line(line)
{

}

Token::Token(const int &code, const double &text, const int &line)
:code(code),
 text(text),
 line(line)
{

}

Token::Token(const int &code, const int &line)
:code(code),
 line(line)
{
}

Token::Token(const Token &token) {
    code = token.code;
    text = token.text;
    line = token.line;
}

void Token::print_tk() {

    switch (code) {
        case -1: std::cout<<"END ";
            break;
        case 2: std::cout<<"ID ";
            break;
        case 5: std::cout<<"CT_CHAR ";
            break;
        case 8: std::cout<<"CT_STRING ";
            break;
        case 10: std::cout<<"CT_INT ";
            break;
        case 22: std::cout<<"CT_REAL ";
            break;
        case 23: std::cout<<") ";
            break;
        case 24: std::cout<<"( ";
            break;
        case 25: std::cout<<"[ ";
            break;
        case 26: std::cout<<"] ";
            break;
        case 27: std::cout<<"{ ";
            break;
        case 28: std::cout<<"} ";
            break;
        case 29: std::cout<<", ";
            break;
        case 30: std::cout<<"; ";
            break;
        case 31: std::cout<<". ";
            break;
        case 32: std::cout<<"- ";
            break;
        case 33: std::cout<<"+ ";
            break;
        case 34: std::cout<<"* ";
            break;
        case 37: std::cout<<"/ ";
            break;
        case 42: std::cout<<"! ";
            break;
        case 43: std::cout<<"!= ";
            break;
        case 44: std::cout<<"== ";
            break;
        case 45: std::cout<<"< ";
            break;
        case 46: std::cout<<"<= ";
            break;
        case 47: std::cout<<"= ";
            break;
        case 48: std::cout<<"> ";
            break;
        case 50: std::cout<<">= ";
            break;
        case 52: std::cout<<"OR ";
            break;
        case 54: std::cout<<"AND ";
            break;
        case 60: std::cout<<"BREAK ";
            break;
        case 61: std::cout<<"CHAR ";
            break;
        case 62: std::cout<<"DOUBLE ";
            break;
        case 63: std::cout<<"ELSE ";
            break;
        case 64: std::cout<<"FOR ";
            break;
        case 65: std::cout<<"INT ";
            break;
        case 66: std::cout<<"IF ";
            break;
        case 67: std::cout<<"RETURN ";
            break;
        case 68: std::cout<<"STRUCT ";
            break;
        case 69: std::cout<<"VOID ";
            break;
        case 70: std::cout<<"WHILE ";
            break;
        default: std::cout<<code;
    }

}
