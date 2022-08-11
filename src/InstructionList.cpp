//
// Created by Iulia on 22/05/2022.
//

#include "../headers/InstructionList.h"
#include <iostream>


InstructionList::InstructionList()
{}

void InstructionList::insert_instr_after(const Instruction& after, const Instruction& i) {
    auto index = std::find(head.begin(), head.end(), after);
    if( index != head.end() ) {
        head.insert(index, i);
    }
    else {
        std::cout<<"NOT FOUND in INSTRUCTION_LIST!"<<std::endl;
        exit(151);
    }
}

void InstructionList::insert_instr(const Instruction& i) {
    head.push_back(i);
}

void InstructionList::add_instr_after(const Instruction& after, const int& op_code) {
    Instruction i = Instruction();
    i.op_code = op_code;
    insert_instr_after(after, i);
}

void InstructionList::add_instr(const int& op_code) {
    Instruction i = Instruction();
    i.op_code = op_code;
    insert_instr(i);
}

void InstructionList::delete_instr_after(const Instruction& start) {
    auto index = std::find(head.begin(), head.end(), start);
    if( index != head.end() ) {
        head.erase(index, head.end());
    }
    else {
        std::cout<<"NOT FOUND in INSTRUCTION_LIST!"<<std::endl;
        exit(152);
    }
}

void InstructionList::add_instr_A(const int &op_code, void *addr) {
    Instruction i = Instruction();
    i.op_code = op_code;
    i.init_args(addr);
    insert_instr(i);
}

void InstructionList::add_instr_I(const int &op_code, long int val) {
    Instruction i = Instruction();
    i.op_code = op_code;
    i.init_args(val);
    insert_instr(i);
}

void InstructionList::add_instr_II(const int &op_code, long int val1, long int val2) {
    Instruction i = Instruction();
    i.op_code = op_code;
    i.init_args(val1);
    i.init_args(val2);
    insert_instr(i);
}

void InstructionList::add_instr_D(const int &op_code, double val) {
    Instruction i = Instruction();
    i.op_code = op_code;
    i.init_args(val);
    insert_instr(i);
}
