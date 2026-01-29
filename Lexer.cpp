#include "Lexer.h"
using namespace Lexer;

/*

Tokenizer to split arithmetic operations into tokens.
Given an input string, it separates numbers and identifiers.
Produces manageable tokens for further processing.

*/

std::vector<Token> Lexer::Tokenize(std::string Input) {
	std::vector<Token> Tokens;
	std::string Stack;

	bool IsQuotationMarkPresent = 0;
	bool WasQuotationMarkPresent = 0;
	bool FirstChar = 1;

	bool IsNegative = 0;

	for (int i = 0; i < Input.length(); i++) {
		char currentChar = Input.at(i);

		if (currentChar == '\"')
		{
			IsQuotationMarkPresent = !IsQuotationMarkPresent;
			if (!IsQuotationMarkPresent) WasQuotationMarkPresent = 1;
		}

		if (WasQuotationMarkPresent) {
			Tokens.push_back({ TokenType::IDENTIFIER, Stack });
			return Tokens;
		}

		if (!IsQuotationMarkPresent) {

		 	    if (currentChar == '-') {
					IsNegative = !IsNegative;
				}

				if (isspace(currentChar)) {
					if (isdigit(Stack[0])) {
						Tokens.push_back({ TokenType::NUMBER, (IsNegative ? "-"+Stack : Stack) });
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
						Tokens.push_back({ TokenType::NUMBER, (IsNegative ? "-" + Stack : Stack) });
					}
					else {
						Tokens.push_back({ TokenType::IDENTIFIER, Stack });
					}
				}
				
			}
			else {
				if (!FirstChar) {
					Stack += currentChar;
				}
				else {
					FirstChar = 0;
				}
			}
	}
	return Tokens;
}