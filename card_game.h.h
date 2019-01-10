/*
 *
 *      Author: Samed Kahyaoglu / Urtuba
 *
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_
#define LANGUAGE_DEPTH 5 //defines how many functions can be worked as nested
#include<string>

struct Statement
{
    std::string type;
    std::string arg1;
    std::string arg2;
};

typedef unsigned AddressValue;
typedef int ScalarValue;

template<typename T>
struct Stack
{
    T variables[LANGUAGE_DEPTH][5];
    //LANGUAGE_DEPTH is capacity of working with nested functions.
    int degree;
    //degree,for main degree=0, main calls a function: 1, the function calls another:2
    //each function works with different level of data, until return statement allows it to copy its value to parent function.
    Statement* const top; // makes possible to return first statement whether where you are at.
    AddressValue degreeCalls[LANGUAGE_DEPTH];
    //holds addresses of functions, there can be nested functions so they uses their data
    //I had to store addresses of their caller, program can be compiled for more complex codes via changing LANGUAGE_DEPTH.
    AddressValue currentAddress;
    bool isDone;
};

AddressValue executeStatement( const Statement & statement, const AddressValue currentAddress, ScalarValue variables [5], Stack<ScalarValue> & callStack, const AddressValue addressOfCalleeIfCall, bool & isDone );

#endif /* RUNTIME_H_ */
