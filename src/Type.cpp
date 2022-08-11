//
// Created by Iulia on 14/05/2022.
//

#include <iostream>
#include "../headers/Type.h"

Type::Type(){
    nElements = -1;
}

Type::Type(int tBase, int nElem) {
    typeBase = tBase;
    nElements = nElem;
}

RetVal::RetVal() {
    type = Type();
}

void RetVal::cast(Type *dst, Type *src) {
    if(src->nElements>-1){
        if(dst->nElements>-1){
            if(src->typeBase!=dst->typeBase){
                std::cout<<"An array cannot be converted to an array of another type";
                exit(61);
            }
        }else{
            std::cout<<"an array cannot be converted to a non-array";
            exit(62);
        }
    }else{
        if(dst->nElements>-1){
            std::cout<<"a non-array cannot be converted to an array";
            exit(63);
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
                exit(64);
            }
    }
    std::cout<<"incompatible types";
    exit(65);
}

Type RetVal::getArithType(Type *s1, Type *s2) {

    Type t = Type();
    switch (s1->typeBase) {
        case TB_CHAR:
            switch(s2->typeBase){
                case TB_CHAR:
                    t.typeBase = TB_CHAR;
                    return t;
                case TB_INT:
                    t.typeBase = TB_INT;
                    return t;
                case TB_DOUBLE:
                    t.typeBase = TB_DOUBLE;
                    return t;
                case TB_STRUCT:
                    std::cout<<"Can not perform operations on structure";
                    exit(51);
                case TB_VOID:
                    std::cout<<"Can not perform operations on void";
                    exit(52);
            }
        case TB_INT:
            switch(s2->typeBase){
                case TB_CHAR:
                case TB_INT:
                    t.typeBase = TB_INT;
                    return t;
                case TB_DOUBLE:
                    t.typeBase = TB_DOUBLE;
                    return t;
                case TB_STRUCT:
                    std::cout<<"Can not perform operations on structure";
                    exit(53);
                case TB_VOID:
                    std::cout<<"Can not perform operations on void";
                    exit(54);
            }
        case TB_DOUBLE:
            switch(s2->typeBase){
                case TB_CHAR:
                case TB_INT:
                case TB_DOUBLE:
                    t.typeBase = TB_DOUBLE;
                    return t;
                case TB_STRUCT:
                    std::cout<<"Can not perform operations on structure";
                    exit(55);
                case TB_VOID:
                    std::cout<<"Can not perform operations on void";
                    exit(56);
            }
        case TB_STRUCT:
            std::cout<<"Can not perform operations on structure";
            exit(57);

        case TB_VOID:
            std::cout<<"Can not perform operations on void";
            exit(58);
    }

    std::cout<<"Invalid type";
    exit(59);
}


