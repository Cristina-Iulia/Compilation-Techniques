cmake_minimum_required(VERSION 3.16.3)
project(LA)

set(CMAKE_CXX_STANDARD 17)

add_executable(LA main.cpp src/Token.cpp src/LexicalAnalyzer.cpp src/SyntacticAnalizer.cpp src/Symbol.cpp src/SymbolTable.cpp src/Type.cpp src/VirtualMachine.cpp src/Instruction.cpp
        src/InstructionList.cpp)