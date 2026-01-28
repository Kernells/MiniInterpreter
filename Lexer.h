#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Lexer
{
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

	std::vector<Token> Tokenize(std::string Input);

};