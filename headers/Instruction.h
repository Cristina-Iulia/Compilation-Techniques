//
// Created by Iulia on 22/05/2022.
//

#ifndef SYNTACTICANALIZER_CPP_INSTRUCTION_H
#define SYNTACTICANALIZER_CPP_INSTRUCTION_H

#include <iostream>
#include <variant>
#include <vector>
#include <algorithm>
enum Instruction_Type {
    O_ADD_C       = 0,   O_ADD_D      = 1, O_ADD_I        = 2,
    O_AND_A       = 3,   O_AND_C      = 4, O_AND_D        = 5, O_AND_I = 6,
    O_CALL        = 7, O_CALLEXT      = 8,
    O_CAST_C_D    = 9,  O_CAST_C_I    = 10,
    O_CAST_D_C    = 11, O_CAST_D_I    = 12,
    O_CAST_I_C    = 13, O_CAST_I_D    = 14,
    O_DIV_C       = 15, O_DIV_D       = 16, O_DIV_I       = 17,
    O_DROP        = 18, O_ENTER       = 19,
    O_EQ_A        = 20, O_EQ_C        = 21, O_EQ_D        = 22, O_EQ_I = 23,
    O_GREATER_C   = 24, O_GREATER_D   = 25, O_GREATER_I   = 26,
    O_GREATEREQ_C = 27, O_GREATEREQ_D = 28, O_GREATEREQ_I = 29,
    O_HALT        = 30, O_INSERT      = 31,
    O_JF_A        = 32, O_JF_C        = 33, O_JF_D        = 34, O_JF_I = 35,
    O_JMP         = 36,
    O_JT_A        = 37, O_JT_C        = 38, O_JT_D        = 39, O_JT_I = 40,
    O_LESS_C      = 41, O_LESS_D      = 42, O_LESS_I      = 43,
    O_LESSEQ_C    = 44, O_LESSEQ_D    = 45, O_LESSEQ_I    = 46,
    O_LOAD        = 47,
    O_MUL_C       = 48, O_MUL_D       = 49, O_MUL_I       = 50,
    O_NEG_C       = 51, O_NEG_D       = 52, O_NEG_I       = 53,
    O_NOTEQ_A     = 54, O_NOTEQ_C     = 55, O_NOTEQ_D     = 56, O_NOTEQ_I = 57,
    O_OFFSET      = 58,
    O_OR_A        = 59, O_OR_C        = 60, O_OR_D        = 61, O_OR_I    = 62,
    O_PUSHFPADDR  = 63,
    O_PUSHCT_A    = 64, O_PUSHCT_C    = 65, O_PUSHCT_D    = 66, O_PUSHCT_I    = 67,
    O_RET         = 68, O_STORE       = 69,
    O_SUB_C       = 70, O_SUB_D       = 71, O_SUB_I       = 72, O_NOP = 73,
    O_NOT_A       = 74, O_NOT_C       = 75, O_NOT_D       = 76, O_NOT_I = 77
};

class Instruction {
public:

    int op_code;
    std::vector<std::variant<long, double, void *>> args;

    Instruction();

    void init_args(std::variant<long, double, void *> arr);
    inline bool operator==(const Instruction& i) {
        return ((this->op_code == i.op_code) && (this->args == i.args));
    }

};


#endif //SYNTACTICANALIZER_CPP_INSTRUCTION_H
