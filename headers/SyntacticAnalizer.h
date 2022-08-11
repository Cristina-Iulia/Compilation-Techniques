//
// Created by Iulia on 03/04/2022.
//

#ifndef LA_SYNTACTICANALIZER_H
#define LA_SYNTACTICANALIZER_H
#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include "VirtualMachine.h"

class SyntacticAnalizer {
public:
    LexicalAnalyzer LA;
    SymbolTable ST;
    inline static VirtualMachine VM = VirtualMachine();
    std::shared_ptr<Token> startTk;
    std::shared_ptr<Token> currentTk;

    SyntacticAnalizer(LexicalAnalyzer lex);

    bool consume(int code);
    bool check_name(int code);

    /**
     * Expressions
     */
    bool exprPrimary();
    bool exprPostfix();
    bool exprUnary();
    bool exprCast();
    bool exprMul();
    bool exprAdd();
    bool exprRel();
    bool exprEq();
    bool exprAnd();
    bool exprOr();
    bool exprAssign();
    bool expr();

    /*************
    *Declarations*
    **************/

    bool unit();
    bool declStruct();
    bool declVar();
    bool typeBase();
    int arrayDecl();
    bool typeName(Type *rve);
    bool declFunc();
    bool funcArg();

    /*
     Statements
     */
    bool stm();
    bool stmCompound();

    /**
     * Now we start creating the rules
     * of the syntactic analyzer
     **/

    bool rule_WHILE();
    bool rule_IF();
    bool rule_FOR();
    bool rule_BREAK();
    bool rule_RETURN();
    bool rule_EXPR();

    /*******************
     * HELPER FUNCTIONS *
     * *****************
     **/

    bool expr_mul_helper();
    bool expr_add_helper();
    bool expr_rel_helper();
    bool expr_eq_helper();
    bool expr_and_helper();
    bool expr_or_helper();

    bool expr_assign_helper();

    /*****************
     * FOR SYMBOL TABLE
     * ****************
     */

    void add_arg();
    void set_var_type(Type t);
    void add_struct();
    void add_var();

    int get_typeBase(int code);
    void add_func(Type t);

    /*****************
     * FOR TYPE CHECKING
     * ****************
     */
    void unary_check(int code);
    void set_arg_type(Type type);
    void mul_check(RetVal& rv);
    void add_check(RetVal& rv);
    void rel_check(RetVal& rv);
    void eq_check(RetVal& rv);
    void and_check(RetVal& rv);
    void or_check(RetVal& rv);
    void assign_check(RetVal& rv);

    bool is_array_element();

    /*****************
     * PREDEFINED FUNCTIONS ADDERS
     * ****************/
    void add_predef_func();
    static void put_s();
    static void put_i();
    static void put_d();
    static void put_c();
    static void get_s();
    static void get_i();
    static void get_d();
    static void get_c();

};



#endif //LA_SYNTACTICANALIZER_H
