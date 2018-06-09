//
// Created by magho on 05/06/18.
//

#ifndef PASSONE_PASS2_H
#define PASSONE_PASS2_H


#include <string>
#include <vector>
#include <map>
#include "Row.h"
#include "litLine.h"

using namespace std ;

class Pass2{

private:

public:

    void pass2Algoritm(vector<Row> listFile,map<string,string> symTable,vector<litLine> litTab);
    bool startsWith (string line, string charsStartWith);
    bool endWith (string line, string charsStartWith);
    int formatType (string opcode);
    int calcPC (int currentAddress, int format);
    string string_to_hex(const std::string& input);
    string decimalToHex(int decimal);
    void test(vector <Row> listFile);


    string byte_operand(string operand);
    string word_operand(string operand);
    string start_operand(int& startAddressAtStartStatment,string& nameOfProg , Row entry);
    string end_operand(int& startAddressAtStartStatment,int& startAddressAtEndStatment, int& lengthOfProg , Row entry,map<string,string>);
    string base_operand(Row entry, int& base, map<string, string> symTable);
    string ltorg_operand(Row entry);
    string equ_operand(Row entry);
    string org_operand(Row entry);
    string resb_operand(Row entry);
    string resw_operand(Row entry);
    string toHex(int i);

};

#endif //PASSONE_PASS2_H
