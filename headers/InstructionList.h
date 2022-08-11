//
// Created by Iulia on 22/05/2022.
//

#ifndef SYNTACTICANALIZER_CPP_INSTRUCTIONLIST_H
#define SYNTACTICANALIZER_CPP_INSTRUCTIONLIST_H

#include <list>
#include "Instruction.h"

class InstructionList {
public:
    std::list<Instruction> head;

    InstructionList();

    void insert_instr_after(const Instruction& after, const Instruction& i);
    void insert_instr(const Instruction& i);


    void add_instr_after(const Instruction& after, const int& op_code);
    void add_instr(const int& op_code);
    void add_instr_A(const int& op_code, void *addr);

    void delete_instr_after(const Instruction& start);

    void add_instr_I(const int &op_code, long val);
    void add_instr_D(const int &op_code, double val);

    void add_instr_II(const int &op_code, long val1, long val2);


};


#endif //SYNTACTICANALIZER_CPP_INSTRUCTIONLIST_H
