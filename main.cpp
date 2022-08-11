#include <iostream>
#include "headers/Token.h"
#include "headers/LexicalAnalyzer.h"
#include "headers/SyntacticAnalizer.h"
#include <vector>

std::vector<void *> funcs;

int main() {

//    char files[10][10] = {"0.c","1.c","2.c","3.c", "4.c", "5.c","6.c","7.c","8.c","9.c" };

        FILE *input = fopen("6.c", "r");

        if (!input) {
            std::cout << "Error at file opening\n";
            exit(1);
        }

        char *text;
        fseek(input, 0, SEEK_END);
        long int size = ftell(input);
        fseek(input, 0, SEEK_SET);


        text = (char *) malloc(sizeof(char) * size + 10);
        fread(text, size, sizeof(char), input);
        text[size] = EOF;
        text[size + 1] = '\0';

        fclose(input);

        LexicalAnalyzer LA = LexicalAnalyzer(text);
        LA.get_all_tokens();
        SyntacticAnalizer SA = SyntacticAnalizer(LA);
//        int result = SA.unit();

//        SA.ST.print_symbT();


        funcs.push_back(reinterpret_cast<void *>(&SyntacticAnalizer::put_i));

        void *v = (void*)SyntacticAnalizer::VM.setup_heap(sizeof(int));

        SyntacticAnalizer::VM.IP.add_instr_A(O_PUSHCT_A, v);
        SyntacticAnalizer::VM.IP.add_instr_I(O_PUSHCT_I,3);
        SyntacticAnalizer::VM.IP.add_instr_I(O_STORE, sizeof(int));
        SyntacticAnalizer::VM.IP.add_instr_II(O_LOAD, sizeof(int), 2);
        SyntacticAnalizer::VM.IP.add_instr_I(O_PUSHCT_I,3);

        SyntacticAnalizer::VM.IP.add_instr_I(O_PUSHCT_I,8);
        SyntacticAnalizer::VM.IP.add_instr_A(O_CALLEXT, (void *)funcs[0]);
        SyntacticAnalizer::VM.IP.add_instr_A(O_PUSHCT_A, v);
        SyntacticAnalizer::VM.IP.add_instr_I(O_PUSHCT_I,1);
        SyntacticAnalizer::VM.IP.add_instr(O_SUB_I);
        SyntacticAnalizer::VM.IP.add_instr_I(O_STORE, sizeof(int));
        SyntacticAnalizer::VM.IP.add_instr_A(O_PUSHCT_A, v);
        SyntacticAnalizer::VM.IP.add_instr_II(O_LOAD, sizeof(int), 5);
        SyntacticAnalizer::VM.IP.add_instr_I(O_PUSHCT_I,8);
        SyntacticAnalizer::VM.IP.add_instr_I(O_PUSHCT_I,4);
        SyntacticAnalizer::VM.IP.add_instr(O_GREATER_I);
        SyntacticAnalizer::VM.IP.add_instr_I(O_JT_I, 7);
        SyntacticAnalizer::VM.IP.add_instr(O_HALT);
        SyntacticAnalizer::VM.run(SyntacticAnalizer::VM.IP.head);


        free(text);

    return 0;
}
