//
// Created by magho on 05/06/18.
//

#include "Pass2.h"
#include "parsing.h"
#include "optable.h"
#include <bits/stdc++.h>

void Pass2::pass2Algoritm(vector<Row> listFile,map<string,string> symTable,map<string,string> litTable) {

    vector<string> objectcodes;
    int pc ;
    int base = -1;
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
                    int currentAddress = std::stoi(listFile[i].getAddress());
                    format = formatType(listFile[i].getop_code());
                    pc = calcPC(currentAddress, format);


        // determine addressing mode
                    if (startsWith(listFile[i].getOperand(), "#")) {
            //immediate
                        string opr = listFile[i].getOperand().substr(1);
                        int operation = std::stoi(listFile[i].getop_code(),nullptr,16);
                        operation = opertion | (1);
                        operation = operation && ~(1 << 1)
                        int obj = operation;
                        obj <<=1*4;
                        if(format == 4) obj |= 1;
                        obj <<=4*3;
                        if(!isdigit(opr.c_str()[0])){
                            int addr = std::stoi(symTable[opr],nullptr,16);
                            obj |= (addr&((1<<12)-1));
                        }else{
                            obj |= (std::stoi(opr) & ((1<<12)-1));
                        }
            //itoa(obj,string,16)
                    } else if (startsWith(listFile[i].getOperand(), "@")) {
            //indirect
                    string opr = listFile[i].getOperand().substr(1);
                    int operation = std::stoi(listFile[i].getop_code(),nullptr,16);
                    operation = operation | (1 << 1); // set n's bit
                    operation = operation & ~(1);//clear i's bit
                    int obj = operation;
                    obj <<= 4;
                    if(format == 4) obj |= 1;
                    if (endWith(listFile[i].getOperand(), ",x")) {
                        obj |= (1<<3);
                    }

                    int addr = std::stoi(symTable[opr],nullptr,16);
                    int disp = addr - pc;
                    if(!(disp<1024&&disp>=-1024)&& base != -1){
                        //using base
                        disp = addr - base;
                        obj |= (1<<2);
                    }else{
                        obj |= (1<<1);
                    }
                    obj <<=4*3;
                    obj |= (disp &((1<<12)-1));

                    } else {
                        //direct
                        string opr = listFile[i].getOperand().substr(1);
                        int operation = std::stoi(listFile[i].getop_code(),nullptr,16);
                        operation = operation | (1 << 1); // set n's bit
                        operation = operation | (1 << 0); // set i's bit
                        int obj = operation;
                        obj <<= 4;
                        if(format == 4) obj |= 1;//set e's bit
                        if (endWith(listFile[i].getOperand(), ",x")) {
                            obj |= (1<<3);//seting x's bit
                        }
                        int addr = std::stoi(symTable[opr],nullptr,16);
                        int disp = addr - pc;
                        if(!(disp<1024&&disp>=-1024)&& base != -1){
                            //using base
                            disp = addr - base;
                            obj |= (1<<2);
                        }else{
                            obj |= (1<<1);
                        }
                        obj <<=4*3;
                        obj |= (disp &((1<<12)-1));
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
