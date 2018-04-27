#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std ;
#include "Row.h"



//
// Created by HP on 23-Apr-18.
//


void Pass1();
void fillFileList();
bool startsWith(string line, string charsStartWith);
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
bool checkIfContainSymbol (string symbol);
bool checkIfSymbolDefinedBefore(string symbol);
bool searchOPTABForOPCODE (string OPCODE);
vector <Row> listFile ;
map<string,int> symTab;

int main() {

//    Row r;
//
//r.setcomment("temona");
//r.setAddress(5);
//r.setLabel("h");
//r.setop_code("opcode");
//r.setOperand("operand");
    //cout << r.getcomment()<<endl <<r.getAddress()<<endl<<r.getLabel() <<endl<<r.getop_code()<<endl<<r.getOperand();



//        vector <Row> listFile ;
//        listFile.push_back(r);
    //  cout << listFile.at(0).getOperand();
    //cout <<"aayy";
    fillFileList();
    Pass1();
    cout << "test";

    return 0;
}
void fillFileList(){
    Row r ;
    r.setLabel("prog");
    r.setop_code("start");
    r.setOperand("1000");
    listFile.push_back(r);

    r.setLabel("loop");
    r.setop_code("lda");
    r.setOperand("x");
    listFile.push_back(r);

    r.setop_code("byte");
    r.setOperand("c'rita'");
    listFile.push_back(r);

    r.setop_code("comp");
    r.setOperand("x");
    listFile.push_back(r);
}
void Pass1 () {

    int LOCCTR;

    // TODO read first input line

    Row row =listFile.at(0);
    if (row.getop_code().compare("start") == 0) {
        // TODO save value of [OPERAND] as starting address
        // TODO initialize [LOCCTR] to stating address
        // TODO write line to intermediate file
        // TODO read next input line
        LOCCTR = atoi( row.getOperand().c_str() );
        row.setAddress(LOCCTR);
        row = listFile.at(1);
    } else {
        LOCCTR=0;
        row.setAddress(0);
    }
    while (row.getop_code().compare("END") != 0){
        //is not a comment line
        if (!row.isComment) {
            if (row.getLabel().compare("null")!=0) {
                bool found = checkIfSymbolDefinedBefore(row.getLabel());//return true if exist
                if (found) {
                    // TODO set error flag (duplicate symbol)
                    row.hasDuplicateError=true;
                } else {
                    // TODO insert (LABEL,LOCCTR) into SYMTAB
                }
            }

            //search OPTAB for OPCODE
            if (searchOPTABForOPCODE(row.getop_code())) {

                // increase location counter by length of the line (assume all 3)
                LOCCTR = LOCCTR + 3;

            } else if (row.getop_code().compare("word") == 0) {

                // increase location counter by length of the word  (3 bytes)
                LOCCTR = LOCCTR + 3;

            } else if (row.getop_code().compare("resw") == 0) {

                // TODO add 3 * #[OPPERAND] to LOCCTR

            } else if (row.getop_code().compare("resb") == 0) {

                // TODO add #[OPERAND] to LOCCTR//7welha l hex
                LOCCTR= atoi( row.getOperand().c_str() );
            } else if (row.getop_code().compare("byte") == 0){
                cout<<"vv" << row.getOperand().at(0);
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
