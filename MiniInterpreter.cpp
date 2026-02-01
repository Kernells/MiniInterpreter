#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <cctype>
#include <string>
#include <tuple>
#include "Interpreter.h"

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

std::vector<std::string> test_instructions = {               // Test instruction set
"push \"Hello, world!\"",
"sprint 0",
"print 1",
"invoke 1",
"print \"Hello, this is the continuation\"",
"print 3",
"print \"Test\"",
"invoke 6"
};

// To add binary reading

int main()
{
	Interpreter::Interpret(test_instructions);
}
