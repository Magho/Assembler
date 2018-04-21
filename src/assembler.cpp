//============================================================================
// Name        : assembler.cpp
// Author      : Magho
// Version     :
// Copyright   : Your copyright notice
// Description : Assembler in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void Pass1();
bool startsWith(string line, string charsStartWith);
bool checkIfContainSymbol (string symbol);
bool checkIfSymbolDefinedBefore(string symbol);
bool searchOPTABForOPCODE (string OPCODE);

int main() {

	return 0;
}

void Pass1 () {

	string OPCODE;
	string currentLine;
	string label;
	string operand;
	string symbol;
	int LOCCTR;

	// TODO read first input line

	if (OPCODE.compare("START") == 0) {
			// TODO save value of [OPERAND] as starting address
			// TODO initialize [LOCCTR] to stating address
			// TODO write line to intermediate file
			// TODO read next input line
	} else {
		//initialize [LOCCTR] to 0
	}
	while (OPCODE.compare("END") != 0){

		//is not a comment line
		if (!startsWith(currentLine, "--")) {
			if (checkIfContainSymbol(label)) {

				// search SYMTAB for LABEL
				if (checkIfSymbolDefinedBefore(label)) {
					// TODO set error flag (duplicate symbol)
				} else {
					// TODO insert (LABEL,LOCCTR) into SYMTAB
				}
			}

			//search OPTAB for OPCODE
			if (searchOPTABForOPCODE(OPCODE)) {

				// increase location counter by length of the line (assume all 3)
				LOCCTR = LOCCTR + 3;

			} else if (OPCODE.compare("WORD") == 0) {

				// increase location counter by length of the word  (3 bytes)
				LOCCTR = LOCCTR + 3;

			} else if (OPCODE.compare("RESW") == 0) {

				// TODO add 3 * #[OPPERAND] to LOCCTR

			} else if (OPCODE.compare("RESB") == 0) {

				// TODO add #[OPERAND] to LOCCTR

			} else if (OPCODE.compare("BYTE") == 0){

				// TODO find the length of constant in bytes
				// TODO length to LOCCTR

			} else {

				// TODO set error flag (invalid OPCODE)

			}
		}

		// TODO write line to intermediate file
		// TODO read next input line
	}

	// TODO write last line to intermediate file
	// TODO save (LOCCTR - Starting address) as program length
}

bool startsWith (string line, string charsStartWith) {
	if(line.length() < charsStartWith.length())
		return false;
	return (line.compare(0, charsStartWith.length(), charsStartWith) == 0);
}

// TODO implement check if label is symbol
bool checkIfContainSymbol (string symbol) {
	// TODO set symbol to the found one
	return false;
}

// TODO implement checkIfSymbolDefinedBefore
bool checkIfSymbolDefinedBefore (string symbol) {
	return false;
}

// TODO implement searchOPTABForOPCODE
bool searchOPTABForOPCODE (string OPCODE) {
	return false;
}
