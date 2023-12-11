#include <sstream>

#include "tokenizer.h"
#include "utility.h"

void checkForToken(token& tok_ref, std::string word) {
	tok_ref.type = token_enum::NONE;
	tok_ref.value = 0;

	if (word == "return") {
		tok_ref.type = token_enum::RETURN;
	} else {
		if (isAllDigits(word)) {
			tok_ref.type = token_enum::INT_LITERAL;
			tok_ref.value = std::stoi(word);
		}
	}
}

std::vector <token> Tokenizer::tokenize(std::string source) {
	std::vector<token> tokens;
	std::stringstream words(source);
	std::stringstream wordbuf("");
	std::string word;

	token token_temp;

	while (words >> word) {
		for (char c : word) {
			if (c == ';') {
				if (!wordbuf.str().empty()) {
					checkForToken(token_temp, wordbuf.str());
					tokens.push_back(token_temp);
				}

				token_temp.type = token_enum::SEMICOLON;
				token_temp.value = 0;
				tokens.push_back(token_temp);

				wordbuf.str("");
				wordbuf.clear();
			} else {
				wordbuf << c;
			}
		}

		if (!wordbuf.str().empty()) {
			checkForToken(token_temp, wordbuf.str());
			tokens.push_back(token_temp);
		}

		wordbuf.str("");
		wordbuf.clear();
	}

	return tokens;
}
