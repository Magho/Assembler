#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
#include <cstdio>

using namespace std ;
#include "Row.h"
#include "optable.h"
#include "Line.h"
#include "parsing.h"
#include "validation.h"


//
// Created by HP on 23-Apr-18.
//


void Pass1();
void fillFileList();
list<Line> fillLine();
bool checkIfSymbolDefinedBefore(string symbol);
bool searchOPTABForOPCODE (string OPCODE);
string addHex(string hex1,string hex2);
string decimalToHex(int decimal);
int hexToDecimal(string hexa);
void printFileList();
static vector <Row> listFile ;
map<string,string> symTab;
optable opTab;
parsing parser;
validation validate;

int main() {


    opTab.setTable();
   list<Line> parsingList=parser.parisngFunction("D:\\megho\\passOne\\test.txt");
   int size = parsingList.size();


   //parser.printTheList(parsingList);

///   parser.printTheList(parsingList);
 validate.setParsinglist(parsingList);
  validate.validate();
  std::list<Row> test = validate.getValidationList();
  //cout << validate.getValidationList().size()<<endl;
  for(int i=0;i<validate.getValidationList().size();i++){
    //  cout << test.front().getLabel()<<" " <<test.front().getop_code()<<" "<<test.front().getOperand()<<" "<<test.front().getcomment()<<test.front().format<<" "<<test.front().errorMessge<<endl;
      listFile.push_back(test.front());
      test.pop_front();
     // cout<<listFile.at(i).getop_code();
  }



 // std::list<Line> test1 = parsingList;

//    fillFileList();
    Pass1();
    printFileList();
    return 0;
}
list<Line>fillLine(){
    list<Line> test;

    Line line ;
    line.setWord1("prog");
    line.setWord2("start");
    line.setWord3("1000");
    line.NumofwORD=3;
    test.push_back(line);

    line.setWord1("lda");
    line.setWord2("length");
    line.setWord3("null");
    line.NumofwORD=2;
    test.push_back(line);

    line.setWord1("+add");
    line.setWord2("length");
    line.setWord3("null");
    line.NumofwORD=2;
    test.push_back(line);

    line.setWord1("loop");
    line.setWord2("+sta");
    line.setWord3("null");
    line.NumofwORD=2;
    test.push_back(line);

    line.setWord1("lda");
    line.setWord2("lda");
    line.setWord3("null");
    line.NumofwORD=2;

    test.push_back(line);


    line.setWord1("addr");
    line.setWord2("length");
    line.setWord3("null");
    line.NumofwORD=2;
    test.push_back(line);

    line.setWord1("add");
    line.setWord2("+length");
    line.setWord3("null");
    line.setcomment("el comment aho ya ritaaaaa");
    line.NumofwORD=2;

    test.push_back(line);

    return test;

}

void printFileList() {
    cout<<"\n\n"<<endl;
    printf("%3s%10s%10s%10s%10s%10s\n","line","Address","Label","Opcode","Operands","Comment");
    for(int i=0;i<listFile.size();i++) {
        Row r=listFile.at(i);
        printf("%-7d",i);
        printf("%-12s",r.getAddress().c_str());
        if(r.getLabel() != "null" ){
            printf("%-9s",r.getLabel().c_str());
        }else{
            printf("%-9s","");
        }
        if(r.getop_code() != "null")
            printf("%-8s",r.getop_code().c_str());
        else
            printf("%-8s","");
        if(r.getOperand() != "null")
            printf("%-10s",r.getOperand().c_str());
        else
            printf("%-10s","");
        if(r.getcomment() != "null")
            printf("%s  ",r.getcomment().c_str());
        if(r.errorMessge!="") {
                printf("\n");
                printf("%20s%s","****Error:",r.errorMessge.c_str());
        }
        printf("\n");
    }
    printf("\n\n");
    printf("--------------------------------\n");
    printf("|%10s%s%8s|","","symbol Table","");
    printf("\n");
    printf("--------------------------------\n");
    printf("|%-16s|","Label");
    printf("%10s%4s","Address","|");
    printf("\n");
    printf("--------------------------------\n");
    for ( std::map< string, string >::const_iterator iter = symTab.begin();
            iter != symTab.end(); ++iter ){
        printf("|%-16s|",iter->first.c_str());
        printf("%10s%4s",iter->second.c_str(),"|");
        printf("\n");
        printf("--------------------------------\n");
    }
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

//    r.setLabel("null");
//    r.setop_code("end");
//    r.setOperand("first");
//    listFile.push_back(r);


}

void Pass1 () {
    string LOCCTR;
    int index = 0;
    string startAdr;
    Row row = listFile.at(index);
    if (row.getop_code().compare("start") == 0) {
        LOCCTR = row.getOperand();
        symTab.insert(pair<string, string>(row.getLabel(), LOCCTR));
        listFile.at(index).setAddress(LOCCTR);
        startAdr = LOCCTR;
        index++;
        row = listFile.at(index);
        if(row.getop_code().compare("equ")==0) {
            listFile.at(index).setAddress(row.getOperand());
        }else{
            listFile.at(index).setAddress(LOCCTR);
        }
    } else {
        LOCCTR = "0";
        listFile.at(index).setAddress("0");
    }

    while ((row.getop_code().compare("end") != 0) && (index < listFile.size()-1)) {
        //is not a comment line
        //cout<<row()<<endl;
        if (!row.hasError) {
            if (!row.isComment) {
                if (row.getLabel().compare("null") != 0) {
                    bool found = checkIfSymbolDefinedBefore(row.getLabel());//return true if exist
                    if (found) {
                        listFile.at(index).hasError = true;
                        listFile.at(index).errorMessge = "The Label already exists";
                        goto h;
                    } else {
                        if(row.getop_code().compare("equ")==0){
                            string label = row.getOperand();
                            int num = atoi(label.c_str());
                            stringstream str;
                            str << num;
                            if (str.str().size() == label.size()) {
                                symTab.insert(pair<string, string>(row.getLabel(), row.getOperand()));
                            } else if (symTab.count(label)) {
                                symTab.insert(pair<string, string>(row.getLabel(), symTab.at(label)));
                            } else {
                                listFile.at(index).hasError = true;
                                listFile.at(index).errorMessge = "Not defined label, may be forward ref";
                            }


                        }else {
                            symTab.insert(pair<string, string>(row.getLabel(), LOCCTR));
                        }
                    }
                }
                //search OPTAB for OPCODE
                if (searchOPTABForOPCODE(row.getop_code())&&opTab.opTable.at(row.getop_code())!="null") {
                    // increase location counter by length of the line (assume all 3)
                    stringstream str;
                    str << row.format;
                    LOCCTR = addHex(LOCCTR, str.str());
                } else if (row.getop_code().compare("word") == 0) {
                    // increase location counter by length of the word  (3 bytes)
                    LOCCTR = addHex(LOCCTR, "3");
                } else if (row.getop_code().compare("resw") == 0) {
                    // TODO add 3 * #[OPPERAND] to LOCCTR
                    LOCCTR = addHex(LOCCTR, decimalToHex(3 * atoi(row.getOperand().c_str())));
                } else if (row.getop_code().compare("resb") == 0) {
                    // TODO add #[OPERAND] to LOCCTR
                    LOCCTR = addHex(LOCCTR, decimalToHex(atoi(row.getOperand().c_str())));
                } else if (row.getop_code().compare("byte") == 0) {
                    char ch = row.getOperand().at(0);
                    switch (ch) {
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
                                listFile.at(index).hasError = true;
                                listFile.at(index).errorMessge = "The hexidecimal value has an odd numbers of digits";
                            }
                        }
                            break;
                    }

                } else {
                    listFile.at(index).hasError = true;
                    listFile.at(index).errorMessge = "Invalid op-code";
                }
            }

    h:        index++;
            row = listFile.at(index);
            if (row.getop_code().compare("equ") == 0) {
                LOCCTR=addHex(LOCCTR,"-3");
                string label = row.getOperand();
                int num = atoi(label.c_str());
                stringstream str;
                str << num;
                if (str.str().size() == label.size()) {
                    listFile.at(index).setAddress(label);
                } else if (symTab.count(label)) {
                    listFile.at(index).setAddress(symTab.at(label));
                } else {
                    listFile.at(index).hasError = true;
                    listFile.at(index).errorMessge = "Not defined label, may be forward ref";
                }
            } else if (row.getop_code().compare("org") == 0) {
                string label = row.getOperand();
                int num = atoi(label.c_str());
                stringstream str;
                str << num;
                if (str.str().size() == label.size()) {
                    LOCCTR = row.getOperand();
                    index++;
                    listFile.at(index).setAddress(LOCCTR);
                } else if (symTab.count(label)) {
                    LOCCTR = symTab.at(label);
                    index++;
                    listFile.at(index).setAddress(LOCCTR);
                } else {
                    LOCCTR=addHex(LOCCTR,"-3");
                    listFile.at(index).hasError = true;
                    listFile.at(index).errorMessge = "Not defined label, may be forward ref";
                }
            } else {
                listFile.at(index).setAddress(LOCCTR);
            }

        }else{
            index++;
            row = listFile.at(index);
            listFile.at(index).setAddress(LOCCTR);
        }
    }


        if (listFile.at(listFile.size()-1).getop_code().compare("end")!=0) {
            Row r;
            r.hasError = true;
            r.errorMessge = "NO End Statement";
            listFile.push_back(r);

        }

        // TODO write last line to intermediate file
        // TODO save (LOCCTR - Starting address) as program length
        stringstream s;
        s << -1 * atoi(startAdr.c_str());
        string progLength = addHex(LOCCTR, s.str());

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