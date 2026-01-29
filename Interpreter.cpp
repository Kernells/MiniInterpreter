#include "Interpreter.h"

using namespace Interpreter;
using namespace Lexer;

int Interpreter::IP = 0; // // Instruction pointer
std::vector <std::string> Interpreter::stack; // For arithmetic operations (push, add, etc)

// Operation Set

std::vector<Interpreter::Operation> Interpreter::operations = { 

Operation{"add", 0},   // regular add
Operation{"sub", 1},   // regular sub
Operation{"mul", 2},   // regular mul
Operation{"div", 3},   // regular div
Operation{"pop", 4},   // regular pop
Operation{"push", 5},  // regular push
Operation{"out", 6},   // std::cout
Operation{"sadd", 7},  // stack add
Operation{"ssub", 8},  // stack sub
Operation{"smul", 9},  // stack mul
Operation{"sdiv", 10},  // stack div
Operation{"swap", 11},  // swap two stack values
Operation{"dup", 12}  // duplicate a stack value and push it to the top

};


// Holy protector

bool ProtectAddress(int Address, std::vector<std::string> OperationStack) {
	if (!((Address <= stack.size() - 1) && !stack.empty())) {
	Reporter::ThrowMessage("Stack address '" + std::to_string(Address) + "' doesn't exist", 2);

	std::vector<std::string>().swap(OperationStack);
	OperationStack.clear();
	return true;
	}
	return false;
}

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
				for (Operation OperationSet : operations) {
					std::string Operation = OperationSet.opcode;
					int OperationID = OperationSet.opid;
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
		if (ProtectAddress(std::stoi(OperationStack.at(0)), OperationStack)) return;

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
		if (ProtectAddress(std::stoi(OperationStack.at(0)), OperationStack)) return;

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

			if (ProtectAddress(stackaddress, OperationStack)) return;

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

			if (ProtectAddress(stackaddress, OperationStack)) return;

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

			if (ProtectAddress(stackaddress, OperationStack)) return;

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

			if (ProtectAddress(stackaddress, OperationStack)) return;

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
	case 11:
	{

		int ToSwap = std::stoi(OperationStack[0]);
		int SwapAddress = std::stoi(OperationStack[1]);

		if (ProtectAddress(ToSwap, OperationStack)) return;
		if (ProtectAddress(SwapAddress, OperationStack)) return;

		std::string tmpval = stack[ToSwap];

		stack[ToSwap] = stack[SwapAddress];
		stack[SwapAddress] = tmpval;

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 12:
	{
		
		if (ProtectAddress(std::stoi(OperationStack.at(0)), OperationStack)) return;

		stack.push_back(stack[std::stoi(OperationStack[0])]);

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	}
}

// Interpret function which leads to ProcessInstruction for subsequent processing

void Interpreter::Interpret(std::vector<std::string> instructions) {
	for (IP = 0; IP < instructions.size(); IP++) {
		try {
			ProcessInstruction(Tokenize(instructions[IP]));
		}
		catch (const std::exception& e) {
			Reporter::ThrowMessage(e.what(), 2);
		}
	}
}