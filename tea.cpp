/*
 *AUTHOR: Samed Kahyaoglu
 *GITHUB: urtuba
 */

#define MAX_STATEMENTS 100
#include "runtime.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

AddressValue executeStatement( const Statement & statement,
			       const AddressValue currentAddress,
			       ScalarValue variables [5],
			       Stack<ScalarValue> & callStack,
			       const AddressValue addressOfCalleeIfCall,
			       bool & isDone )
{
    (void) variables;
    (void) callStack;
    (void) isDone;
    (void) addressOfCalleeIfCall;

		//entry point
		//cout << variables[0] << " " << variables[1] << " " << variables[2] << " " << variables[3] << " " << variables[4] << " "<< endl;

    cout << "Executing " << statement.type << " at line " << currentAddress /*<< " degree " << callStack.degree*/ << endl;


		if (statement.type.compare("call") == 0)
		{
			//this part finds the address of calling function by its name
			AddressValue a = 0;
				while(true)
				{
					if (((callStack.top + a) -> type.compare("function") == 0) && ((callStack.top + a) -> arg1.compare(statement.arg1) == 0)) break;
					a++;
				}
			//then degree increases, it means a b c d e variables are re-arranged for this function
			callStack.degree ++;
			//one variable will be transferred to new variables due to arg2
			if (statement.arg2.compare("a")==0) callStack.variables[callStack.degree][0] = variables[0];
			else callStack.variables[callStack.degree][0] = 0;
			if (statement.arg2.compare("b")==0) callStack.variables[callStack.degree][1] = variables[1];
			else callStack.variables[callStack.degree][1] = 0;
			if (statement.arg2.compare("c")==0) callStack.variables[callStack.degree][2] = variables[2];
			else callStack.variables[callStack.degree][2] = 0;
			if (statement.arg2.compare("d")==0) callStack.variables[callStack.degree][3] = variables[3];
			else callStack.variables[callStack.degree][3] = 0;
			if (statement.arg2.compare("e")==0) callStack.variables[callStack.degree][4] = variables[4];
			else callStack.variables[callStack.degree][4] = 0;
			//address before passing new function is recorded to array
			callStack.degreeCalls[callStack.degree] = currentAddress;

			return a + 1;
		}

		if ((addressOfCalleeIfCall != 0) && (statement.type.compare("return") == 0))
		{
			//if function is not main function, return statement goes next statement in parent function
			//it saves one of its temporary variables into general variables before
			if (statement.arg1.compare("a") == 0) callStack.variables[callStack.degree - 1][0] = variables[0];
			if (statement.arg1.compare("b") == 0) callStack.variables[callStack.degree - 1][1] = variables[1];
			if (statement.arg1.compare("c") == 0) callStack.variables[callStack.degree - 1][2] = variables[2];
			if (statement.arg1.compare("d") == 0) callStack.variables[callStack.degree - 1][3] = variables[3];
			if (statement.arg1.compare("e") == 0) callStack.variables[callStack.degree - 1][4] = variables[4];

			callStack.degree --;
			return addressOfCalleeIfCall + 1;
		}

		if ((addressOfCalleeIfCall == 0) && (statement.type.compare("return") == 0))
		{
			//final situation, if function is not called it is main(first condition) and if statement is return, program finishes its work.
			if (statement.arg1.compare("a") == 0) cout << variables[0];
			if (statement.arg1.compare("b") == 0) cout << variables[1];
			if (statement.arg1.compare("c") == 0) cout << variables[2];
			if (statement.arg1.compare("d") == 0) cout << variables[3];
			if (statement.arg1.compare("e") == 0) cout << variables[4];
			cout << endl;
			callStack.isDone = true;
			return 0;
		}

		if ((statement.type.size() == 3)) //mul,div,inc and dec are all consists of 3 chars.
		{
			// finding value of arg2, if it is value itself; typecasting to ScalarValue.
			ScalarValue arg2;
			if(statement.arg2.compare("a") == 0) arg2 = variables[0];
			else if(statement.arg2.compare("b") == 0) arg2 = variables[1];
			else if(statement.arg2.compare("c") == 0) arg2 = variables[2];
			else if(statement.arg2.compare("d") == 0) arg2 = variables[3];
			else if(statement.arg2.compare("e") == 0) arg2 = variables[4];
			else arg2 = atoi(statement.arg2.c_str());

			//operations with order: inc, dec, mul, div.
			if (statement.type.compare("inc") == 0) {
				if (statement.arg1.compare("a") == 0) variables[0] += arg2;
				if (statement.arg1.compare("b") == 0) variables[1] += arg2;
				if (statement.arg1.compare("c") == 0) variables[2] += arg2;
				if (statement.arg1.compare("d") == 0) variables[3] += arg2;
				if (statement.arg1.compare("e") == 0) variables[4] += arg2;
			}

			if (statement.type.compare("dec") == 0) {
				if (statement.arg1.compare("a") == 0) variables[0] -= arg2;
				if (statement.arg1.compare("b") == 0) variables[1] -= arg2;
				if (statement.arg1.compare("c") == 0) variables[2] -= arg2;
				if (statement.arg1.compare("d") == 0) variables[3] -= arg2;
				if (statement.arg1.compare("e") == 0) variables[4] -= arg2;
			}

			if (statement.type.compare("mul") == 0) {
				if (statement.arg1.compare("a") == 0) variables[0] *= arg2;
				if (statement.arg1.compare("b") == 0) variables[1] *= arg2;
				if (statement.arg1.compare("c") == 0) variables[2] *= arg2;
				if (statement.arg1.compare("d") == 0) variables[3] *= arg2;
				if (statement.arg1.compare("e") == 0) variables[4] *= arg2;
			}

			if (statement.type.compare("div") == 0) {
				if (statement.arg1.compare("a") == 0) variables[0] /= arg2;
				if (statement.arg1.compare("b") == 0) variables[1] /= arg2;
				if (statement.arg1.compare("c") == 0) variables[2] /= arg2;
				if (statement.arg1.compare("d") == 0) variables[3] /= arg2;
				if (statement.arg1.compare("e") == 0) variables[4] /= arg2;
			}
		}
		//except function calls and returns each statement returns next statement
    return currentAddress + 1;
}

int main(int argc, char const *argv[]) {

	(void) argc;
	Statement statements[MAX_STATEMENTS];
	Stack<ScalarValue> callStack =
	{
		{{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}},
		0, statements, {0,0,0,0,0}, 0, false
	};
	ifstream myFile(argv[1]);

	int x = 0;
	string buffer;
	while (myFile >> buffer) { //this while loop transfers data from file to statements array
		statements[x].type = buffer;
		if ((buffer.compare("function") == 0) || (buffer.compare("return") == 0))
		{//this functions has 1 arg so I should skip arg2 for them.
			myFile >> buffer;
			statements[x].arg1 = buffer;
			statements[x].arg2 = "";
		} else {
			myFile >> buffer;
			statements[x].arg1 = buffer;
			myFile >> buffer;
			statements[x].arg2 = buffer;
		}
		x++;
	}
	myFile.close();


	int k = 0; //k detects the address value of main function
	while (true) {
		k++;
		if (statements[k-1].arg1.compare("main") == 0) break; //when i find main function, I can start with it's next statement. so k is 1 after main.
	}

	while (!callStack.isDone)
	{
		//I used callStack for most of data because I can reach and change call stack parts in every function (because it is passed by reference)
		//callStack degreeCalls gives me chance to follow nested function connections and their return addressess
		//cStack.variables[degree] gives each function its variables as a matrix row
		k = executeStatement(statements[k], k, callStack.variables[callStack.degree], callStack, callStack.degreeCalls[callStack.degree], callStack.isDone);
	}

	return 0;
}
