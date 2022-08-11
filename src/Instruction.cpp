//
// Created by Iulia on 22/05/2022.
//

#include "../headers/Instruction.h"

Instruction::Instruction()
        : op_code(0)
{}

void Instruction::init_args(std::variant<long, double, void *> arr) {

    try {
        args.push_back(std::get<long> (arr));
    }
    catch(const std::exception &e) {
        try {
            args.push_back(std::get<double> (arr));
        }
        catch(const std::exception &e) {
            try {
                args.push_back(std::get<void *> (arr));
            }
            catch(const std::exception &e) {
                std::cout<< "No match with defined arg type!"<<std::endl;
                exit(200);
            }
        }
    }


}
