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
#include "litLine.h"
#include "optable.h"
#include "Line.h"
#include "parsing.h"
#include "validation.h"
#include "Pass2.h"


//
// Created by HP on 23-Apr-18.
//


void Pass1();
void fillFileList();
list<Line> fillLine();
bool checkIfSymbolDefinedBefore(string symbol);
bool checkIfLiteralDefinedBefore(string litValue);
bool searchOPTABForOPCODE (string OPCODE);
string addHex(string hex1,string hex2);
string decimalToHex(int decimal);
int hexToDecimal(string hexa);
void printFileList();
static vector <Row> listFile ;
map<string,string> symTab;
vector<litLine> litTab;
optable opTab;
parsing parser;
validation validate;
Pass2 pass2;

int main() {


    opTab.setTable();
   list<Line> parsingList=parser.parisngFunction("D:\\Assembler\\passOne\\test.txt");
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

    // test pass2
    pass2.test(listFile);

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
    FILE *ptr;
    ptr = fopen("pass1_Output.txt","w");
    fprintf(ptr,"%3s%10s%10s%10s%10s%10s\n","line","Address","Label","Opcode","Operands","Comment");

    printf("%3s%10s%10s%10s%10s%10s\n","line","Address","Label","Opcode","Operands","Comment");
    for(int i=0;i<listFile.size();i++) {
        Row r=listFile.at(i);
        printf("%-7d",i);
        fprintf(ptr,"%-7d",i);

        printf("%-12s",r.getAddress().c_str());
        fprintf(ptr,"%-12s",r.getAddress().c_str());

        if(r.getLabel() != "null" ){
            printf("%-9s",r.getLabel().c_str());
            fprintf(ptr,"%-9s",r.getLabel().c_str());
        }else{
            printf("%-9s","");
            fprintf(ptr,"%-9s","");
        }

        if(r.getop_code() != "null"){
            printf("%-8s",r.getop_code().c_str());
            fprintf(ptr,"%-8s",r.getop_code().c_str());
        }else{
            printf("%-8s","");
            fprintf(ptr,"%-8s","");
        }
        if(r.getOperand() != "null"){
            printf("%-10s",r.getOperand().c_str());
            fprintf(ptr,"%-10s",r.getOperand().c_str());
        }else{
            printf("%-10s","");
            fprintf(ptr,"%-10s","");
        }
        if(r.getcomment() != "null"){
            printf("%s  ",r.getcomment().c_str());
            fprintf(ptr,"%s  ",r.getcomment().c_str());
        }
        if(r.errorMessge!="") {
                printf("\n");
                printf("%20s%s","****Error:",r.errorMessge.c_str());
                fprintf(ptr,"\n%20s%s","****Error:",r.errorMessge.c_str());
        }
        printf("\n");
        fprintf(ptr,"\n");
    }
    printf("\n\n");
    printf("--------------------------------\n");
    fprintf(ptr,"\n\n--------------------------------\n");

    printf("|%10s%s%8s|","","symbol Table","");
    fprintf(ptr,"|%10s%s%8s|","","symbol Table","");

    printf("\n");
    printf("--------------------------------\n");
    fprintf(ptr,"\n--------------------------------\n");

    printf("|%-16s|","Label");
    fprintf(ptr,"|%-16s|","Label");
    printf("%10s%4s","Address","|");
    fprintf(ptr,"%10s%4s","Address","|");

    printf("\n");
    printf("--------------------------------\n");
    fprintf(ptr,"\n--------------------------------\n");
    for ( std::map< string, string >::const_iterator iter = symTab.begin();
            iter != symTab.end(); ++iter ){
        printf("|%-16s|",iter->first.c_str());
        fprintf(ptr,"|%-16s|",iter->first.c_str());

        printf("%10s%4s",iter->second.c_str(),"|");
        fprintf(ptr,"%10s%4s",iter->second.c_str(),"|");

        printf("\n");
        printf("--------------------------------\n");
        fprintf(ptr,"\n--------------------------------\n");
    }
    fclose(ptr);
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
                        if (row.getop_code().compare("equ") == 0) {
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


                        } else {
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

                }else if (row.getop_code().compare("base")==0){
                    goto h;

                } else if (row.getop_code().compare("ltorg")==0){

                    for(int i=0;i<litTab.size();i++){
                        litTab.at(i).setAddress(LOCCTR);
                        Row row;
                        row.setAddress(LOCCTR);
                        row.setop_code(litTab.at(i).getLiteral());
                        row.setOperand(litTab.at(i).getValue());
                        listFile.insert(listFile.begin() + (index+1), row);
                        LOCCTR=addHex(LOCCTR,litTab.at(i).getLength());
                        index++;
                    }

                }else {
                    listFile.at(index).hasError = true;
                    listFile.at(index).errorMessge = "Invalid op-code";
                }
                //literals
                if(listFile.at(index).getOperand().at(0)=='='){
                    litLine line ;
                    line.setLiteral(listFile.at(index).getOperand());
                    //set Length and value of literal
                    if(listFile.at(index).getOperand().at(1)=='c'){
                        line.setLength(decimalToHex(listFile.at(index).getOperand().size()-4));
                        string str=listFile.at(index).getOperand();
                        string hexStr="";
                        for(std::string::size_type i = 3; i < str.size()-1; ++i) {
                            hexStr+=decimalToHex(int(str[i]));
                        }
                        line.setValue(hexStr);
                    }else if (listFile.at(index).getOperand().at(1)=='x'){
                        if(((listFile.at(index).getOperand().size() - 4) % 2) == 0) {
                            line.setLength(decimalToHex((listFile.at(index).getOperand().size()-4)/2));
                            string str = listFile.at(index).getOperand().substr(3,hexToDecimal(line.getLength())*2);
                            line.setValue(str);
                        } else{
                            listFile.at(index).hasError = true;
                            listFile.at(index).errorMessge = "The hexidecimal value has an odd numbers of digits";
                        }
                    }
                    if(!checkIfLiteralDefinedBefore(line.getValue())){
                        litTab.push_back(line);
                        cout<<"literalssss"<<litTab.at(0).getLength();
                    }
                }
            }

    h:        index++;
            row = listFile.at(index);
            if (row.getop_code().compare("equ") == 0) {
                if(row.format!=4){
                LOCCTR = addHex(LOCCTR, "-3");
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
            }else {
                    listFile.at(index).hasError=true;
                    listFile.at(index).errorMessge="+ before equ";
                    LOCCTR = addHex(LOCCTR, "-4");
            }
            } else if (row.getop_code().compare("org") == 0) {
                if(row.format!=4){
                string label = row.getOperand();
                int num = atoi(label.c_str());
                stringstream str;
                str << num;
                if (str.str().size() == label.size()) {
                    LOCCTR = row.getOperand();
                    index++;
                    listFile.at(index).setAddress(LOCCTR);
                    row = listFile.at(index);

                } else if (symTab.count(label)) {
                    LOCCTR = symTab.at(label);
                    index++;
                    listFile.at(index).setAddress(LOCCTR);
                    row = listFile.at(index);
                } else {
                    LOCCTR=addHex(LOCCTR,"-3");
                    listFile.at(index).hasError = true;
                    listFile.at(index).errorMessge = "Not defined label, may be forward ref";
                }
                }else {
                    listFile.at(index).hasError=true;
                    listFile.at(index).errorMessge="+ before org";
                    LOCCTR = addHex(LOCCTR, "-4");
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

        }else {

            for(int i=0;i<litTab.size();i++){
                if(litTab.at(i).getAddress().compare("null")==0){
                    litTab.at(i).setAddress(LOCCTR);
                    Row row;
                    row.setAddress(LOCCTR);
                    row.setop_code(litTab.at(i).getLiteral());
                    row.setOperand(litTab.at(i).getValue());
                    listFile.push_back(row);
                    LOCCTR=addHex(LOCCTR,litTab.at(i).getLength());
                }
            }

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
bool checkIfLiteralDefinedBefore(string litValue) {
    for(int i=0;i<litTab.size();i++){
        if(litTab.at(i).getValue().compare(litValue)==0){
            return true;
        }
    }
    return false;
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