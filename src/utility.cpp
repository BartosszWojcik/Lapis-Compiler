#include "utility.h"

bool isAllDigits(std::string& str) {
	for (char c : str) {
		if (!isdigit(c))
			return false;
	}

	return true;
}

bool isAllAplhaNumeric(std::string& str) {
	for (char c : str) {
		if (!isalnum(c))
			return false;
	}

	return true;
}

char lastChar(std::string& str) {
	if (str.size() > 0)
		return str[str.size() - 1];	
	else 
		return 0;
}
