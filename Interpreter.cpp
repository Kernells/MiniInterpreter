#include "Interpreter.h"

using namespace Interpreter;
using namespace Lexer;

int Interpreter::IP = 0; // // Instruction pointer
std::vector <std::string> Interpreter::stack; // For arithmetic operations (push, add, etc)

bool SkipNextOp = 0;

bool PreReturnToIP, ReturnToIP = 0;
int PrevIP = 0;

// Operation Set

std::vector<Interpreter::Operation> Interpreter::operations = { 

Operation{"add", 0},   // regular add
Operation{"sub", 1},   // regular sub
Operation{"mul", 2},   // regular mul
Operation{"div", 3},   // regular div
Operation{"pop", 4},   // regular pop
Operation{"push", 5},  // regular push
Operation{"sprint", 6},   // stack print
Operation{"sadd", 7},  // stack add
Operation{"ssub", 8},  // stack sub
Operation{"smul", 9},  // stack mul
Operation{"sdiv", 10},  // stack div
Operation{"swap", 11},  // swap two stack values
Operation{"dup", 12},  // duplicate a stack value and push it to the top
Operation{"jmp", 13},  // goes to the selected address
Operation{"eq", 14},  // equals logical op
Operation{"neq", 15},  // reverse equals logical op
Operation{"lt", 16},  // lower than
Operation{"gt", 17},  // greater than
Operation{"lte", 18},  // lower than or equals
Operation{"gte", 19},  // greater than or equals
Operation{"ift", 20},  // if true, executes next action
Operation{"iff", 21},  // if false, executes next action
Operation{"print",22}, // print
Operation{"invoke",23}, // invokes a single instruction on the instructions
Operation{"neg",24} // turns the value on the stack to negative

};


// Holy protector

bool ProtectAddress(int Address, std::vector<std::string> OperationStack) {
	if (!((Address <= stack.size() - 1) && !stack.empty())) {
	Reporter::ThrowException(0, std::to_string(Address));
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
	bool ValidOperation = 0;

	std::vector<std::string> OperationStack;
	for (Token token : Instructions) {
		if (token.type == TokenType::IDENTIFIER) {
			if (OperationType == -1) {
				for (Operation OperationSet : operations) {
					std::string Operation = OperationSet.opcode;
					int OperationID = OperationSet.opid;
					if (token.value == Operation) {
						OperationType = OperationID;
						ValidOperation = 1;
					}
				}
				if (!ValidOperation) {
					Reporter::ThrowMessage("Invalid operation '" + token.value + "'", 2);
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
	case 13: 
	{
		IP = std::stoi(OperationStack[0]) - 1;

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 14:
	{

		int Address1 = std::stoi(OperationStack[0]);
		int Address2 = std::stoi(OperationStack[1]);

		if (ProtectAddress(Address1, OperationStack)) return;
		if (ProtectAddress(Address2, OperationStack)) return;

		stack.push_back(std::to_string(stack[Address1] == stack[Address2]));

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 15:
	{

		int Address1 = std::stoi(OperationStack[0]);
		int Address2 = std::stoi(OperationStack[1]);

		if (ProtectAddress(Address1, OperationStack)) return;
		if (ProtectAddress(Address2, OperationStack)) return;

		stack.push_back(std::to_string(!(stack[Address1] == stack[Address2])));

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 16:
	{

		int Address1 = std::stoi(OperationStack[0]);
		int Address2 = std::stoi(OperationStack[1]);

		if (ProtectAddress(Address1, OperationStack)) return;
		if (ProtectAddress(Address2, OperationStack)) return;

		stack.push_back(std::to_string(std::stoi(stack[Address1]) < std::stoi(stack[Address2])));

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 17:
	{

		int Address1 = std::stoi(OperationStack[0]);
		int Address2 = std::stoi(OperationStack[1]);

		if (ProtectAddress(Address1, OperationStack)) return;
		if (ProtectAddress(Address2, OperationStack)) return;

		stack.push_back(std::to_string(std::stoi(stack[Address1]) > std::stoi(stack[Address2])));

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 18:
	{

		int Address1 = std::stoi(OperationStack[0]);
		int Address2 = std::stoi(OperationStack[1]);

		if (ProtectAddress(Address1, OperationStack)) return;
		if (ProtectAddress(Address2, OperationStack)) return;

		stack.push_back(std::to_string(std::stoi(stack[Address1]) <= std::stoi(stack[Address2])));

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 19:
	{

		int Address1 = std::stoi(OperationStack[0]);
		int Address2 = std::stoi(OperationStack[1]);

		if (ProtectAddress(Address1, OperationStack)) return;
		if (ProtectAddress(Address2, OperationStack)) return;

		stack.push_back(std::to_string(std::stoi(stack[Address1]) >= std::stoi(stack[Address2])));

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 20:
	{

		int Address = std::stoi(OperationStack[0]);

		if (ProtectAddress(Address, OperationStack)) return;

		if (!std::stoi(stack[Address])) SkipNextOp = 1;

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 21:
	{

		int Address = std::stoi(OperationStack[0]);

		if (ProtectAddress(Address, OperationStack)) return;

		if (std::stoi(stack[Address])) SkipNextOp = 1;

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 22:
	{
		for (std::string Output : OperationStack) {
			std::cout << Output << std::endl;
		}

		std::vector<std::string>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 23:
	{
        PreReturnToIP = 1;
		PrevIP = IP;
		IP = std::stoi(OperationStack[0]) -1;
		break;
	}
	case 24:
	{
        int Address = std::stoi(OperationStack[0]);
		if (ProtectAddress(Address, OperationStack)) return;
        
		stack[Address] = std::to_string(-(std::stoi(stack[Address])));

		break;
	}
	}
}

// Interpret function which leads to ProcessInstruction for subsequent processing

void Interpreter::Interpret(std::vector<std::string> instructions) {
	for (IP = 0; IP < instructions.size(); IP++) {
		try {
			if (!SkipNextOp) {
				
				ProcessInstruction(Tokenize(instructions[IP]));

				if (ReturnToIP){
					IP = PrevIP;
					ReturnToIP = 0;
				}else if (PreReturnToIP){
					PreReturnToIP = 0;
					ReturnToIP = 1;
				}
				
			}
			else {
				SkipNextOp = 0;
			}
		}
		catch (const std::exception& e) {
			Reporter::ThrowMessage(e.what(), 2);
		}
	}
}