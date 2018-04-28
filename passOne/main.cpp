#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
using namespace std ;
#include "Row.h"
#include "optable.h"
#include "parsing_map.h"



//
// Created by HP on 23-Apr-18.
//


void Pass1();
void fillFileList();
bool checkIfSymbolDefinedBefore(string symbol);
bool searchOPTABForOPCODE (string OPCODE);
string addHex(string hex1,string hex2);
string decimalToHex(int decimal);
int hexToDecimal(string hexa);
void printFileList();
static vector <Row> listFile ;
map<string,string> symTab;
optable opTab;
parsing_map parser;

int main() {

    opTab.setTable();
//    list<map<string, string>> parsingList=parser.parisngFunction("D:\\magho\\passOne\\test.txt");
//    parser.printTheList(parsingList);

    fillFileList();
    Pass1();
    printFileList();
    return 0;
}

void printFileList() {
      for(int i=0;i<listFile.size();i++) {
          Row r=listFile.at(i);
          cout <<r.getAddress()<<"  "<<r.getLabel()<<"  "<<r.getop_code()<<"  "<<r.getOperand()<<"  "<<r.getcomment()<<"  " <<r.errorMessge<<endl;
      }
  /*  for ( std::map< string, string >::const_iterator iter = symTab.begin();
          iter != symTab.end(); ++iter )
        cout << iter->first << '\t' << iter->second << '\n';

    cout << endl;*/
}

void fillFileList(){
    Row r ;
    r.setLabel("copy");
    r.setop_code("start");
    r.setOperand("1000");
    listFile.push_back(r);


    r.setLabel("first");
    r.setop_code("add");
    r.setOperand("retadr");
    listFile.push_back(r);

    r.setLabel("first");
    r.setop_code("jsub");
    r.setOperand("rdrec");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("add");
    r.setOperand("length");
    listFile.push_back(r);

   /* r.setLabel("null");
    r.setop_code("org");
    r.setOperand("5500");
    listFile.push_back(r);*/

    r.setLabel("null");
    r.setop_code("comp");
    r.setOperand("zero");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("jeq");
    r.setOperand("endfil");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("jsub");
    r.setOperand("wrrec");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("j");
    r.setOperand("cloop");
    listFile.push_back(r);

    r.setLabel("endfil");
    r.setop_code("add");
    r.setOperand("eof");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("add");
    r.setOperand("buffer");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("add");
    r.setOperand("three");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("add");
    r.setOperand("length");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("jsub");
    r.setOperand("wrrec");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("add");
    r.setOperand("retadr");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("rsub");
    r.setOperand("null");
    listFile.push_back(r);

    r.setLabel("eof");
    r.setop_code("byte");
    r.setOperand("c'eof'");
    listFile.push_back(r);

    r.setLabel("three");
    r.setop_code("word");
    r.setOperand("3");
    listFile.push_back(r);

    r.setLabel("zero");
    r.setop_code("word");
    r.setOperand("0");
    listFile.push_back(r);

    r.setLabel("retadr");
    r.setop_code("resw");
    r.setOperand("1");
    listFile.push_back(r);

    r.setLabel("length");
    r.setop_code("resw");
    r.setOperand("1");
    listFile.push_back(r);

    r.setLabel("buffer");
    r.setop_code("resb");
    r.setOperand("4096");
    listFile.push_back(r);

    r.setLabel("rita");
    r.setop_code("equ");
    r.setOperand("length");
    listFile.push_back(r);

    r.setLabel("null");
    r.setop_code("end");
    r.setOperand("first");
    listFile.push_back(r);


}

void Pass1 () {
    string LOCCTR;
    int index=0;
    string startAdr;
    Row row = listFile.at(index);
    if (row.getop_code().compare("start") == 0) {
        LOCCTR = row.getOperand();
        symTab.insert(pair<string, string>(row.getLabel(), LOCCTR));
        listFile.at(index).setAddress(LOCCTR);
        startAdr=LOCCTR;
        index++;
        row = listFile.at(index);
        listFile.at(index).setAddress(LOCCTR);
    } else {
        LOCCTR = "0";
        listFile.at(index).setAddress("0");
    }

    while ((row.getop_code().compare("end") != 0)&&(index<listFile.size()) ){
        //is not a comment line
        if (!row.isComment) {
            if (row.getLabel().compare("null") != 0) {
                bool found = checkIfSymbolDefinedBefore(row.getLabel());//return true if exist
                if (found) {
                    listFile.at(index).hasError=true;
                    listFile.at(index).errorMessge="The Label already exists";
                } else {
                    symTab.insert(pair<string, string>(row.getLabel(), LOCCTR));
                }
            }
            //search OPTAB for OPCODE
            if (searchOPTABForOPCODE(row.getop_code())) {
                // increase location counter by length of the line (assume all 3)
                LOCCTR = addHex(LOCCTR,"3");
            } else if (row.getop_code().compare("word") == 0) {
                // increase location counter by length of the word  (3 bytes)
                LOCCTR = addHex(LOCCTR,"3");
            } else if (row.getop_code().compare("resw") == 0) {
                // TODO add 3 * #[OPPERAND] to LOCCTR
                LOCCTR =addHex(LOCCTR,decimalToHex(3*atoi(row.getOperand().c_str())));
            }else if (row.getop_code().compare("resb") == 0) {
                // TODO add #[OPERAND] to LOCCTR
                LOCCTR=addHex(LOCCTR,decimalToHex(atoi( row.getOperand().c_str())));
            } else if (row.getop_code().compare("byte") == 0){
                char ch = row.getOperand().at(0);
                switch (ch){
                    case 'c': {
                        stringstream str;
                        str << row.getOperand().size() - 3;
                        LOCCTR = addHex(LOCCTR, str.str());
                    }
                        break;
                    case 'x': {
                        if (((row.getOperand().size() - 3) % 2) == 0) {
                            stringstream str;
                            str << (row.getOperand().size() - 3) / 2;
                            LOCCTR = addHex(LOCCTR, str.str());
                        } else {
                            listFile.at(index).hasError=true;
                            listFile.at(index).errorMessge="The hexidecimal value has an odd numbers of digits";
                        }
                    }
                        break;
                }

            }else {
                listFile.at(index).hasError=true;
                listFile.at(index).errorMessge="Invalid op-code";
            }
        }
        index++;
        row = listFile.at(index);
        if(row.getop_code().compare("equ") == 0){
            string label =row.getOperand();
            int num=atoi( label.c_str());
            stringstream str;
            str << num;
            if(str.str().size()==label.size()){
                listFile.at(index).setAddress(label);
            }else if(symTab.count(label)) {
                listFile.at(index).setAddress(symTab.at(label));
            }else{
                listFile.at(index).hasError=true;
                listFile.at(index).errorMessge="Not defined label, may be forward ref";
            }
        }else if(row.getop_code().compare("org") == 0){
            string label =row.getOperand();
            int num=atoi( label.c_str());
            stringstream str;
            str << num;
            if(str.str().size()==label.size()){
                LOCCTR=row.getOperand();
            }else if(symTab.count(label)) {
                LOCCTR=symTab.at(label);
            }else{
                listFile.at(index).hasError=true;
                listFile.at(index).errorMessge="Not defined label, may be forward ref";
            }
        }else {
            listFile.at(index).setAddress(LOCCTR);
        }

    }
    if(index>=(listFile.size())){
        listFile.at(index-1).hasError=true;
        listFile.at(index-1).errorMessge="here is no end statement";
    }

    // TODO write last line to intermediate file
    // TODO save (LOCCTR - Starting address) as program length
    stringstream s;
    s<<-1*atoi( startAdr.c_str());
    string progLength = addHex(LOCCTR,s.str());
}

bool checkIfSymbolDefinedBefore(string symbol) {
    return symTab.count(symbol);
}

bool searchOPTABForOPCODE(string OPCODE) {

    return opTab.opTable.count( OPCODE );
}

string addHex(string hex1,string hex2){
    return decimalToHex(hexToDecimal(hex1)+hexToDecimal(hex2));
}

string decimalToHex(int decimal){
    stringstream ss;
    ss<<hex << decimal;
    string res ( ss.str() );

    return res.c_str();
}

int hexToDecimal(string hexa){
    int decimal;
    stringstream ss;
    ss  <<  hexa;
    ss >> hex >> decimal ;

    return decimal;
}