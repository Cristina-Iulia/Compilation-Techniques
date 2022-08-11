//
// Created by Iulia on 22/05/2022.
//

#include "../headers/VirtualMachine.h"
#include <iostream>
#include <vector>

VirtualMachine::~VirtualMachine() {
    delete stack_pt;
    delete stack_after;
}

VirtualMachine::VirtualMachine()
    : stack_pt(nullptr),
      stack_after(nullptr)
{}

void VirtualMachine::push_d(const double &d) {
    if ( stack_pt + sizeof(double) > stack_after ) {
        std::cout<<"PUSH_D OUT OF STACK!"<<std::endl;
        exit(101);
    }
    *(double *)stack_pt = d;
    stack_pt += sizeof(double);
}

double VirtualMachine::pop_d() {
    if ( stack_after - sizeof(double) < stack_pt ) {
        std::cout<<"POP_D NOT ENOUGH BYTES!"<<std::endl;
        exit(102);
    }
    stack_pt -= sizeof(double);
    return *(double *)stack_pt;
}

void VirtualMachine::push_a(void *a) {
    if ( stack_pt + sizeof(void *) > stack_after ) {
        std::cout<<"PUSH_A OUT OF STACK!"<<std::endl;
        exit(103);
    }
    *(void **)stack_pt = a;
    stack_pt += sizeof(void *);
}

void *VirtualMachine::pop_a() {
    if ( stack_after - sizeof(void *) < stack_pt ) {
        std::cout<<"POP_A NOT ENOUGH BYTES!"<<std::endl;
        exit(104);
    }
    stack_pt -= sizeof(void *);
    return *(void **)stack_pt;
}

void VirtualMachine::push_i(const int& i) {
    if ( stack_pt + sizeof(int) > stack_after ) {
        std::cout<<"PUSH_I OUT OF STACK!"<<std::endl;
        exit(105);
    }
    *(int *)stack_pt = i;
    stack_pt += sizeof(int);
}

int VirtualMachine::pop_i() {
    if ( stack_after - sizeof(int) < stack_pt ) {
        std::cout<<"POP_I NOT ENOUGH BYTES!"<<std::endl;
        exit(106);
    }
    stack_pt -= sizeof(int);
    return *(int *)stack_pt;
}

void VirtualMachine::push_c(const char& c) {
    if ( stack_pt + sizeof(char) > stack_after ) {
        std::cout<<"PUSH_C OUT OF STACK!"<<std::endl;
        exit(107);
    }
    *(char *)stack_pt = c;
    stack_pt += sizeof(char);
}

char VirtualMachine::pop_c() {
    if ( stack_after - sizeof(char) < stack_pt ) {
        std::cout<<"POP_C NOT ENOUGH BYTES!"<<std::endl;
        exit(108);
    }
    stack_pt -= sizeof(char);
    return *(char *)stack_pt;
}

void *VirtualMachine::setup_heap(const int &size) {
    if ( n_globals + size > GLOBAL_SIZE ) {
        std::cout<<"Not enough memory on HEAP!"<<std::endl;
        exit(300);
    }
    void * p = globals + n_globals;
    n_globals +=size;
    return p;
}

void VirtualMachine::run(std::list<Instruction> head) {

    long int iVal1,iVal2;
    double dVal1,dVal2;
    void *aVal1, *aVal2;
    char c1, c2;
    char *FP=0,*old_stack_pt;
    stack_pt = stack;
    stack_after = stack+STACK_SIZE;
    auto current  = head.begin();
    while(1) {
        switch (current->op_code) {
            case O_ADD_C:
                std::cout<<"O_ADD_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                std::cout<<c1<<"+"<<c2<<std::endl;
                push_c(c1 + c2);
                current++;
                break;
            case O_ADD_D:
                std::cout<<"O_ADD_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                std::cout<<dVal1<<"+"<<dVal2<<std::endl;
                push_d(dVal2+dVal1);
                current++;
                break;
            case O_ADD_I:
                std::cout<<"O_ADD_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                std::cout<<iVal1<<"+"<<iVal2<<std::endl;
                push_i(iVal2+iVal1);
                current++;
                break;
            case O_AND_A:
                std::cout<<"O_AND_A"<<std::endl;
                aVal1 = pop_a();
                aVal2 = pop_a();
                push_i(aVal2 && aVal1);
                current++;
                break;
            case O_AND_C:
                std::cout<<"O_AND_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 && c2);
                current++;
                break;
            case O_AND_D:
                std::cout<<"O_AND_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 && dVal2);
                current++;
                break;
            case O_AND_I:
                std::cout<<"O_AND_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 && iVal2);
                current++;
                break;
            case O_CALL:
                std::cout<<"O_CALL"<<std::endl;
                aVal1=std::get<void *>(current->args[0]);
                std::cout<<"Call : "<<aVal1;
//                push_a(reinterpret_cast<void *>();
//                current = *(Instruction *)aVal1;
                break;
            case O_CALLEXT:
                std::cout<<"O_CALLEXT"<<std::endl;
                aVal1=std::get<void *>(current->args[0]);
                std::cout<<"Call : "<<aVal1<<std::endl;
                (*(void(*)())aVal1)();
                current++;
                break;
            case O_CAST_C_D:
                std::cout<<"O_CAST_C_D"<<std::endl;
                c1 = pop_c();
                push_d(c1);
                current++;
                break;
            case O_CAST_C_I:
                std::cout<<"O_CAST_C_I"<<std::endl;
                c1 = pop_c();
                push_i(c1);
                current++;
                break;
            case O_CAST_D_C:
                std::cout<<"O_CAST_D_C"<<std::endl;
                dVal1 = pop_d();
                push_c(dVal1);
                current++;
                break;
            case O_CAST_D_I:
                std::cout<<"O_CAST_D_I"<<std::endl;
                dVal1 = pop_d();
                push_i(dVal1);
                current++;
                break;
            case O_CAST_I_C:
                std::cout<<"O_CAST_I_C"<<std::endl;
                iVal1 = pop_i();
                push_c(iVal1);
                current++;
                break;
            case O_CAST_I_D:
                std::cout<<"O_CAST_I_D"<<std::endl;
                iVal1 = pop_i();
                push_d(iVal1);
                current++;
                break;
            case O_DIV_C:
                std::cout<<"O_DIV_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_c(c1/c2);
                current++;
                break;
            case O_DIV_D:
                std::cout<<"O_DIV_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_d(dVal1 / dVal2);
                current++;
                break;
            case O_DIV_I:
                std::cout<<"O_DIV_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 / iVal2);
                current++;
                break;
            case O_ENTER:
                std::cout<<"O_ENTER"<<std::endl;
//                iVal1 = pop_i();
//                iVal2 = pop_i();
//                push_i(iVal1 / iVal2);
                current++;
                break;
            case O_EQ_A:
                std::cout<<"O_EQ_A"<<std::endl;
                aVal1 = pop_a();
                aVal2 = pop_a();
                push_i(aVal1 == aVal2);
                current++;
                break;
            case O_EQ_C:
                std::cout<<"O_EQ_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 == c2);
                current++;
                break;
            case O_EQ_D:
                std::cout<<"O_EQ_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 == dVal2);
                current++;
                break;
            case O_EQ_I:
                std::cout<<"O_EQ_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 == iVal2);
                current++;
                break;
            case O_GREATER_C:
                std::cout<<"O_GREATER_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 > c2);
                current++;
                break;
            case O_GREATER_D:
                std::cout<<"O_GREATER_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 > dVal2);
                current++;
                break;
            case O_GREATER_I:
                std::cout<<"O_GREATER_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 > iVal2);
                current++;
                break;
            case O_GREATEREQ_C:
                std::cout<<"O_GREATEREQ_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 >= c2);
                current++;
                break;
            case O_GREATEREQ_D:
                std::cout<<"O_GREATEREQ_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 >= dVal2);
                current++;
                break;
            case O_GREATEREQ_I:
                std::cout<<"O_GREATEREQ_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 >= iVal2);
                current++;
                break;
            case O_HALT:
                std::cout<<"O_HALT"<<std::endl;
                std::cout<<"HALT!"<<std::endl;
                exit(900);
            case O_JF_I:
                std::cout<<"O_JF_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = std::get<long>(current->args[0]);
                current = !iVal1 ? std::next(head.begin(), iVal2) : std::next(current, 1);
                break;
            case O_JF_D:
                std::cout<<"O_JF_D"<<std::endl;
                dVal1 = pop_d();
                iVal2 = std::get<long>(current->args[0]);
                current = !dVal1 ? std::next(head.begin(), iVal2) : std::next(current, 1);
                break;
            case O_JMP:
                std::cout<<"O_JMP"<<std::endl;
                iVal2 = std::get<long>(current->args[0]);
                current = std::next(head.begin(), iVal2);
                break;
            case O_JT_I:
                std::cout<<"O_JT_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = std::get<long>(current->args[0]);
                current = iVal1 ? std::next(head.begin(), iVal2) : std::next(current, 1);
                break;
            case O_JT_D:
                std::cout<<"O_JT_D"<<std::endl;
                dVal1 = pop_d();
                iVal2 = std::get<long>(current->args[0]);
                current = dVal1 ? std::next(head.begin(), iVal2) : std::next(current, 1);
                break;
            case O_LESS_C:
                std::cout<<"O_LESS_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 < c2);
                current++;
                break;
            case O_LESS_D:
                std::cout<<"O_LESS_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 < dVal2);
                current++;
                break;
            case O_LESS_I:
                std::cout<<"O_LESS_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 < iVal2);
                current++;
                break;
            case O_LESSEQ_C:
                std::cout<<"O_LESSEQ_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 <= c2);
                current++;
                break;
            case O_LESSEQ_D:
                std::cout<<"O_LESSEQ_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 <= dVal2);
                current++;
                break;
            case O_LESSEQ_I:
                std::cout<<"O_LESSEQ_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 <= iVal2);
                current++;
                break;
            case O_MUL_C:
                std::cout<<"O_MUL_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 * c2);
                current++;
                break;
            case O_MUL_D:
                std::cout<<"O_MUL_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_d(dVal1 * dVal2);
                current++;
                break;
            case O_MUL_I:
                std::cout<<"O_MUL_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 * iVal2);
                current++;
                break;
            case O_NEG_C:
                std::cout<<"O_NEG_C"<<std::endl;
                c1 = pop_c();
                push_i(-c1);
                current++;
                break;
            case O_NEG_D:
                std::cout<<"O_NEG_D"<<std::endl;
                dVal1 = pop_d();
                push_d(-dVal1);
                current++;
                break;
            case O_NEG_I:
                std::cout<<"O_NEG_I"<<std::endl;
                iVal1 = pop_i();
                push_i(-iVal1);
                current++;
                break;
            case O_NOP:
                std::cout<<"NOP!"<<std::endl;
                current++;
            case O_NOT_A:
                std::cout<<"O_NOT_A"<<std::endl;
                aVal1 = pop_a();
                push_i(!aVal1);
                current++;
                break;
            case O_NOT_C:
                std::cout<<"O_NOT_C"<<std::endl;
                c1 = pop_c();
                push_i(!c1);
                current++;
                break;
            case O_NOT_D:
                std::cout<<"O_NOT_D"<<std::endl;
                dVal1 = pop_d();
                push_d(!dVal1);
                current++;
                break;
            case O_NOT_I:
                std::cout<<"O_NOT_I"<<std::endl;
                iVal1 = pop_i();
                push_i(!iVal1);
                current++;
                break;
            case O_NOTEQ_A:
                std::cout<<"O_NOTEQ_A"<<std::endl;
                aVal1 = pop_a();
                aVal2 = pop_a();
                push_i(aVal1 != aVal2);
                current++;
                break;
            case O_NOTEQ_C:
                std::cout<<"O_NOTEQ_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 != c2);
                current++;
                break;
            case O_NOTEQ_D:
                std::cout<<"O_NOTEQ_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 != dVal2);
                current++;
                break;
            case O_NOTEQ_I:
                std::cout<<"O_NOTEQ_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 != iVal2);
                current++;
                break;
            case O_OR_A:
                std::cout<<"O_OR_A"<<std::endl;
                aVal1 = pop_a();
                aVal2 = pop_a();
                push_i(aVal1 || aVal2);
                current++;
                break;
            case O_OR_C:
                std::cout<<"O_OR_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 || c2);
                current++;
                break;
            case O_OR_D:
                std::cout<<"O_OR_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_i(dVal1 || dVal2);
                current++;
                break;
            case O_OR_I:
                std::cout<<"O_OR_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 || iVal2);
                current++;
                break;
            case O_PUSHCT_A:
                std::cout<<"O_PUSHCT_A"<<std::endl;
                aVal1 = std::get<void *>(current->args[0]);
                push_a(aVal1);
                current++;
                break;
            case O_PUSHCT_C:
                std::cout<<"O_PUSHCT_C"<<std::endl;
                c1 = std::get<long>(current->args[0]);
                std::cout<<"PUSHCT_C: "<<c1<<std::endl;
                push_c(c1);
                current++;
                break;
            case O_PUSHCT_D:
                std::cout<<"O_PUSHCT_D"<<std::endl;
                dVal1 = std::get<double>(current->args[0]);
                std::cout<<"PUSHCT_D: "<<dVal1<<std::endl;
                push_d(dVal1);
                current++;
                break;
            case O_PUSHCT_I:
                iVal1 = std::get<long>(current->args[0]);
                std::cout<<"PUSHCT_I: "<<iVal1<<std::endl;
                push_i(iVal1);
                current++;
                break;
            case O_STORE:
                try{
                    iVal1 = std::get<long>(current->args[0]);
                    std::cout<<"STORE: "<<iVal1<<std::endl;
                    push_i(iVal1);
                }catch (const std::exception &ex1){
                    try {
                        dVal1 = std::get<double>(current->args[0]);
                        std::cout<<"STORE: "<<dVal1<<std::endl;
                        push_d(dVal1);
                    }catch (const std::exception &ex2){

                    }
                }
                current++;
                break;
            case O_SUB_C:
                std::cout<<"O_SUB_C"<<std::endl;
                c1 = pop_c();
                c2 = pop_c();
                push_i(c1 - c2);
                current++;
                break;
            case O_SUB_D:
                std::cout<<"O_SUB_D"<<std::endl;
                dVal1 = pop_d();
                dVal2 = pop_d();
                push_d(dVal1 - dVal2);
                current++;
                break;
            case O_SUB_I:
                std::cout<<"O_SUB_I"<<std::endl;
                iVal1 = pop_i();
                iVal2 = pop_i();
                push_i(iVal1 - iVal2);
                current++;
                break;
            case O_LOAD:
                std::cout<<"O_LOAD"<<std::endl;
                iVal1 = std::get<long>(current->args[0]);
                if(iVal1 == sizeof(int)){
                    iVal2 = std::get<long>(current->args[1]);
                    push_i(iVal2);
                }
                else{
                    dVal1 = std::get<double>(current->args[0]);
                    if(dVal1 == sizeof(double)){
                        dVal2 = std::get<double>(current->args[1]);
                        push_d(dVal2);
                    }
                }
                current++;
                break;
            default:
                std::cout << "Invalid code" << std::endl;
                exit(500);
        }
    }
}
