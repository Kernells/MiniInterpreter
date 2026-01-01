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
std::vector <std::string> stack; // For arithmetic functions (push, add, etc)

std::vector<std::tuple<std::string, int>> functions = {      // Functions set
	std::make_tuple("print",0)
};

std::vector<std::string> test_instructions = {               // Test instruction set
	"printa Hello, World!"
};

void ThrowMessage(std::string message, int type) { // type 0 = info, type 1 = warning, type 2 = error	
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

/*

ProcessInstruction processes the current instruction set and determines if it corresponds to any function.
If it does then it'll recognize it by it's function id and do the corresponding response.

*/

void ProcessInstruction(std::string Instruction) {
	for (int function_set = 0; function_set < functions.size(); function_set++) {
		std::string currentfunctionset = std::get<0>(functions[function_set]);
		int currentfunctionid = std::get<1>(functions[function_set]);

		int valid_instruction = 0;

		if (Instruction.rfind(currentfunctionset, 0) == 0) {
			if (isspace(Instruction.at(currentfunctionset.length()))) {
				valid_instruction = 1;
				switch (currentfunctionid) {
				case 0:
				{
					std::string plaintext = Instruction.erase(Instruction.find(currentfunctionset), currentfunctionset.length() + 1); // + 1 for white space
					std::cout << plaintext;
				}
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
