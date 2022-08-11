//
// Created by Iulia on 02/05/2022.
//

#ifndef SYNTACTICANALIZER_CPP_SYMBOLTABLE_H
#define SYNTACTICANALIZER_CPP_SYMBOLTABLE_H
#include "Symbol.h"


class SymbolTable {
public:

    /*****************
     * MEMBERS
     * ****************/
    std::vector<Symbol> head;
    int crtDepth;
    Symbol crtFunc;
    Symbol crtStruct;
    RetVal rv;

    /*****************
     * CONSTRUCTORS
     * ****************/
    SymbolTable();
    Symbol addSymbol(const char *name = "", int cls = -1, int mem = -1);


    /*****************
     * ADDING METHODS
     * ****************/
    void add_arg_to_Func(Symbol s);
    void add_var_to_Struct(Symbol s);
    void set_retVal(Type t, int isL , int isCt, long int val);
    void set_retVal(Type t, int isL , int isCt, double val);
    void set_retVal(Type t, int isL , int isCt, char * val);
    void set_retVal(Type t, int isL , int isCt);
    Type createType(int typeBase,int nElements);
    /*****************
     * DELETING METHODS
     * ****************/
    void delete_lastSymbol();
    void deleteSymbolAfter(int crt_d);


    /*****************
     * SEARCHING METHODS
     * ****************/
    size_t findSymbol(const char *name);
    size_t findSymbol(std::vector<Symbol>start, const char *name);
    bool existSymbol(const char *name);


    /*****************
     * PRINTING METHODS
     * ****************/
    void print_symbT();

    void cast(Type *dst,Type *src);


    /*****************
     * PREDEFINED FUNCTIONS ADDERS
     * ****************/

    void add_put_s(void *ad);
    void add_put_i(void *ad);
    void add_put_d(void *ad);
    void add_put_c(void *ad);
    void add_get_s(void *ad);
    void add_get_i(void *ad);
    void add_get_d(void *ad);
    void add_get_c(void *ad);
    void add_seconds(void *ad);
};


#endif //SYNTACTICANALIZER_CPP_SYMBOLTABLE_H
