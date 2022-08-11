//
// Created by Iulia on 22/05/2022.
//

#ifndef SYNTACTICANALIZER_CPP_VIRTUALMACHINE_H
#define SYNTACTICANALIZER_CPP_VIRTUALMACHINE_H

#define STACK_SIZE (32*1024)
#define GLOBAL_SIZE (32*1024)

#include <stack>
#include "InstructionList.h"


class VirtualMachine {
public:
    char stack[STACK_SIZE];
    char globals[GLOBAL_SIZE];
    char *stack_pt; // Stack Pointer
    char *stack_after; // first byte after stack; used for stack limit tests
    int n_globals;
    InstructionList IP;

    VirtualMachine();
    ~VirtualMachine();
    void run(std::list<Instruction> head);

    void* setup_heap(const int& size);

    /******************
    ** STACK METHODS **
    ******************/
    void push_d(const double& d);
    double pop_d();
    void push_a(void *a);
    void *pop_a();
    void push_i(const int& i);
    int pop_i();
    void push_c(const char& c);
    char pop_c();
};


#endif //SYNTACTICANALIZER_CPP_VIRTUALMACHINE_H
