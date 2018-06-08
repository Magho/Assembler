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




        // TODO value of label is the object code in hex
        if (startsWith(listFile[i].getop_code(), "byte")) {

        } else if (startsWith(listFile[i].getop_code(), "word")) {

        }
        // TODO no object code
        else if (startsWith(listFile[i].getop_code(), "start")) {

            startAddressAtEndStatment = 0;

            if (listFile[i].getOperand() != "null") {
               // startAddressAtEndStatment = std::stoi(listFile[i].getOperand());
            }

            nameOfProg = listFile[i].getLabel();

        }else if (startsWith(listFile[i].getop_code(), "end")) {
            if (listFile[i].getOperand() != "null") {
             //   startAddressAtEndStatment = std::stoi(listFile[i].getOperand());
            }

         //   lengthOfProg = std::stoi(listFile[i].getAddress()) - startAddressAtEndStatment;
        }

        else if (startsWith(listFile[i].getop_code(), "base")) {

        }else if (startsWith(listFile[i].getop_code(), "ltorg")) {

        }else if (startsWith(listFile[i].getop_code(), "equ")) {

        }else if (startsWith(listFile[i].getop_code(), "org")) {

        }
        // TODO need to know that its a resw or resb to escape while writing in file
        else if (startsWith(listFile[i].getop_code(), "resw")) {

        }else if (startsWith(listFile[i].getop_code(), "resb")) {

        }
        else{


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

bool Pass2 :: startsWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(0, charsStartWith.length(), charsStartWith) == 0);
}

bool Pass2 :: endWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(line.size()-charsStartWith.length()-1, charsStartWith.length(), charsStartWith) == 0);
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
