#include "utility.h"

bool isAllDigits(std::string& str) {
	for (char c : str) {
		if (!isdigit(c))
			return false;
	}

	return true;
}

bool isAllAplhaNumeric(std::string& str) {
	for (int i = 0; i < str.size(); i++) {
		if (!isalnum(str[i]))
			return false;
	}

	return true;
}

char lastChar(std::string& str) {
	if (!str.empty())
		return str[str.size() - 1];	
	else 
		return 0;
}

void resetBuffer(std::stringstream& stringbuf) {
	stringbuf.str("");
	stringbuf.clear();
}
