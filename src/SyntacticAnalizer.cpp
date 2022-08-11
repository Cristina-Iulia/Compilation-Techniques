//
// Created by Iulia on 03/04/2022.
//

#include "../headers/SyntacticAnalizer.h"

#include <utility>
#include <string.h>

SyntacticAnalizer::SyntacticAnalizer(LexicalAnalyzer lex)
    : LA(std::move(lex))
{
    currentTk = LA.tk_list.head;
    startTk = currentTk;
    ST = SymbolTable();
    add_predef_func();
}

bool SyntacticAnalizer::consume(int code) {


    if(currentTk->code == code){
        currentTk->print_tk();
        if(currentTk->code == LA.END) return true;
//        std::cout<<"NO END"<<std::endl;
        if(currentTk->next) {
//            std::cout<<"NEXT"<<std::endl;
            currentTk = currentTk->next;
            return true;
        }
        std::cout<<"NO NEXT"<<std::endl;

    }
    return false;
}


/*********
 * RULES *
 *********/
bool SyntacticAnalizer::rule_WHILE() {
    if(!consume(LA.WHILE)) { return false;}
    if(!consume(LA.LPAR)) {std::cout<<"Error: Missing LPAR in WHILE statement"<<std::endl; exit(1);}
    if(!expr()) {std::cout<<"Error: No EXPR in  WHILE statement"<<std::endl; exit(1);}
    if(ST.rv.type.typeBase == TB_STRUCT){
        std::cout<<"A structure cannot be logically tested";
        exit(18);
    }
    if(!consume(LA.RPAR)) {std::cout<<"Error: Missing RPAR in WHILE statement"<<std::endl; exit(1);}
    if(!stm()) {std::cout<<"Error: Bad WHILE statement"<<std::endl; exit(1);}

    return true;
}

bool SyntacticAnalizer::rule_IF() {
//    std::cout<<"in IF"<<std::endl;
    if(!consume(LA.IF)) { return false;}
    if(!consume(LA.LPAR)) {std::cout<<"Error: Missing LPAR in IF statement"<<std::endl; exit(1);}
    if(!expr()) {std::cout<<"Error: No EXPR in IF statement"<<std::endl; exit(1);}
    if(ST.rv.type.typeBase == TB_STRUCT){
        std::cout<<"A structure cannot be logically tested";
        exit(19);
    }
    if(!consume(LA.RPAR)) {std::cout<<"Error: Missing RPAR in IF statement"<<std::endl; exit(1);}
    if(!stm()) {std::cout<<"Error: Bad IF statement"<<std::endl; exit(1);}

    while(consume(LA.ELSE)) {
        if (!stm()) {
            std::cout<<"Error: Bad IF statement"<<std::endl; exit(1);
        }
    }


    return true;
}

bool SyntacticAnalizer::rule_BREAK() {

    if(!consume(LA.BREAK)) { return false;}
    if(!consume(LA.SEMICOLON)) {std::cout<<"Error: Bad BREAK statement"<<std::endl; exit(1);}
    return true;
}

bool SyntacticAnalizer::rule_FOR() {
    if(!consume(LA.FOR)) { return false;}
    if(!consume(LA.LPAR)) {std::cout<<"Error: Bad FOR statement"<<std::endl; exit(1);}
    expr();
    if(!consume(LA.SEMICOLON)) {std::cout<<"Error: Bad FOR statement"<<std::endl; exit(1);}
    expr();
    if(ST.rv.type.typeBase == TB_STRUCT){
        std::cout<<"A structure cannot be logically tested";
        exit(17);
    }
    if(!consume(LA.SEMICOLON)) {std::cout<<"Error: Bad FOR statement"<<std::endl; exit(1);}
    expr();
    if(!consume(LA.RPAR)) {std::cout<<"Error: Bad FOR statement"<<std::endl; exit(1);}
    if(!stm()) {std::cout<<"Error: Bad FOR statement"<<std::endl; exit(1);}
    return true;
}

bool SyntacticAnalizer::rule_EXPR() {
//    std::cout<<"EXPR RULE"<<std::endl;
    expr();
    if(!consume(LA.SEMICOLON)) {std::cout<<"Error: Missing SEMICOLON after expression"<<std::endl; return false;}
    return true;
}

bool SyntacticAnalizer::rule_RETURN() {
//    std::cout<<"RETURN"<<std::endl;
    if(!consume(LA.RETURN)) { return false;}
//    std::cout<<ST.crtFunc.type.typeBase;
    if(ST.crtFunc.type.typeBase==TB_VOID){
        std::cout<<"A void function cannot return a value";
        exit(16);
    }
    expr();
    ST.cast(&ST.crtFunc.type,&ST.rv.type);
    if(!consume(LA.SEMICOLON)) {std::cout<<"Error: Bad RETURN statement"<<std::endl; exit(1);}
    return true;
}

/**************
 * EXPRESIONS *
 **************/
bool SyntacticAnalizer::expr() {

    startTk = currentTk;
    if(exprAssign()){
        return true;
    }

    currentTk = startTk;
    return false;
}

bool SyntacticAnalizer::exprPrimary() {
    startTk = currentTk;
    if(consume(LA.CT_INT))
    {
        ST.set_retVal(ST.createType(TB_INT, -1),0,1, std::get<long int>(startTk->text));
        return true;
    }
    if (consume(LA.CT_REAL))
    {
        ST.set_retVal(ST.createType(TB_DOUBLE, -1),0,1, std::get<double>(startTk->text));
        return true;
    }
    if (consume(LA.CT_CHAR))
    {
        ST.set_retVal(ST.createType(TB_CHAR, -1),0,1, std::get<char *>(startTk->text));
        return true;
    }
    if (consume(LA.CT_STRING))
    {
        ST.set_retVal(ST.createType(TB_CHAR, 0),0,1, std::get<char *>(startTk->text));
        return true;
    }
    if (consume(LA.LPAR)) {
        if (expr())
            if (consume(LA.RPAR))
                return true;
    }

    else if(consume(LA.ID)){
        auto index= ST.findSymbol(std::get<char *>(startTk->text));
        if(index == -1){
            std::cout<<"Undefined symbol"<<std::endl;
            exit(6);
        }
        ST.set_retVal(ST.head[index].type,1,0);
        if(is_array_element()){ST.rv.type.nElements = -1; return true;}
        if(consume(LA.LPAR)){
            auto crtDefArg = ST.head[index].members.begin();
            if(ST.head[index].cls!=CLS_FUNC && ST.head[index].cls!=CLS_EXTFUNC) {
                std::cout<<"Call of the non-function "<<std::get<char *>(startTk->text);
                exit(6);
            }

            if(consume(LA.RPAR)) {
                if(crtDefArg != ST.head[index].members.end()) {
                    std::cout<<"Too few arguments in call"<<std::endl;
                        exit(6);
                }
                ST.set_retVal(ST.head[index].type,0,0);
                return true;
            }
            while(expr()){
                RetVal rve = ST.rv;
                if(crtDefArg == ST.head[index].members.end()) {
                    std::cout<<"Too many arguments in call"<<std::endl;
                    exit(6);
                }

                ST.cast(&crtDefArg->type,&rve.type);
                crtDefArg++;
                if(consume(LA.COMMA))continue;
                if(consume(LA.RPAR)) {
                    if(crtDefArg != ST.head[index].members.end()) {
                        std::cout<<"Too few arguments in call"<<std::endl;
                        exit(6);
                    }
                    ST.set_retVal(ST.head[index].type,0,0);
                    return true;
                }
            }
            currentTk = startTk;
            return false;

        } else{
            if(ST.head[index].cls == CLS_FUNC || ST.head[index].cls == CLS_EXTFUNC) {
                std::cout << "Missing call for function " << std::get<char *>(startTk->text) << std::endl;
                exit(6);
            }
            return true;
        }
    }
    else {
        return false;
    }

    return false;
}

bool SyntacticAnalizer::exprPostfix() {
    startTk = currentTk;
    RetVal rve = ST.rv;
    if(!consume(LA.LBRACKET)) {
        if (!consume(LA.DOT)) {
//            std::cout<<"EXPRESION POSTFIX";
            if (exprPrimary()) return true;
            else { return false; }
        }
//        std::cout<<"AM DAT DE PUNCT";
        auto temp=std::get<char *>(currentTk->text);
        if (!consume(LA.ID)) {currentTk = startTk; return false;}
        auto i=ST.findSymbol(ST.rv.type.TB_name);
        ST.head[i].print_sbl();
        auto index=ST.findSymbol(ST.head[i].members,temp);
        if(index == -1) {
            std::cout << "Struct " << ST.head[i].name << " does not have a member " << temp;
            exit(8);
        }

        ST.set_retVal(ST.head[i].type,1,0);
    }

    int cnt = 0;
    while (expr()){
        if(ST.rv.type.nElements<0) {
            std::cout<<"Only an array can be indexed"<<std::endl;
            exit(7);
        }
        Type typeInt = ST.createType(TB_INT,-1);
        ST.cast(&typeInt,&rve.type);
        ST.set_retVal(rve.type,1,0);
        ST.rv.type.nElements=-1;
        cnt++;
        rve = ST.rv;
    }
    if(cnt == 0) {currentTk = startTk; return false;}
    if(!consume(LA.RBRACKET)) {currentTk = startTk; return false;}

    exprPostfix();
    return true;
}

void SyntacticAnalizer::unary_check(int code){
    if(code == LA.SUB){
        if(ST.rv.type.nElements>=0) {
            std::cout << "Unary '-' cannot be applied to an array" << std::endl;
            exit(9);
        }
        if(ST.rv.type.typeBase==TB_STRUCT){
            std::cout << "Unary '-' cannot be applied on struct" << std::endl;
            exit(9);
        }
    }
    else{
        if(ST.rv.type.typeBase==TB_STRUCT){
            std::cout <<"'!' cannot be applied to a struct"<< std::endl;
            exit(9);
        }
        ST.rv.type=ST.createType(TB_INT,-1);
    }
    ST.rv.isLVal=0;
    ST.rv.isCtVal=0;
}
bool SyntacticAnalizer::exprUnary() {

    int code = currentTk->code;
//    std::cout<<"BJHWJH : "<<ST.rv.type.typeBase;
    if(!consume(LA.SUB) && !consume(LA.NOT)){
        if(exprPostfix()) return true;
        else { return false;}
    }

    unary_check(code);
    exprUnary();

    return true;
}

bool SyntacticAnalizer::exprCast() {
    startTk = currentTk;

    if(!consume(LA.LPAR)) {
        if (exprUnary()) { return true; }
        else { return false; }
    }
    Type t;
    if(!typeName(&t)) {currentTk = startTk; return false;}
    if(!consume(LA.RPAR)) {currentTk = startTk; return false;}

    RetVal rve = ST.rv;
    exprCast();

    ST.cast(&t,&rve.type);
    ST.rv.type=t;
    ST.rv.isCtVal=0;
    ST.rv.isLVal=0;

    return true;
}
void SyntacticAnalizer::mul_check(RetVal& rve) {
    if (rve.type.nElements >= 0 || ST.rv.type.nElements >= 0) {
        std::cout<<"An ARRAY can't be MULTIPLIED or DIVIDED!";
        exit(9);
    }

    if (rve.type.typeBase == TB_STRUCT || ST.rv.type.typeBase == TB_STRUCT) {
        std::cout<<"A STRUCT can't be MULTIPLIED or DIVIDED!";
        exit(9);
    }
    ST.cast(&ST.rv.type, &rve.type);
    ST.rv.type = ST.rv.getArithType(&rve.type, &ST.rv.type);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}

bool SyntacticAnalizer::expr_mul_helper() {
    startTk = currentTk;

    RetVal rve = ST.rv;
    if(consume(LA.MUL) || consume(LA.DIV) ) {
        if(!exprCast()) {
            currentTk = startTk;
            return false;
        }
    }
    else {
        currentTk = startTk;
        return false;
    }

    while(expr_mul_helper() ) {}
    mul_check(rve);
    return true;
}

bool SyntacticAnalizer::exprMul() {
    startTk = currentTk;
    int val = exprCast();

    if(!expr_mul_helper()) {
        if(val == 1) {
            return true;
        }
        else {currentTk = startTk; return false;}
    }
    else {
        return true;
    }

    return false;
}

void SyntacticAnalizer::add_check(RetVal& rve) {
    if (rve.type.nElements >= 0 || ST.rv.type.nElements >= 0) {
        std::cout<<"An ARRAY can't be ADDED or SUBSTRACTED!";
        exit(10);
    }

    if (rve.type.typeBase == TB_STRUCT || ST.rv.type.typeBase == TB_STRUCT) {
        std::cout<<"A STRUCT can't be ADDED or SUBSTRACTED!";
        exit(10);
    }
    ST.cast(&ST.rv.type, &rve.type);
    ST.rv.type = ST.rv.getArithType(&rve.type, &ST.rv.type);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}

bool SyntacticAnalizer::expr_add_helper() {
    startTk = currentTk;

    RetVal rve = ST.rv;
    if(consume(LA.ADD) || consume(LA.SUB)) {
        if(!exprMul()) {currentTk = startTk; return false;}
    }
    else { return false;}

    while(expr_add_helper() ) {}
    add_check(rve);
    return true;
}

bool SyntacticAnalizer::exprAdd() {
    startTk = currentTk;
    int val = exprMul();

    if(!expr_add_helper()) {
        if(val == 1) {
            return true;
        }
        else {currentTk = startTk; return false;}
    }
    else {
        return true;
    }

    return false;
}

void SyntacticAnalizer::rel_check(RetVal& rve) {
    if (rve.type.nElements >= 0 || ST.rv.type.nElements >= 0) {
        std::cout<<"An ARRAY can't be COMPARED!";
        exit(11);
    }

    if (rve.type.typeBase == TB_STRUCT || ST.rv.type.typeBase == TB_STRUCT) {
        std::cout<<"A STRUCT can't be COMPARED!";
        exit(11);
    }

    ST.rv.type = ST.createType(TB_INT,-1);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}


bool SyntacticAnalizer::expr_rel_helper() {
    startTk = currentTk;

    RetVal rve =ST.rv;
    if(consume(LA.LESS) || consume(LA.LESSEQ) || consume(LA.GREATER) || consume(LA.GREATEREQ)) {
        if(!exprAdd()) {currentTk = startTk; return false;}
    }
    else { return false;}

    while(expr_rel_helper() ) {}
    rel_check(rve);
    return true;
}

bool SyntacticAnalizer::exprRel() {
    startTk = currentTk;
    int val = exprAdd();

    if(!expr_rel_helper()) {
        if(val == 1) {
            return true;
        }
        else {currentTk = startTk; return false;}
    }
    else {
        return true;
    }

    return false;
}

void SyntacticAnalizer::eq_check(RetVal& rve) {

    if (rve.type.typeBase == TB_STRUCT || ST.rv.type.typeBase == TB_STRUCT) {
        std::cout<<"A STRUCT can't be COMPARED!";
        exit(12);
    }

    ST.rv.type = ST.createType(TB_INT,-1);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}

bool SyntacticAnalizer::expr_eq_helper() {
    startTk = currentTk;

    RetVal rve =ST.rv;
    if(consume(LA.EQUAL) || consume(LA.NOTEQ)) {
        if(!exprRel()) {currentTk = startTk; return false;}
    }
    else { return false;}

    while(expr_eq_helper() ) {}
    eq_check(rve);
    return true;
}

bool SyntacticAnalizer::exprEq() {
    startTk = currentTk;
    int val = exprRel();

    if(!expr_eq_helper()) {
        if(val == 1) {
            return true;
        }
        else {currentTk = startTk; return false;}
    }
    else {
        return true;
    }

    return false;
}

void SyntacticAnalizer::and_check(RetVal& rve) {

    if (rve.type.typeBase == TB_STRUCT || ST.rv.type.typeBase == TB_STRUCT) {
        std::cout<<"A STRUCT can't be logically tested!";
        exit(13);
    }

    ST.rv.type = ST.createType(TB_INT,-1);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}

bool SyntacticAnalizer::expr_and_helper() {
    startTk = currentTk;

    RetVal rve =ST.rv;
    if(consume(LA.AND)) {
        if(!exprEq()) {currentTk = startTk; return false;}
    }
    else { return false;}

    while(expr_and_helper() ) {}
    and_check(rve);
    return true;
}

bool SyntacticAnalizer::exprAnd() {
    startTk = currentTk;
    int val = exprEq();

    if(!expr_and_helper()) {
        if(val == 1) {
            return true;
        }
        else {currentTk = startTk; return false;}
    }
    else {
        return true;
    }

    return false;
}

void SyntacticAnalizer::or_check(RetVal& rve) {

    if (rve.type.typeBase == TB_STRUCT || ST.rv.type.typeBase == TB_STRUCT) {
        std::cout<<"A STRUCT can't be logically tested!";
        exit(14);
    }

    ST.rv.type = ST.createType(TB_INT,-1);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}

bool SyntacticAnalizer::expr_or_helper() {
    startTk = currentTk;

    RetVal rve =ST.rv;
    if(consume(LA.OR)) {
        if(!exprAnd()) {currentTk = startTk; return false;}
    }
    else { return false;}

    while(expr_or_helper() ) {}
    or_check(rve);
    return true;
}

bool SyntacticAnalizer::exprOr() {
    startTk = currentTk;
    int val = exprAnd();

    if(!expr_or_helper()) {
        if(val == 1) {
            return true;
        }
        else {currentTk = startTk; return false;}
    }
    else {
        return true;
    }

    return false;
}

void SyntacticAnalizer::assign_check(RetVal& rve) {

    if (!rve.isLVal) {
        std::cout<<"Cannot assign to a NON-LEFT VALUE!";
        exit(15);
    }
    if (rve.type.nElements >= 0 || ST.rv.type.nElements >= 0) {
        std::cout<<"An ARRAY can't be ASSIGNED!";
        exit(15);
    }

    ST.cast(&ST.rv.type, &rve.type);
    ST.rv.isCtVal = 0;
    ST.rv.isLVal = 0;
}

bool SyntacticAnalizer::expr_assign_helper() {
    startTk = currentTk;

    RetVal rve =ST.rv;
    if( consume(LA.ASSIGN) ) {
        if( !exprAssign()) {currentTk = startTk; return false;}
    }
    else {
        return false;
    }

    while(expr_eq_helper() ) {}
    assign_check(rve);
    return true;
}

bool SyntacticAnalizer::exprAssign() {
    startTk = currentTk;
    int val = exprOr();

    if(!expr_assign_helper()) {
        if(val == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
    return false;
}

/**********
 * OTHERS *
 **********/


bool SyntacticAnalizer::typeBase() {
//    std::cout<<"typeBase\n";
    startTk = currentTk;
//    std::cout<<currentTk->code<<std::endl;
    if(consume(LA.INT)) return true;
//    std::cout<< currentTk->code<<std::endl;
    if(consume(LA.DOUBLE)) return true;
    if(consume(LA.CHAR)) return true;
    if(consume(LA.STRUCT)){
        if(consume(LA.ID)) return true;
        currentTk = startTk;
        return false;
    }

    return false;
}

int SyntacticAnalizer::arrayDecl() {
    startTk = currentTk;
    if(!consume(LA.LBRACKET)) { return -1;}
    if(consume(LA.RBRACKET)) {
        ST.head.back().type.nElements = 0;
        return 0;
    }
    else {
        auto arr = ST.head.back();
        expr();
        if(!ST.rv.isCtVal) { std::cout<<"Array size is not a constant";  exit(20);}
        if(ST.rv.type.typeBase != TB_INT) { std::cout<<"Array size is not an integer";  exit(20);}
        arr.type.nElements = std::get<long int>(ST.rv.ctVal);
        if (!consume(LA.RBRACKET)) {
//            std::cout << "Am crapat x2\n";
            currentTk = startTk;
            return -1;
        }
    }
    return 0;
}

bool SyntacticAnalizer::typeName(Type *t) {
    t->typeBase = currentTk->code;
    if(!typeBase()) { return false;}
    if(arrayDecl()){
        t->nElements = 0;
    }
    return true;
}

bool SyntacticAnalizer::declVar() {
//    std::cout<<"ME HERE"<<std::endl;
    startTk = currentTk;
    Type t = Type();

    t.typeBase = get_typeBase(currentTk->code);
    if(!typeBase()){ return false;}

    add_var();
    if(!consume(LA.ID)){currentTk = startTk; return false;}
    t.nElements = arrayDecl();
    set_var_type(t);

    if(consume(LA.SEMICOLON)) return true;
    else{
    while (consume(LA.COMMA)){
        add_var();
        if(!consume(LA.ID)) {std::cout<<"Error: Bad VARIABLE declaration 2"<<std::endl; exit(1);}
        t.nElements = arrayDecl();
        set_var_type(t);
    }

    if(!consume(LA.SEMICOLON)) {currentTk = startTk; return false;}
    }
    return true;
}

bool SyntacticAnalizer::declStruct() {
//    std::cout<<"declStruct\n";
    startTk = currentTk;
    if(!consume(LA.STRUCT)) { return false;}
    add_struct();
    if(!consume(LA.ID)) {std::cout<<"Error: Bad STRUCT statement"<<std::endl; exit(1);}
    if(!consume(LA.LACC)) { currentTk = startTk; return false;}
    while (declVar()){}
    if(!consume(LA.RACC)) { currentTk = startTk; return false;}
    if(!consume(LA.SEMICOLON)) {std::cout<<"Error: Bad STRUCT statement"<<std::endl; exit(1);}

    ST.crtStruct.name = "";
//    ST.crtStruct.print_sbl();
//    if(ST.crtStruct.name == ""){
//        std::cout<<"Am iesit din struct"<<std::endl;
//    }
    return true;
}

bool SyntacticAnalizer::funcArg() {
    startTk = currentTk;
    Type t = Type();
    bool is_pointer = false;

    t.typeBase = get_typeBase(currentTk->code);
    if(!typeBase()) { return false;}
    if(consume(LA.MUL)) {t.nElements = 0; is_pointer = true;}

    add_arg();
    if(!consume(LA.ID)) {std::cout<<"Error: Bad ARGUMENT statement"<<std::endl; exit(1);}

    if(!is_pointer){
        t.nElements = arrayDecl();
    }

    set_var_type(t);
    set_arg_type(t);

    return true;
}

bool SyntacticAnalizer::declFunc() {
    startTk = currentTk;
    Type t = Type();

    t.typeBase = get_typeBase(currentTk->code);
    if(!consume(LA.VOID)) {
        if (!typeBase()) { return false;}
        else {
//            std::cout<< currentTk->code<<std::endl;
            consume(LA.MUL);}
    }
    else {
        if (consume(LA.MUL)) {
            {std::cout<<"Error: Can not have VOID pointer"<<std::endl; exit(1);}
        }
    }

    add_func(t);
    if(!consume(LA.ID)){ST.crtFunc.name=""; currentTk = startTk; ST.delete_lastSymbol(); return false;}
    if(!consume(LA.LPAR)) {ST.crtFunc.name=""; currentTk = startTk; ST.delete_lastSymbol();  return false;}
    ST.crtDepth++;
    if(consume(LA.RPAR)){
        ST.crtDepth--;
        if(consume(LA.SEMICOLON)){return true;}
        if(!stm()){std::cout<<"Error: Missing statement or semicolon"<<std::endl; exit(1);}
    }
    else{
        funcArg();

        while (consume(LA.COMMA)){
            if(!funcArg()) {std::cout<<"Error: Missing function argument"<<std::endl; exit(1);}
        }

        if (!consume(LA.RPAR)) {std::cout<<"Error: Missing right parenthesis"<<std::endl; exit(1);}

        if(consume(LA.SEMICOLON)){ ST.crtDepth--; return true;}
        if(!stm()){std::cout<<"Error: Missing statement or semicolon"<<std::endl; exit(1);}
//        ST.delete_lastSymbol(); ST.crtDepth--;
        ST.crtFunc.name = "";
    }


    return true;
}

/**************
 * STATEMENTS *
 **************/
bool SyntacticAnalizer::stmCompound() {
//    std::cout<<"COMPOUND"<<std::endl;
    startTk = currentTk;
    if(!consume(LA.LACC)) {return false;}
    ST.crtDepth++;
    if(consume(LA.RACC)) {
        ST.deleteSymbolAfter(ST.crtDepth);
        ST.crtDepth--;
        return true;
    }

    while(declVar() || stm()){
        if(consume(LA.RACC)) {
            ST.deleteSymbolAfter(ST.crtDepth);
            ST.crtDepth--;
            return true;
        }
    }

    if(!consume(LA.RACC)) {
        currentTk = startTk;
        ST.deleteSymbolAfter(ST.crtDepth);
        ST.crtDepth--;
        exit(5);
    }

    exit(5);
}

bool SyntacticAnalizer::stm() {
//    std::cout<<"ME STM"<<std::endl;
    if(stmCompound()) return true;
    if(rule_IF())return true;
    if(rule_WHILE()) return true;
    if(rule_FOR()) return true;
    if(rule_BREAK()) return true;
    if(rule_RETURN()) return true;
    if(rule_EXPR()) return true;

    return false;
}



bool SyntacticAnalizer::unit() {

    while(declStruct() || declFunc()  || declVar() ){}
    if(!consume(LA.END)) return false;

    return true;
}

/**************************************************
 *        FCT FOR SYMBOL TABLE               ******
 **************************************************/

bool SyntacticAnalizer::check_name(int code) {
    if (code == LA.ID) return true;
    return false;
}

void SyntacticAnalizer::add_arg() {
    if(currentTk)
        if (check_name(currentTk->code)){
            char *tk_name = std::get<char *>(currentTk->text);
            Symbol s = ST.addSymbol(tk_name,CLS_VAR,MEM_ARG);
            auto index = ST.findSymbol(tk_name);
            ST.head[index].type.TB_name = ST.crtFunc.name;
            ST.add_arg_to_Func(s);
            return;
        }
    exit(1);
}

void SyntacticAnalizer::set_var_type(Type t) {
    ST.head.back().type.typeBase = t.typeBase;
    ST.head.back().type.TB_name = t.TB_name;
    ST.head.back().type.nElements = t.nElements;
}

void SyntacticAnalizer::add_struct() {
    if(currentTk)
        if (check_name(currentTk->code)){
            char *tk_name = std::get<char *>(currentTk->text);
            if (ST.existSymbol(tk_name)) {
                std::cout<<"ERROR: STRUCT already defined, can not be overriden";
                exit(2);
            }
            Symbol s = ST.addSymbol(tk_name,CLS_STRUCT);
            ST.crtStruct = s;
            return;
        }
    exit(2);
}

void SyntacticAnalizer::add_var() {
    if(currentTk)
        if (check_name(currentTk->code)){
            char *tk_name = std::get<char *>(currentTk->text);

            Symbol s;
            if(ST.crtStruct.name != NULL && strlen(ST.crtStruct.name) != 0){
                s = ST.addSymbol(tk_name,CLS_VAR);
                ST.add_var_to_Struct(s);
            }
            else if(ST.crtFunc.name != NULL && strlen(ST.crtFunc.name) != 0){

                if (ST.existSymbol(tk_name)) {
                    auto index = ST.findSymbol(tk_name);
                    if((ST.head[index].depth == ST.crtDepth && ST.head[index].mem != MEM_ARG) || ST.head[index].mem == MEM_GLOBAL){
                        std::cout<<"ERROR: Variable already defined, can not be overriden";
                        exit(3);
                    }

                }
                s = ST.addSymbol(tk_name,CLS_VAR,MEM_LOCAL);
            }
            else{
                auto index = ST.findSymbol(tk_name);
                if (index != -1 && ST.head[index].mem == MEM_GLOBAL) {
                    std::cout<<"ERROR: Variable already defined, can not be overriden";
                    exit(3);
                }
                s = ST.addSymbol(tk_name,CLS_VAR,MEM_GLOBAL);
            }

            return;
        }
    exit(3);
}

int SyntacticAnalizer::get_typeBase(int code) {
    if(code == LA.INT) return 0;
    if(code ==LA.DOUBLE) return 1;
    if(code ==LA.CHAR) return 2;
    if(code ==LA.STRUCT) return 3;
    if(code ==LA.VOID) return 4;

    return -1;
}

void SyntacticAnalizer::add_func(Type t) {
    if(currentTk)
        if (check_name(currentTk->code)){
            char *tk_name = std::get<char *>(currentTk->text);
            auto idx = ST.findSymbol(tk_name);
            if (idx != -1 && ST.head[idx].cls == CLS_FUNC) {
                std::cout<<"ERROR: FUNC already defined, can not be overriden";
                exit(4);
            }
            Symbol s = ST.addSymbol(tk_name,CLS_FUNC);
            auto index = ST.findSymbol(s.name);
            ST.head[index].type.typeBase = t.typeBase;
            s.type.typeBase = t.typeBase;
            ST.crtFunc = s;
            return;
        }
    exit(4);
}

void SyntacticAnalizer::set_arg_type(Type t) {
    auto index = ST.findSymbol(ST.crtFunc.name);
    ST.head[index].members.back().type.typeBase = t.typeBase;
    ST.head[index].members.back().type.TB_name = t.TB_name;
    ST.head[index].members.back().type.nElements = t.nElements;
}

bool SyntacticAnalizer::is_array_element(){
    RetVal rve = ST.rv;
    if(!consume(LA.LBRACKET)) return false;
    if(ST.rv.type.nElements == -1){
        std::cout<<"ERROR: Non-array can not be indexed"<<std::endl;
        exit(80);
    }
    if(consume(LA.RBRACKET)) {
        std::cout<<"ERROR: Missing array index"<<std::endl;
        exit(81);
    }

    if(!expr()) {
        std::cout<<"ERROR: Unexpected argument for array index"<<std::endl;
        exit(83);
    }
    else{
        if(ST.rv.type.typeBase != TB_INT){
            std::cout<<"ERROR: Invalide array index type"<<std::endl;
            exit(84);
        }
    }

    if(!consume(LA.RBRACKET)) {
        std::cout<<"ERROR: Missing RBRACKET"<<std::endl;
        exit(85);
    }

    ST.rv = rve;
    return true;
}

void SyntacticAnalizer::add_predef_func() {

    ST.add_put_s(reinterpret_cast<void *>(&put_s));
    ST.add_put_i(reinterpret_cast<void *>(&put_i));
    ST.add_put_d(reinterpret_cast<void *>(&put_d));
    ST.add_put_c(reinterpret_cast<void *>(&put_c));
    ST.add_get_s(reinterpret_cast<void *>(&get_s));
    ST.add_get_i(reinterpret_cast<void *>(&get_i));
    ST.add_get_d(reinterpret_cast<void *>(&get_d));
    ST.add_get_c(reinterpret_cast<void *>(&get_c));
//    ST.add_seconds();


}

void SyntacticAnalizer::put_s() {
    std::cout<<VM.pop_a()<<std::endl;
}

void SyntacticAnalizer::put_i() {
    std::cout<<"put_i\n";
    std::cout<<VM.pop_i()<<std::endl;
}

void SyntacticAnalizer::put_d() {
    std::cout<<VM.pop_d()<<std::endl;
}

void SyntacticAnalizer::put_c() {
    std::cout<<VM.pop_c()<<std::endl;
}

void SyntacticAnalizer::get_s() {
    char *a;
    strcpy(a,"GETS");
    VM.push_a(a);
}

void SyntacticAnalizer::get_i() {
    VM.push_i(99999);
}

void SyntacticAnalizer::get_d() {
    VM.push_d(999.99);
}

void SyntacticAnalizer::get_c() {
    VM.push_d('C');
}