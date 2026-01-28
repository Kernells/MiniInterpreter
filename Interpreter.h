#pragma once
#include <vector>
#include "Lexer.h"

namespace Interpreter
{
	// Operation struct (To be later implemented)

	struct Operation {
		std::string name;
		int opcode;
	};

	extern int IP; // Instruction pointer
	extern std::vector <std::string> stack; // For arithmetic operations (push, add, etc)
	extern std::vector<std::tuple<std::string, int>> operations; // Operation set

	// Interpret function which leads to ProcessInstruction for subsequent processing

	void Interpret(std::vector<std::string> instructions); 

};

