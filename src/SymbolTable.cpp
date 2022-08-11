//
// Created by Iulia on 02/05/2022.
//

#include <iostream>
#include "../headers/SymbolTable.h"
#include <algorithm>
#include <string.h>
#include <vector>

SymbolTable::SymbolTable()
{
    crtDepth = 0;
    crtFunc = Symbol();
    crtStruct = Symbol();
    rv = RetVal();

}

Symbol SymbolTable::addSymbol(const char *name, int cls, int mem) {
    Symbol s = Symbol(name,cls,mem,crtDepth);
    head.push_back(s);
    return s;
}

size_t SymbolTable::findSymbol(const char *name) {
    size_t index = -1;
    for(size_t i = 0 ; i < head.size(); ++ i) {
        if(strcmp(head[i].name,name) == 0) {
            index = i;
        }
    }

    if(index != -1) {
        return index;
    }
    else {
        return -1;
    }

}

void SymbolTable::print_symbT() {

    std::cout<<std::endl;
    for(size_t i = 0 ; i < head.size(); ++i) {
        std::cout<<std::endl<<"Symbol "<<i<<":";
        head[i].print_sbl();
        std::cout<<std::endl;
    }
}

void SymbolTable::deleteSymbolAfter(int crt_d) {

    for(size_t i = 0 ; i < head.size(); ++i) {
        if(head[i].depth == crt_d) {
//            head[i].print_sbl();
            head.erase(head.begin()+i);
            return;
        }
    }

}

void SymbolTable::add_arg_to_Func(Symbol s) {
    auto index = findSymbol(crtFunc.name);
    auto i = findSymbol(s.name);
    head[index].members.push_back(head[i]);
}

void SymbolTable::add_var_to_Struct(Symbol s) {
    auto index = findSymbol(crtStruct.name);
    auto i = findSymbol(s.name);
//    std::cout<<head[index].name;
//    std::cout<<head[i].name;
    head[index].members.push_back(head[i]);

}

bool SymbolTable::existSymbol(const char *name) {
    size_t index = -1;
    for(size_t i = 0 ; i < head.size(); ++ i) {
        if(strcmp(head[i].name,name) == 0) {
            index = i;
        }
    }

    if(index != -1) {
        return true;
    }
    else {
        return false;
    }
}

void SymbolTable::delete_lastSymbol() {
    head.pop_back();
}

void SymbolTable::set_retVal(Type t, int isL, int isCt, long int val) {
    rv.type = t;
    rv.isLVal = isL;
    rv.isCtVal = isCt;
    rv.ctVal = val;
}

void SymbolTable::set_retVal(Type t, int isL, int isCt, double val) {
    rv.type = t;
    rv.isLVal = isL;
    rv.isCtVal = isCt;
    rv.ctVal = val;
}

void SymbolTable::set_retVal(Type t, int isL, int isCt, char *val) {
    rv.type = t;
    rv.isLVal = isL;
    rv.isCtVal = isCt;
    rv.ctVal = val;
}

Type SymbolTable::createType(int typeBase, int nElements) {
    return Type(typeBase,nElements);
}

void SymbolTable::set_retVal(Type t, int isL, int isCt) {
    rv.type = t;
    rv.isLVal = isL;
    rv.isCtVal = isCt;
}

void SymbolTable::cast(Type *dst, Type *src) {
    if(src->nElements>-1){
        if(dst->nElements>-1){
            if(src->typeBase!=dst->typeBase){
                std::cout<<"An array cannot be converted to an array of another type";
                exit(71);
            }
        }else{
            std::cout<<"an array cannot be converted to a non-array";
            exit(72);
        }
    }else{
        if(dst->nElements>-1){
            std::cout<<"a non-array cannot be converted to an array";
            exit(73);
        }
    }
    switch(src->typeBase){
        case TB_CHAR:
        case TB_INT:
        case TB_DOUBLE:
            switch(dst->typeBase){
                case TB_CHAR:
                case TB_INT:
                case TB_DOUBLE:
                    return;
            }
        case TB_STRUCT:
            if(dst->typeBase==TB_STRUCT){
                if(src->TB_name!=dst->TB_name)
                    std::cout<<"a structure cannot be converted to another one";
                exit(74);
            }
    }
    std::cout<<"incompatible types";
    exit(75);

}

size_t SymbolTable::findSymbol(std::vector<Symbol> start, const char *name) {
    size_t index = -1;
    for(size_t i = 0 ; i < start.size(); ++ i) {
        if(strcmp(start[i].name,name) == 0) {
            index = i;
        }
    }

    if(index != -1) {
        return index;
    }
    else {
        return -1;
    }
}
void SymbolTable::add_put_s(void * ad){
    ///////   Add put_s()
    Symbol s = addSymbol("put_s", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_VOID;
    head[index].depth = 0;
    head[index].addr = ad;
    Symbol arg = Symbol("s",CLS_VAR,MEM_ARG,1);
    arg.type.typeBase = TB_CHAR;
    arg.type.nElements = 0;
    head[index].members.push_back(arg);
}

void SymbolTable::add_put_i(void * ad){
    ///////   Add put_i()
    Symbol s = addSymbol("put_i", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_VOID;
    head[index].depth = 0;
    head[index].addr = ad;
    Symbol arg = Symbol("i",CLS_VAR,MEM_ARG,1);
    arg.type.typeBase = TB_INT;
    arg.type.nElements = -1;
    head[index].members.push_back(arg);
}

void SymbolTable::add_put_d(void * ad){
    ///////   Add put_d()
    Symbol s = addSymbol("put_d", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_VOID;
    head[index].depth = 0;
    head[index].addr = ad;
    Symbol arg = Symbol("i",CLS_VAR,MEM_ARG,1);
    arg.type.typeBase = TB_INT;
    arg.type.nElements = -1;
    head[index].members.push_back(arg);
}

void SymbolTable::add_put_c(void * ad){
    ///////   Add put_c()
    Symbol s = addSymbol("put_c", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_CHAR;
    head[index].depth = 0;
    head[index].addr = ad;
    Symbol arg = Symbol("i",CLS_VAR,MEM_ARG,1);
    arg.type.typeBase = TB_INT;
    arg.type.nElements = -1;
    head[index].members.push_back(arg);
}

void SymbolTable::add_get_s(void * ad){
    ///////   Add get_s()
    Symbol s = addSymbol("get_s", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_VOID;
    head[index].depth = 0;
    head[index].addr = ad;
    Symbol arg = Symbol("s",CLS_VAR,MEM_ARG,1);
    arg.type.typeBase = TB_CHAR;
    arg.type.nElements = 0;
    head[index].members.push_back(arg);
}

void SymbolTable::add_get_i(void * ad){
    ///////   Add get_i()
    Symbol s = addSymbol("get_i", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_INT;
    head[index].depth = 0;
    head[index].addr = ad;
}

void SymbolTable::add_get_d(void * ad){
    ///////   Add get_d()
    Symbol s = addSymbol("get_d", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_DOUBLE;
    head[index].depth = 0;
    head[index].addr = ad;
}

void SymbolTable::add_get_c(void * ad){
    ///////   Add get_c()
    Symbol s = addSymbol("get_c", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_CHAR;
    head[index].depth = 0;
    head[index].addr = ad;
}

void SymbolTable::add_seconds(void * ad){
    ///////   Add seconds()
    Symbol s = addSymbol("seconds", CLS_FUNC);
    auto index = findSymbol(s.name);
    head[index].type.typeBase = TB_DOUBLE;
    head[index].depth = 0;
    head[index].addr = ad;
}



