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
	"printa Hello, World!"
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

void ProcessInstruction(std::string Instruction) {
	for (int operation_set = 0; operation_set < operations.size(); operation_set++) {
		std::string currentoperationset = std::get<0>(operations[operation_set]);
		int currentoperationid = std::get<1>(operations[operation_set]);

		int valid_instruction = 0;


		// Check if instruction starts with any operation set

		if (Instruction.rfind(currentoperationset, 0) == 0) {
			if (isspace(Instruction.at(currentoperationset.length()))) {
				valid_instruction = 1;
				switch (currentoperationid) {
				case 0:
				{

				}
			/*	
			   -TODO : Implement stack incorporation
			    case 4:
				{
					std::string plaintext = Instruction.erase(Instruction.find(currentoperationset), currentoperationset.length() + 1);
					std::cout << plaintext;
					break;
				}
				
				*/
				}
			}
		}

		if (!valid_instruction) {
			std::string ErrorLine = std::to_string(IP);
			std::string ErrorDescription = "Error at line "+ ErrorLine + " : Instruction '" + Instruction + "' not recognized.";
			ThrowMessage(ErrorDescription, 2);
		}
	}
}

// Interpret function which leads to ProcessInstruction for subsequent processing

void Interpret(std::vector<std::string> instructions) {
	for (IP = 0; IP < instructions.size(); IP++) {
		std::string CurrentInstruction = instructions[IP];
		ProcessInstruction(CurrentInstruction);
	}
}

// For easier separation, to add binary reading

int main()
{
	Interpret(test_instructions);
}
