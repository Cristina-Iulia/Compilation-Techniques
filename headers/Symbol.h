//
// Created by Iulia on 02/05/2022.
//

#ifndef SYNTACTICANALIZER_CPP_SYMBOL_H
#define SYNTACTICANALIZER_CPP_SYMBOL_H
#include <vector>
#include "Type.h"

//enum{CLS_VAR,CLS_FUNC,CLS_EXTFUNC,CLS_STRUCT};
//enum{MEM_GLOBAL,MEM_ARG,MEM_LOCAL};
//
//enum{TB_INT,TB_DOUBLE,TB_CHAR,TB_STRUCT,TB_VOID};
//typedef struct{
//    int typeBase; // TB_*
//    const char *TB_name;
//    int nElements; // >0 array of given size, 0=array without size, <0 non array
//}Type;

class Symbol {
public:

    /*****************
     * MEMBERS
     * ****************/
    const char *name;

    void * addr; // vm: the memory address for local Lvars
    long int value;

    int cls;
    int mem;
    int depth;
    Type type;
    std::vector<Symbol> members;

    /*****************
     * CONSTRUCTORS
     * ****************/
    Symbol(const char *name, int cls, int mem, int depth);
    Symbol(const char *name, int cls);
    Symbol();



    /*****************
     * PRINTING METHODS
     * ****************/
    void print_sbl();
    void print_cls(int cls);
    void print_mem(int mem);
    void print_typeBase(int tb);
};

#endif //SYNTACTICANALIZER_CPP_SYMBOL_H
