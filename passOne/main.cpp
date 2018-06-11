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
string subHex(string hex1,string hex2);
string mulHex(string hex1,string hex2);
string divHex(string hex1,string hex2);
string decimalToHex(int decimal);
int hexToDecimal(string hexa);
void printFileList();
static vector <Row> listFile ;
map<string,string> symTab;
map<string,string> TypeTable;
vector<litLine> litTab;
optable opTab;
parsing parser;
validation validate;
Pass2 pass2;
string partOfExpression ;
Row calculateExpression(Row row);

int main(int argc,char* argv[]) {


    opTab.setTable();
    list<Line> parsingList=parser.parisngFunction(argv[1]);
    int size = parsingList.size();

    validate.setParsinglist(parsingList);
    validate.validate();

    std::list<Row> test = validate.getValidationList();
    for(int i=0;i<validate.getValidationList().size();i++){
        listFile.push_back(test.front());
        test.pop_front();

    }



    Pass1();
    printFileList();

    // test pass2
    pass2.pass2Algoritm(listFile,symTab,litTab,TypeTable);

    return 0;
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

void Pass1 () {
    string LOCCTR;
    int index = 0;
    string startAdr;
    Row row = listFile.at(index);
    if (row.getop_code().compare("start") == 0) {
        LOCCTR = row.getOperand();
        symTab.insert(pair<string, string>(row.getLabel(), LOCCTR));
        TypeTable.insert(pair<string, string>(row.getLabel(), "r"));
        listFile.at(index).setAddress(LOCCTR);
        startAdr = LOCCTR;
        index++;
        row = listFile.at(index);
        if(row.getop_code().compare("equ")==0) {
            if(row.hasError){
                listFile.at(index).hasError=true;
                listFile.at(index).errorMessge=row.errorMessge;
                goto h;
            }
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
                            cout<<"index "<<index<<endl;
                            cout<<row.getLabel()<<row.hasError<<" expressio"<<endl;
                            if(row.hasError){
                                listFile.at(index).hasError=true;
                                listFile.at(index).errorMessge=row.errorMessge;
                                goto h;
                            }
                            string label = row.getOperand();
                            int num = atoi(label.c_str());
                            stringstream str;
                            str << num;
                            if (str.str().size() == label.size()) {
                                symTab.insert(pair<string, string>(row.getLabel(), decimalToHex(num)));
                                TypeTable.insert(pair<string, string>(row.getLabel(), "r"));

                            } else if (symTab.count(label)) {
                                symTab.insert(pair<string, string>(row.getLabel(), symTab.at(label)));
                                TypeTable.insert(pair<string, string>(row.getLabel(), "r"));

                            } else {
                                listFile.at(index).hasError = true;
                                listFile.at(index).errorMessge = "Not defined label, may be forward ref";
                            }


                        } else {
                         //   cout << row.getLabel()<<"   anaaa"<<endl;
                            symTab.insert(pair<string, string>(row.getLabel(), LOCCTR));
                            TypeTable.insert(pair<string, string>(row.getLabel(), "r"));

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
                            LOCCTR = addHex(LOCCTR, decimalToHex(atoi(str.str().c_str())));
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
                    if(listFile.at(index).getOperand().at(1)=='c'||listFile.at(index).getOperand().at(1)=='C'){
                        line.setLength(decimalToHex(listFile.at(index).getOperand().size()-4));
                        string str=listFile.at(index).getOperand();
                        string hexStr="";
                        for(std::string::size_type i = 3; i < str.size()-1; ++i) {
                            hexStr+=decimalToHex(int(str[i]));
                        }
                        line.setValue(hexStr);
                    }else if (listFile.at(index).getOperand().at(1)=='x'||listFile.at(index).getOperand().at(1)=='X'){
                        if(((listFile.at(index).getOperand().size() - 4) % 2) == 0) {
                            line.setLength(decimalToHex((listFile.at(index).getOperand().size()-4)/2));
                            string str = listFile.at(index).getOperand().substr(3,hexToDecimal(line.getLength())*2);
                            line.setValue(str);
                        } else{
                            listFile.at(index).hasError = true;
                            listFile.at(index).errorMessge = "The hexidecimal value has an odd numbers of digits";
                        }
                    }else if(listFile.at(index).getOperand().at(1)=='w'||listFile.at(index).getOperand().at(1)=='W'){
                        line.setLength(decimalToHex((listFile.at(index).getOperand().size()-4)*3));
                        string str = listFile.at(index).getOperand().substr(3,listFile.at(index).getOperand().size()-4);
                        line.setValue(str);
                    }else{
                        listFile.at(index).hasError=true;
                        listFile.at(index).errorMessge="The literal is not defined";
                    }
                    if(!checkIfLiteralDefinedBefore(line.getValue())){
                        litTab.push_back(line);
                    }
                }
            }

            h:        index++;
            row = listFile.at(index);

            if (row.getop_code().compare("equ") == 0) {


                if(row.format!=4){
                    LOCCTR = addHex(LOCCTR, "-3");
                    if(row.isExpression){
                        row=calculateExpression(row);
                        if(row.hasError){
                            listFile.at(index).hasError=true;
                            listFile.at(index).errorMessge=row.errorMessge;
                        }
                        stringstream str;
                        str << hexToDecimal(row.getOperand());
                        listFile.at(index).setOperand(str.str());
                        row=listFile.at(index);
                    }
                    string label = row.getOperand();
                    int num = atoi(label.c_str());
                    stringstream str;
                    str << num;
                    if (str.str().size() == label.size()) {
                        listFile.at(index).setAddress(decimalToHex(num));
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
cout<<"org  "<<row.getLabel()<<endl;
                if(row.format!=4){
                    if(row.isExpression){
                        row=calculateExpression(row);
                        if(row.hasError){
                            listFile.at(index).hasError=true;
                            listFile.at(index).errorMessge=row.errorMessge;
                        }
                        stringstream str;
                        str << hexToDecimal(row.getOperand());
                        listFile.at(index).setOperand(str.str());
                        row=listFile.at(index);
                    }

                    string label = row.getOperand();
                    int num = atoi(label.c_str());
                    stringstream str;
                    str << num;
                    if (str.str().size() == label.size()) {
                        LOCCTR = decimalToHex(num);
                        index++;
                        listFile.at(index).setAddress(LOCCTR);
                        row = listFile.at(index);
                        string str;          //The string
                        ostringstream temp;  //temp as in temporary
                        temp<<num;
                        str=temp.str();
                        Row lastRow = listFile.at(index-1);
                        symTab.insert(pair<string, string>(lastRow.getLabel(),str));
                        TypeTable.insert(pair<string, string>(lastRow.getLabel(), "a"));

                    } else if (symTab.count(label)) {
                        LOCCTR = symTab.at(label);
                        index++;
                        listFile.at(index).setAddress(LOCCTR);
                        row = listFile.at(index);
                        Row lastRow = listFile.at(index-1);
                        symTab.insert(pair<string, string>(lastRow.getLabel(),LOCCTR));
                        TypeTable.insert(pair<string, string>(lastRow.getLabel(), "r"));
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
            goto h;
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

Row calculateExpression(Row row) {

    string expression = row.getOperand();

    vector<string>expressionList;
    int counter =0;
    int substringStart=0;
    while (counter < expression.length()){

        if(expression.at(counter) == '*' || expression.at(counter) == '+' || expression.at(counter) == '/' || expression.at(counter) == '-' ) {

            int length = counter-substringStart;
            partOfExpression = expression.substr(substringStart, length);

            if (symTab.find(partOfExpression) == symTab.end()) {
                bool flag = false;
                for(int j=0;j<partOfExpression.length();j++){
                    if(isalpha(partOfExpression.at(j))){
                        flag = true;
                        break;
                    }

                }
                if(flag){
                    row.hasError = true;
                    row.errorMessge = "expression has un defined label ";
                    return row;

                } else{
                    int num = atoi( partOfExpression.c_str());
                    string hexNum = decimalToHex(num);
                    expressionList.push_back(hexNum);

                    expressionList.push_back(expression.substr(counter,1));

                    TypeTable.insert(pair<string, string>(hexNum, "Na"));
                    substringStart = counter + 1;

                }
            } else {

                expressionList.push_back(expression.substr(substringStart, counter-substringStart ));
                expressionList.push_back(expression.substr(counter,1));
                substringStart = counter + 1;
            }

        }
        counter++;
        if(counter == expression.length()){
            partOfExpression = expression.substr(substringStart, counter-substringStart);
            if (symTab.find(partOfExpression) == symTab.end()) {
                bool flag = false;
                string temp =partOfExpression;
                for(int j=0;j<temp.length();j++){
                    if(isalpha(temp.at(j))){
                        flag = true;
                        break;
                    }

                }
                if(flag){
                    row.hasError = true;
                    row.errorMessge = "expression has un defined label ";
                    return row;
                    break;} else{
                    int num = atoi( expression.substr(substringStart, counter-substringStart).c_str());
                    string hexNum = decimalToHex(num);
                    expressionList.push_back(hexNum);

                    TypeTable.insert(pair<string, string>(hexNum, "Na"));

                }
            } else {
                expressionList.push_back(expression.substr(substringStart, counter-substringStart));
            }

        }

    }


    if(expressionList.size()<3){
        for(int ii=0;ii<expressionList.size();ii++){
        //    cout<< expressionList.at(ii)<<" ";
        }
        row.hasError = true;
        row.errorMessge = "expression  syntax error ";
        return row;

    } else {
        // cout << TypeTable.at(expressionList.back());

        for(int i=0; i <expressionList.size();i++) {

            if(expressionList.at(i)=="*" || expressionList.at(i)=="/" ){

                if(TypeTable.at(expressionList.at(i-1)) == "r" || TypeTable.at(expressionList.at(i+1)) == "r" ||
                   TypeTable.at(expressionList.at(i-1)) == "Nr"||TypeTable.at(expressionList.at(i+1)) == "Nr")
                {
                    row.errorMessge = " Relative don't use * or /  operations";
                    row.hasError = true;
                    return row;


                }else{

                    string num1 ="";
                    string num2 = "";
                    if(TypeTable.at(expressionList.at(i-1))=="Na"){
                        num1 =expressionList.at(i-1);

                    } else {
                        num1 = symTab.at(expressionList.at(i-1));

                    }
                    if(TypeTable.at(expressionList.at(i+1))=="Na"){
                        num2 = expressionList.at(i+1);
                    } else {
                        num2 = symTab.at(expressionList.at(i+1));

                    }

                    if(expressionList.at(i)=="*"){


                        expressionList.at(i-1)=mulHex(num1,num2);
                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Na"));
                        expressionList.erase(expressionList.begin()+i);
                        expressionList.erase(expressionList.begin()+i);
                        i=0;

                    } else{

                        expressionList.at(i-1)=divHex(num1,num2);
                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Na"));
                        expressionList.erase(expressionList.begin()+i);
                        expressionList.erase(expressionList.begin()+i);
                        i=0;
                    }

                }





            }


            if(expressionList.size()==1){
                row.setAddress(expressionList.at(0));
                string type = "";
                if(TypeTable.at(expressionList.at(0))=="Na"){
                    type = "a";
                } else{
                    type = "r";
                }
                //         symTab.insert(pair<string, string>(row.getLabel(),expressionList.at(0) ));
                TypeTable.insert(pair<string, string>(row.getLabel(),type));
                row.setOperand(expressionList.at(0));
                //TypeTable.at(row.getLabel())=TypeTable.at(expressionList.at(0));
                return row;

            }

        }







        for(int i=0 ; i < expressionList.size();i++){

            if(expressionList.at(i)=="+"){

                if((TypeTable.at(expressionList.at(i-1)) == "r" && TypeTable.at(expressionList.at(i+1)) == "r") ||
                   (TypeTable.at(expressionList.at(i-1)) == "Nr" && TypeTable.at(expressionList.at(i+1)) == "Nr")||
                   (TypeTable.at(expressionList.at(i-1)) == "r" && TypeTable.at(expressionList.at(i+1)) == "Nr" ||
                    (TypeTable.at(expressionList.at(i-1)) == "Nr" && TypeTable.at(expressionList.at(i+1)) == "r")
                   )){

                    row.hasError = true;
                    row.errorMessge = "relative + relative is invalid expression";
                    return row;
                }else{

                    string num1 ="";
                    string num2 = "";
                    if(TypeTable.at(expressionList.at(i-1))=="Na" ||TypeTable.at(expressionList.at(i-1))=="Nr"){
                        num1 =expressionList.at(i-1);
                    } else {
                        num1 = symTab.at(expressionList.at(i-1));

                    }
                    if(TypeTable.at(expressionList.at(i+1))=="Na" ||TypeTable.at(expressionList.at(i+1))=="Nr"){
                        num2 = expressionList.at(i+1);
                    } else {
                        num2 = symTab.at(expressionList.at(i+1));

                    }

                    if(TypeTable.at(expressionList.at(i-1)).find('r') ||TypeTable.at(expressionList.at(i+1)).find('r') ){

                        expressionList.at(i-1)=addHex(num1,num2);

                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Nr"));

                    } else{
                        expressionList.at(i-1)= addHex(num1,num2);

                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Na"));

                    }
                    expressionList.erase(expressionList.begin()+i);
                    expressionList.erase(expressionList.begin()+i);
                    i=0;


                }



            }


            if(expressionList.at(i)=="-"){

                if((TypeTable.at(expressionList.at(i-1)) == "a" && TypeTable.at(expressionList.at(i+1)) == "r") ||
                   (TypeTable.at(expressionList.at(i-1)) == "Na" && TypeTable.at(expressionList.at(i+1)) == "Nr")||
                   (TypeTable.at(expressionList.at(i-1)) == "a" && TypeTable.at(expressionList.at(i+1)) == "Nr" ||
                    (TypeTable.at(expressionList.at(i-1)) == "Na" && TypeTable.at(expressionList.at(i+1)) == "r")
                   )){

                    row.hasError = true;
                    // cout<< "e7m" << TypeTable.at(expressionList.at(i-1)) <<" " << expressionList.at(i-1) ;
                    row.errorMessge = "absolute - relative  is invalid expression";
                    return row;

                }else{

                    string num1 ="";
                    string num2 = "";

                    if(TypeTable.at(expressionList.at(i-1))=="Na" ||TypeTable.at(expressionList.at(i-1))=="Nr"){
                        num1 =expressionList.at(i-1);
                    } else {
                        num1 = symTab.at(expressionList.at(i-1));

                    }
                    if(TypeTable.at(expressionList.at(i+1))=="Na" ||TypeTable.at(expressionList.at(i+1))=="Nr"){
                        num2 = expressionList.at(i+1);
                    } else {
                        num2 = symTab.at(expressionList.at(i+1));

                    }


                    if((TypeTable.at(expressionList.at(i-1))=="r" && TypeTable.at(expressionList.at(i+1))=="r" ) ||
                       (TypeTable.at(expressionList.at(i-1))=="Nr" && TypeTable.at(expressionList.at(i+1))=="r" )||
                       (TypeTable.at(expressionList.at(i-1))=="r" && TypeTable.at(expressionList.at(i+1))=="Nr" )||
                       (TypeTable.at(expressionList.at(i-1))=="Nr" && TypeTable.at(expressionList.at(i+1))=="Nr" )){

                        expressionList.at(i-1)=subHex(num1,num2);
                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Na"));

                    } else if((TypeTable.at(expressionList.at(i-1)).find('r') || TypeTable.at(expressionList.at(i+1)).find('r')) ){

                        expressionList.at(i-1)=subHex(num1,num2);
                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Nr"));

                    }else{
                        expressionList.at(i-1)=subHex(num1,num2);
                        TypeTable.insert(pair<string, string>(expressionList.at(i-1), "Na"));

                    }
                    expressionList.erase(expressionList.begin()+i);
                    expressionList.erase(expressionList.begin()+i);
                    i=0;



                }



            }






        }
    }



    if(expressionList.size()==1){
        row.setAddress(expressionList.at(0));
        string type = "";
        if(TypeTable.at(expressionList.at(0))=="Na"){
            type = "a";
        } else{
            type = "r";
        }
        //symTab.insert(pair<string, string>(row.getLabel(),expressionList.at(0) ));
        TypeTable.insert(pair<string, string>(row.getLabel(),type));
        row.setOperand(expressionList.at(0));
        //TypeTable.at(row.getLabel())=TypeTable.at(expressionList.at(0));


    }
    return row;
}

string subHex(string hex1,string hex2){
    return decimalToHex(abs(hexToDecimal(hex1)-hexToDecimal(hex2)));
}
string mulHex(string hex1,string hex2){
    return decimalToHex(hexToDecimal(hex1)*hexToDecimal(hex2));
}
string divHex(string hex1,string hex2){
    return decimalToHex(hexToDecimal(hex1)/hexToDecimal(hex2));
}
