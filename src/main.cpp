#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "tokenizer.h"

void print_ut(std::vector<token>& tok) {
	for (int i = 0; i < tok.size(); i++) {
		if (tok[i].type == token_enum::RETURN)
			std::cout << "ret" << " : " << tok[i].value << std::endl;

		else if (tok[i].type == token_enum::INT_LITERAL)
			std::cout << "int_lit" << " : " << tok[i].value << std::endl;

		else if (tok[i].type == token_enum::SEMICOLON)
			std::cout << "semi" << " : " << tok[i].value << std::endl;
		else if (tok[i].type == token_enum::NONE)
			std::cout << "none" << " : " << tok[i].value << std::endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc == 2)
		std::cout << "Compiling " << argv[1] << std::endl;
	else {
		std::cout << "Invalid arguments! Proper usage: ./lapis.out {filename.lps}" << std::endl;
		return 1;
	}	

	std::string line;
	std::stringstream content;
	std::ifstream file(argv[1]);

	while (std::getline(file, line)) {
		content << line << "\n";		
	}

	file.close();

	Tokenizer tokenizer;
	std::vector<token> tokens = tokenizer.tokenize(content.str());

	print_ut(tokens);
}
