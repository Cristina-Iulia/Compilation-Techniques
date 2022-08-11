//
// Created by Iulia on 02/05/2022.
//

#include "../headers/Symbol.h"
#include <iostream>

Symbol::Symbol(const char *name, int cls, int mem, int depth)
:   name(name),
    cls(cls),
    mem(mem),
    depth(depth)
{
}
Symbol::Symbol(const char *name, int cls)
        :   name(name),
            cls(cls)
{
}

Symbol::Symbol()
        :   name("")
{
}

void Symbol::print_sbl() {
    std::cout<<'\t'<<"Name : "<<name<<'\t';
    print_cls(cls);
    print_mem(mem);
    std::cout<<'\t'<<"Depth : "<<depth<<'\t';
    print_typeBase(type.typeBase);
    if(type.nElements >= 0){
        std::cout<<"VECTOR"<<'\t';
    }
}

void Symbol::print_cls(int cls) {
    switch (cls) {
        case 0 : std::cout<<"cls: CLS_VAR"<<'\t';
            break;
        case 1 : std::cout<<"cls: CLS_FUNC"<<'\t';
            break;
        case 2 : std::cout<<"cls: CLS_EXTFUNC"<<'\t';
            break;
        case 3 : std::cout<<"cls: CLS_STRUCT"<<'\t';
            break;
        default: std::cout<<'\t';
            break;
    }

}
void Symbol::print_mem(int mem) {
    switch (mem) {
        case -1 : std::cout<<"mem: no-mem"<<'\t';
            break;
        case 0 : std::cout<<"mem: MEM_GLOBAL"<<'\t';
            break;
        case 1 : std::cout<<"mem: MEM_ARG"<<'\t';
            break;
        case 2 : std::cout<<"mem: LOCAL"<<'\t';
            break;
        default: std::cout<<'\t';
            break;
    }

}

void Symbol::print_typeBase(int tb) {
//    std::cout<<tb;
    switch (tb) {
        case 0 : std::cout<<"type: TB_INT"<<'\t';
            break;
        case 1 : std::cout<<"type: TB_DOUBLE"<<'\t';
            break;
        case 2 : std::cout<<"type: TB_CHAR"<<'\t';
            break;
        case 3 : std::cout<<"type: TB_STRUCT"<<'\t';
            break;
        case 4 : std::cout<<"type: TB_VOID"<<'\t';
            break;
        default: std::cout<<"not found"<<'\t';
            break;
    }

}