#pragma once
#include <iostream>
#include <vector>
#include <string>

enum class Token_Enum {
	UNKNOWN = -1, EXIT = 0, INT_LITERAL = 1, SEMICOLON = 2
};

struct Token {
	Token_Enum type = Token_Enum::UNKNOWN;
	std::string value = "";
};

class Tokenizer {
	public:
		std::vector<Token> tokenize(std::string source); 
};
