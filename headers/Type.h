//
// Created by Iulia on 14/05/2022.
//

#ifndef SYNTACTICANALIZER_CPP_TYPE_H
#define SYNTACTICANALIZER_CPP_TYPE_H
#include <vector>
#include<variant>

enum{CLS_VAR,CLS_FUNC,CLS_EXTFUNC,CLS_STRUCT};
enum{MEM_GLOBAL,MEM_ARG,MEM_LOCAL};

enum{TB_INT,TB_DOUBLE,TB_CHAR,TB_STRUCT,TB_VOID};

class Type {
public:
    int typeBase; // TB_*
    const char *TB_name;
    int nElements; // >0 array of given size, 0=array without size, <0 non array

    Type();
    Type(int typeBase,int nElements);
};

class RetVal {
public:
    Type type;
    int isLVal;     // if it is a LVal
    int isCtVal;    // if it is a constant value (int, real, char, char[])
    std::variant<char *, long int, double> ctVal;

    RetVal();

    void cast(Type *dst,Type *src);
    Type getArithType(Type *s1,Type *s2);
};

#endif //SYNTACTICANALIZER_CPP_TYPE_H
