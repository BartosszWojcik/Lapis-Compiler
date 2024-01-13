#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "tokenizer.h"
#include "utility.h"

std::string tokensToAsm(std::vector<Token> tokens) {
	std::stringstream assembly("");
	assembly << "global _start\n_start:\n";

	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].type == Token_Enum::EXIT) {
			assembly << "	mov rax, 60\n";

			i++;
			if (i < tokens.size() && tokens[i].type == Token_Enum::INT_LITERAL) {
				assembly << "	mov rdi, " << tokens[i].value << "\n";
				
				i++;
				if (i < tokens.size() && tokens[i].type == Token_Enum::SEMICOLON) {
					assembly << "	syscall\n";
				}
			}
		}
	}

	return assembly.str();
}

int main(int argc, char* argv[]) {
	std::string sourceFile = "";
	std::string outputFile = "";
	
	/* Get the source and output arguments */
	if (argc == 5) {
		std::string argument;
		for (int i = 1; i < argc; i++) {
			argument = argv[i];

			if (argument == "-s") {
				if (i + 1 < argc) {
					argument = argv[i + 1];
					sourceFile = argument;
				}
			} else if (argument == "-o") {
				if (i + 1 < argc) {
					argument = argv[i + 1];
					outputFile = argument;
				}
			}
		}

		std::cout << "Compiling " << sourceFile << " to " << outputFile << std::endl;
	} else {
		std::cout << "Invalid arguments! Proper arguments: -s source.lps -o output" << std::endl;
		return 1;
	}

	/* Read in the source file */

	std::string line;
	std::stringstream content;
	std::ifstream fileIn(sourceFile);

	while (std::getline(fileIn, line)) {
		content << line << "\n";		
	}

	fileIn.close();

	/* Tokenize the source and compile it into the assembly file */

	std::stringstream stringbuf;
	stringbuf << outputFile << ".asm";

	Tokenizer tokenizer;
	std::ofstream fileOut(stringbuf.str());
	fileOut << tokensToAsm(tokenizer.tokenize(content.str()));
	fileOut.close();

	/* Assemble the compiled file */

	resetBuffer(stringbuf);
	stringbuf << "nasm -f elf64 " << outputFile << ".asm";
	system(stringbuf.str().c_str());

	resetBuffer(stringbuf);
	stringbuf << "ld -s -o " << outputFile << " " << outputFile << ".o";
	system(stringbuf.str().c_str());

	resetBuffer(stringbuf);
	stringbuf << "rm " << outputFile << ".o";
	system(stringbuf.str().c_str());

	return 0;
}
