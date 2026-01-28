#include "Interpreter.h"

using namespace Interpreter;
using namespace Lexer;

int Interpreter::IP = 0; // // Instruction pointer
std::vector <std::string> Interpreter::stack; // For arithmetic operations (push, add, etc)

// Operation Set

std::vector<std::tuple<std::string, int>> Interpreter::operations = { 
	std::make_tuple("add",0), // regular add
	std::make_tuple("sub",1), // regular sub
	std::make_tuple("mul",2), // regular mul
	std::make_tuple("div",3), // regular div 
	std::make_tuple("pop",4), // regular pop
	std::make_tuple("push",5), // regular push
	std::make_tuple("out",6), // std::cout
	std::make_tuple("sadd",7), // stack add
	std::make_tuple("ssub",8), // stack sub
	std::make_tuple("smul",9), // stack mul
	std::make_tuple("sdiv",10), // stack div
};

/*

ProcessInstruction processes the current instruction set and determines if it corresponds to any function.
If it does then it'll recognize it by it's function id and do the corresponding response.

*/

void ProcessInstruction(std::vector<Token> Instructions) {

	// This assumes the values are always positive numbers, To be updated

	// Operation types 

	int OperationType = -1;
	std::vector<std::string> OperationStack;
	for (Token token : Instructions) {
		if (token.type == TokenType::IDENTIFIER) {
			if (OperationType == -1) {
				for (std::tuple OperationSet : operations) {
					std::string Operation = std::get<0>(OperationSet);
					int OperationID = std::get<1>(OperationSet);
					if (token.value == Operation) {
						OperationType = OperationID;
					}
				}
			}
			else {
				OperationStack.push_back(token.value);
			}
		}
		else if (token.type == TokenType::NUMBER) {
			int value = std::stoi(token.value);
			OperationStack.push_back(std::to_string(value));
		}
	}
	switch (OperationType) {
	case 0:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawoperation : OperationStack) {
			int operation = std::stoi(rawoperation);
			if (firstoperation) {
				operation_result = operation;
				firstoperation = 0;
			}
			else {
				operation_result += operation;
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 1:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawoperation : OperationStack) {
			int operation = std::stoi(rawoperation);
			if (firstoperation) {
				operation_result = operation;
				firstoperation = 0;
			}
			else {
				operation_result -= operation;
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 2:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawoperation : OperationStack) {
			int operation = std::stoi(rawoperation);
			if (firstoperation) {
				operation_result = operation;
				firstoperation = 0;
			}
			else {
				operation_result *= operation;
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 3:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawoperation : OperationStack) {
			int operation = std::stoi(rawoperation);
			if (firstoperation) {
				operation_result = operation;
				firstoperation = 0;
			}
			else {
				operation_result /= operation;
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 4:
	{
		std::erase(stack, stack[std::stoi(OperationStack.at(0))]);
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 5:
	{
		for (std::string push_value : OperationStack) {
			stack.push_back(push_value);
		}
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 6:
	{
		std::cout << stack[std::stoi(OperationStack.at(0))] << std::endl;
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 7:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawstackaddress : OperationStack) {
			int stackaddress = std::stoi(rawstackaddress);
			if (firstoperation) {
				operation_result = std::stoi(stack[stackaddress]);
				firstoperation = 0;
			}
			else {
				operation_result += std::stoi(stack[stackaddress]);
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 8:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawstackaddress : OperationStack) {
			int stackaddress = std::stoi(rawstackaddress);
			if (firstoperation) {
				operation_result = std::stoi(stack[stackaddress]);
				firstoperation = 0;
			}
			else {
				operation_result -= std::stoi(stack[stackaddress]);
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 9:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawstackaddress : OperationStack) {
			int stackaddress = std::stoi(rawstackaddress);
			if (firstoperation) {
				operation_result = std::stoi(stack[stackaddress]);
				firstoperation = 0;
			}
			else {
				operation_result *= std::stoi(stack[stackaddress]);
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 10:
	{
		bool firstoperation = 1;
		int operation_result = 0;
		for (std::string rawstackaddress : OperationStack) {
			int stackaddress = std::stoi(rawstackaddress);
			if (firstoperation) {
				operation_result = std::stoi(stack[stackaddress]);
				firstoperation = 0;
			}
			else {
				operation_result /= std::stoi(stack[stackaddress]);
			}
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	}
}

// Interpret function which leads to ProcessInstruction for subsequent processing

void Interpreter::Interpret(std::vector<std::string> instructions) {
	for (IP = 0; IP < instructions.size(); IP++) {
		ProcessInstruction(Tokenize(instructions[IP]));
	}
}