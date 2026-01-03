#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <cctype>
#include <string>

/*

 /$$      /$$ /$$           /$$       /$$$$$$             /$$                                                         /$$
| $$$    /$$$|__/          |__/      |_  $$_/            | $$                                                        | $$
| $$$$  /$$$$ /$$ /$$$$$$$  /$$        | $$   /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$
| $$ $$/$$ $$| $$| $$__  $$| $$        | $$  | $$__  $$|_  $$_/   /$$__  $$ /$$__  $$ /$$__  $$ /$$__  $$ /$$__  $$|_  $$_/   /$$__  $$ /$$__  $$
| $$  $$$| $$| $$| $$  \ $$| $$        | $$  | $$  \ $$  | $$    | $$$$$$$$| $$  \__/| $$  \ $$| $$  \__/| $$$$$$$$  | $$    | $$$$$$$$| $$  \__/
| $$\  $ | $$| $$| $$  | $$| $$        | $$  | $$  | $$  | $$ /$$| $$_____/| $$      | $$  | $$| $$      | $$_____/  | $$ /$$| $$_____/| $$
| $$ \/  | $$| $$| $$  | $$| $$       /$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$| $$      | $$$$$$$/| $$      |  $$$$$$$  |  $$$$/|  $$$$$$$| $$
|__/     |__/|__/|__/  |__/|__/      |______/|__/  |__/   \___/   \_______/|__/      | $$____/ |__/       \_______/   \___/   \_______/|__/
																					 | $$
																					 | $$
																					 |__/
*/

/*

WIP

Made by Kernels
An experimental C++ interpreter for a minimal instruction language, focusing on execution flow, parsing, and VM fundamentals.

*/


int IP = 0; // Instruction pointer
std::vector <std::string> stack; // For arithmetic operations (push, add, etc)
std::vector <std::string> env; // Environment storage (variables, names, etc)

std::vector<std::tuple<std::string, int>> operations = {      // Operation set
	std::make_tuple("add",0),
	std::make_tuple("sub",1),
	std::make_tuple("mul",2),
	std::make_tuple("div",3),
	std::make_tuple("print",4),
};

std::vector<std::string> test_instructions = {               // Test instruction set
	"add 5 5",
	"10 10 add",
	"get 0",
	"1 get"
};



// Message throwing function for info, warnings, and errors.

void ThrowMessage(std::string message, int type) { // Type 0 = Info, Type 1 = Warning, Type 2 = Error	

	switch (type) {
	case 0:
	{
		std::cout << "[INFO]: " << message << std::endl;
	}
	case 1:
	{
		std::cout << "[WARNING]: " << message << std::endl;
	}
	case 2:
	{
		std::cout << "[ERROR]: " << message << std::endl;
	}
	}

}

// Token Types

enum class TokenType {
	NUMBER,
	IDENTIFIER
};

// Token Structure

struct Token {
	TokenType type;
	std::string value;
};

/*

Tokenizer to split arithmetic operations into tokens.
Given an input string, it separates numbers and identifiers.
Produces manageable tokens for further processing.

*/

std::vector<Token> Tokenize(std::string Input) {
	std::vector<Token> Tokens;
	std::string Stack;
	for (int i = 0; i < Input.length(); i++) {
		char currentChar = Input.at(i);
		if (isspace(currentChar)) {
			if (isdigit(Stack[0])) {
				Tokens.push_back({ TokenType::NUMBER, Stack });
			}
			else {
				Tokens.push_back({ TokenType::IDENTIFIER, Stack });
			}
			Stack = "";
			continue;
		}
		if (isdigit(currentChar)) {
			Stack += currentChar;
		}
		if (isalpha(currentChar)) {
			Stack += currentChar;
		}
		if (i == Input.length() - 1) {
			if (isdigit(Stack[0])) {
				Tokens.push_back({ TokenType::NUMBER, Stack });
			}
			else {
				Tokens.push_back({ TokenType::IDENTIFIER, Stack });
			}
		}
	}
	return Tokens;
}

/*

ProcessInstruction processes the current instruction set and determines if it corresponds to any function.
If it does then it'll recognize it by it's function id and do the corresponding response.

*/

void ProcessInstruction(std::vector<Token> Instructions) {

	// This assumes the values are always numbers, To be updated
	// Operation types 
	// 0 = add, 1 = sub, 2 = mul, 3 = div, 4 = get, 5 = pop

	int OperationType = -1; 
	std::vector<int> OperationStack;
	for (Token token : Instructions) {
		if (token.type == TokenType::IDENTIFIER) {
			if (token.value == "add") {
				OperationType = 0;
			}
			if (token.value == "get") {
				OperationType = 4;
			}
		}
		else if (token.type == TokenType::NUMBER) {
			int value = std::stoi(token.value);
			OperationStack.push_back(value);
		}
	}
	switch (OperationType) {
	case 0:
	{
		int operation_result = 0;
		for (int operation : OperationStack) {
			operation_result += operation;
		}
		stack.push_back(std::to_string(operation_result));
		std::vector<int>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	case 4:
	{
		std::cout << stack[OperationStack.at(0)]; // Print the stack value at the given index, To be improved later
		std::vector<int>().swap(OperationStack);
		OperationStack.clear();
		break;
	}
	}
}

// Interpret function which leads to ProcessInstruction for subsequent processing

void Interpret(std::vector<std::string> instructions) {
	for (IP = 0; IP < instructions.size(); IP++) {
		ProcessInstruction(Tokenize(instructions[IP]));
	}
    
}

// For easier separation, to add binary reading

int main()
{
	Interpret(test_instructions);
}
