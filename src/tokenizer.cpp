#include <sstream>

#include "tokenizer.h"
#include "utility.h"

void checkForToken(Token& tok_ref, std::string word) {
	tok_ref.type = Token_Enum::UNKNOWN;
	tok_ref.value = "";

	if (word == "exit") {
		tok_ref.type = Token_Enum::EXIT;
	} else {
		if (isAllDigits(word)) {
			tok_ref.type = Token_Enum::INT_LITERAL;
			tok_ref.value = word;
		}
	}
}

std::vector<Token> Tokenizer::tokenize(std::string source) {
	std::vector<Token> tokens;
	std::stringstream words(source);
	std::stringstream wordbuf("");
	std::string word;

	Token token_temp;

	while (words >> word) {
		for (int i = 0; i < word.size(); i++) {
			if (word[i] == ';') {
				if (!wordbuf.str().empty()) {
					checkForToken(token_temp, wordbuf.str());
					tokens.push_back(token_temp);
				}

				token_temp.type = Token_Enum::SEMICOLON;
				token_temp.value = "";
				tokens.push_back(token_temp);

				resetBuffer(wordbuf);
			} else {
				wordbuf << word[i];
			}
		}

		if (!wordbuf.str().empty()) {
			checkForToken(token_temp, wordbuf.str());
			tokens.push_back(token_temp);
		}

		resetBuffer(wordbuf);
	}

	return tokens;
}
