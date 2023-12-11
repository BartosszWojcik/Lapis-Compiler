#pragma once
#include <iostream>
#include <vector>
#include <string>

enum class token_enum {
	NONE = -1, RETURN = 0, INT_LITERAL = 1, SEMICOLON = 2
};

struct token {
	token_enum type = token_enum::NONE;
	int value = 0;
};

class Tokenizer {
	public:
		std::vector<token> tokenize(std::string source); 
};
