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




        // TODO value of label is the object code in hex
        if (startsWith(listFile[i].getop_code(), "byte")) {

        } else if (startsWith(listFile[i].getop_code(), "word")) {

        }
        // TODO no object code
        else if (startsWith(listFile[i].getop_code(), "start")) {

            startAddressAtEndStatment = 0;

            if (listFile[i].getOperand() != "null") {
                startAddressAtEndStatment = std::stoi(listFile[i].getOperand());
            }

            nameOfProg = listFile[i].getLabel();

        }else if (startsWith(listFile[i].getop_code(), "end")) {
            if (listFile[i].getOperand() != "null") {
                startAddressAtEndStatment = std::stoi(listFile[i].getOperand());
            }

            lengthOfProg = std::stoi(listFile[i].getAddress()) - startAddressAtEndStatment;
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






        int currentAddress = std::stoi(listFile[i].getAddress());
        format = formatType(listFile[i].getop_code());
        pc = calcPC(currentAddress, format);







        // determine addressing mode
        if (startsWith(listFile[i].getOperand(), "#")) {
            //immediate
            n=0;
            i=1;
            x=0;
        } else if (startsWith(listFile[i].getOperand(), "@")) {
            //indirect
            n=1;
            i=0;
            x=0;
        } else {
            //direct
            n=1;
            i=1;
            if (endWith(listFile[i].getOperand(), ",x")) {
                //indexed
                x = 1;
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