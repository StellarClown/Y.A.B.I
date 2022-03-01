#include <iostream>
#include <string>
#include <vector>
#include "BfInterpreter.h"

using namespace std;

bool BfInterpreter::checkSyntax(const string& toCheck) const {
	int squareBrackets = 0;
	for (const char c : toCheck) {
		switch (c) {
		case '>':
		case '<':
		case '+':
		case '-':
		case '.':
		case ',':
			break;
		case '[':
			squareBrackets++;
			break;
		case ']':
			squareBrackets--;
			break;
		default:
			return true;
		}
	}
	if (squareBrackets) {
		cerr << "[x] Brackets are missing in the code..." << endl;
		return true;
	}
	return false;
}

unsigned BfInterpreter::matchingBrackets(const string& cmd, const unsigned& pos) const {
	switch (cmd[pos]) {
		case '[': {
			int32_t count = 1;
			for (uint32_t i = pos + 1; i < cmd.length(); i++) {
				if (cmd[i] == '[')
					count++;
				else if (cmd[i] == ']') {
					count--;
					if (count == 0)
						return i;
				}
			}
		}
		case ']': {
			int32_t count = 1;
			for (int32_t i = pos - 1; i >= 0; i--) {
				if (cmd[i] == ']')
					count++;
				else if (cmd[i] == '[') {
					count--;
					if (count == 0)
						return i;
				}
			}
		}
	}
}

void BfInterpreter::runCode() const {
	if (this->errorSyntax) {
		cerr << "[x] A syntax error was encountered in the code: Unable to interpret commands" << endl;
		return;
	}

	//Assets
	vector<uint8_t> data(30000, 0);
	uint16_t dataPtr = 0;
	uint32_t instructionPtr = 0;

	while (instructionPtr < this->_instructions.length()) {
		switch (this->_instructions[instructionPtr]) {
			case '>':
				if (dataPtr < 30000)
					dataPtr++;
				break;
			case '<':
				if (dataPtr > 0)
					dataPtr--;
				break;
			case '+':
				if (data[dataPtr] < 255)
					data[dataPtr]++;
				break;
			case '-':
				if (data[dataPtr] > 0)
					data[dataPtr]--;
				break;
			case '.':
				cout << data[dataPtr];
				break;
			case ',':
				char input;
				cin >> input;
				data[dataPtr] = input;
				break;
			case '[':
				if (!data[dataPtr])
					instructionPtr = matchingBrackets(this->_instructions, instructionPtr);
				break;
			case ']':
				if (data[dataPtr])
					instructionPtr = matchingBrackets(this->_instructions, instructionPtr) - 1;
				break;
		}
		instructionPtr++;
	}
}


/*

				CONSTRUCTOR

*/
BfInterpreter::BfInterpreter(const string& commands) {
	if (checkSyntax(commands)) {
		this->_instructions = "";
		this->errorSyntax = true;
		cerr << "[x] Syntax error in code..." << endl;
	}
	else
		this->_instructions = commands;
}
BfInterpreter::BfInterpreter(const char* commands) {
	if (checkSyntax(commands)) {
		this->_instructions = "";
		this->errorSyntax = true;
		cerr << "[x] Syntax error in code..." << endl;
	}
	else
		this->_instructions = commands;
}
BfInterpreter::BfInterpreter(const BfInterpreter& bf) {
	if (bf.errorSyntax) {
		this->errorSyntax = true;
		this->_instructions = "";
		cerr << "[x] You are trying to copy an object that has an incorrect instruction set..." << endl;
	}
	else {
		this->errorSyntax = bf.errorSyntax;
		this->_instructions = bf._instructions;
	}
}


/*

				OPERATOR =

*/
void BfInterpreter::operator= (const string& s) {
	if (checkSyntax(s)) {
		this->_instructions = "";
		this->errorSyntax = true;
		cerr << "[x] Syntax error in code..." << endl;
	}
	else {
		this->_instructions = s;
		this->errorSyntax = false;
	}
}
void BfInterpreter::operator= (const char* s) {
	if (checkSyntax(s)) {
		this->_instructions = "";
		this->errorSyntax = true;
		cerr << "[x] Syntax error in code..." << endl;
	}
	else {
		this->_instructions = s;
		this->errorSyntax = false;
	}
}
