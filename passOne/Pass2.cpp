//
// Created by magho on 05/06/18.
//

#include "Pass2.h"
#include "parsing.h"
#include <bits/stdc++.h>

void Pass2::pass2Algoritm(vector<Row> listFile) {

    vector<string> objectcodes;
    int pc ;
    int format ;
    int n,i,x,b,p,e;
    string nameOfProg;
    int lengthOfProg;
    int startAddressAtEndStatment;
    int startAddressAtStartStatment;

    for (int i = 0; i < listFile.size(); ++i) {

        string object_code;
        if (listFile[i].isComment) {

        } else {

            if (startsWith(listFile[i].getop_code(), "byte")) {
                object_code = byte_operand(listFile[i].getOperand());

            } else if (startsWith(listFile[i].getop_code(), "word")) {
                object_code = word_operand(listFile[i].getOperand());

            } else if (startsWith(listFile[i].getop_code(), "start")) {
                object_code = start_operand(startAddressAtStartStatment, nameOfProg, listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "end")) {
                object_code = end_operand(startAddressAtStartStatment,startAddressAtEndStatment,
                                          lengthOfProg ,listFile[i]);


            } else if (startsWith(listFile[i].getop_code(), "base")) {
                //TODO need to know that base is avaliable
                object_code = base_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "ltorg")) {
                object_code = ltorg_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "equ")) {
                object_code = equ_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "org")) {
                object_code = org_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "resw")) {
                // TODO need to know that its a resw or resb to escape while writing in file
                object_code = resw_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "resb")) {
                // TODO need to know that its a resw or resb to escape while writing in file
                object_code = resb_operand(listFile[i]);

            } else {

            }

            int currentAddress = std::stoi(listFile[i].getAddress());
            format = formatType(listFile[i].getop_code());
            pc = calcPC(currentAddress, format);



            // determine addressing mode
            if (startsWith(listFile[i].getOperand(), "#")) {
                //immediate
                n = 0;
                i = 1;
                x = 0;
            } else if (startsWith(listFile[i].getOperand(), "@")) {
                //indirect
                n = 1;
                i = 0;
                x = 0;
            } else {
                //direct
                n = 1;
                i = 1;
                if (endWith(listFile[i].getOperand(), ",x")) {
                    //indexed
                    x = 1;
                }
            }


        }

    }
}

bool Pass2 :: startsWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(0, charsStartWith.length(), charsStartWith) == 0);
}

bool Pass2 :: endWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(line.size()-charsStartWith.length(), charsStartWith.length(), charsStartWith) == 0);
}

int Pass2 :: formatType (string opcode) {

    //format 4 : all opcodes starts with '+'
    if (startsWith(opcode, "+")) {
        return 4;
    }
    //format 2 : all opcodes end with 'r'
    else if (endWith(opcode, "r")) {
        return 2;
    //format 1 doesn't exist so rest is '3'
    } else {
        return 3;
    }
}

int Pass2 :: calcPC (int currentAddress, int format) {
    int pc;
    if (format == 4) {
        pc =currentAddress + 4;
    } else if (format == 2){
        pc =currentAddress + 2;
    } else {
        pc =currentAddress + 3;
    }
    return pc;
}

string Pass2:: string_to_hex(const std::string& input) {
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

string Pass2:: decimalToHex(int decimal){
    stringstream ss;
    ss<<hex << decimal;
    string res ( ss.str() );

    return res.c_str();
}

string Pass2:: byte_operand(string operand){

    string object_code;
    if (startsWith(operand, "c")) {
        //skip c="...."
        string operand_value = operand.substr(3, operand.size()-4);
        object_code = string_to_hex(operand_value);
    } else {
        //start with x
        string operand_value = operand.substr(3, operand.size()-4);
        object_code = operand_value;
    }
    return object_code;
}

string Pass2 :: word_operand(string operand) {
    string object_code = decimalToHex(std::stoi(operand));
    return object_code;
}

string Pass2 :: start_operand(int& startAddressAtStartStatment,string& nameOfProg , Row entry) {

    startAddressAtStartStatment = 0;
    if (entry.getOperand() != "null") {
        startAddressAtStartStatment = std::stoi(entry.getOperand());
    }
    nameOfProg = entry.getLabel();

    return "null";
}

string Pass2 ::end_operand(int& startAddressAtStartStatment,int& startAddressAtEndStatment,
                           int& lengthOfProg , Row entry) {

    if (entry.getOperand() != "null") {
        startAddressAtEndStatment = std::stoi(entry.getOperand());
    }
    lengthOfProg = std::stoi(entry.getAddress()) - startAddressAtStartStatment;

    return "null";
}

string Pass2 :: base_operand(Row entry) {
    return "null";
}

string Pass2 :: ltorg_operand(Row entry) {
    return "null";
}

string Pass2 :: equ_operand(Row entry) {
    return "null";
}

string Pass2 :: org_operand(Row entry) {
    return "null";
}

string Pass2 :: resb_operand(Row entry) {
    return "null";
}

string Pass2 :: resw_operand(Row entry) {
    return "null";
}

void Pass2:: test(vector <Row> listFile){

    cout << "***********************************************\n";
    cout << "***********************************************\n";

    int sss ;

    string ss = "12'";
    cout<< word_operand(ss);


    cout << "***********************************************\n";
    cout << "***********************************************\n";

}

