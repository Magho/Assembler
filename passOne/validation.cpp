//
// Created by king on 4/26/2018.
//

#include <iostream>
#include "validation.h"
#include "Row.h"
#include "optable.h"



void validation ::setParsinglist(list<Line>list1)  {

    TheParsinglist = list1;
}
list<Row> validation ::getValidationList() {
    return validationRows;
}


void validation ::validate() {

int size = TheParsinglist.size();

    for (int i = 0; i < size; i++) {

        Row row;
        optable opT;
        opT.setTable();
        Line line = TheParsinglist.back();
        TheParsinglist.pop_back();
        // first check if it's a comment line

      // cout<< line.getWord1()<<" "<<line.getWord2()<<" " <<line.getWord3()<<line.NumofwORD<<endl;

        int counter =0;
        if(line.getWord1().length()>0&&line.getWord1().at(0)=='+'){
            counter ++;
            std::string temp = line.getWord1().substr(1,line.getWord1().length());
            if (opT.opTable.find(temp) == opT.opTable.end()){
                row.errorMessge="un correct format";
                row.hasError= true;

            }else{
                row.format = 4;
                line.setWord1(temp);
            }

        }
        if(line.getWord2().length()>0&&line.getWord2().at(0)=='+'){
            counter ++;

            std::string temp = line.getWord2().substr(1,line.getWord2().length());
            if (opT.opTable.find(temp) == opT.opTable.end()){
                row.errorMessge="un correct format";
                row.hasError= true;

            }else{
                row.format = 4;
                line.setWord2(temp);
            }

        }
        if(line.getWord3().length()>0&&line.getWord3().at(0)=='+'){
            counter ++;
            std::string temp = line.getWord3().substr(1,line.getWord3().length());
            if (opT.opTable.find(temp) == opT.opTable.end()){
                row.errorMessge="un correct format";
                row.hasError= true;


            }else{
                row.format = 4;
                line.setWord3(temp);
            }

        }

        if (line.isComment) {
            row.isComment = true;
            row.setcomment(line.getcomment());

        }



        else if(line.NumofwORD == 1){

            if (opT.opTable.find(line.getWord1()) == opT.opTable.end()) {
                row.errorMessge =" No op_code is exist";
                row.hasError= true;

            } else {
                // found
                if(row.getop_code().compare("null")==0) {
                    row.setop_code(line.getWord1());
                    string temp = line.getWord1();
                    if (opT.opTable.at(temp).at(opT.opTable.at(temp).length() - 1) == '2') {
                        row.format = 2;
                    }
                }else{
                    row.hasError=true;
                    row.errorMessge="syntax error : repeated op_code ";
                    row.hasError= true;

                }

                if(line.getcomment()!= "null"){
                    row.setcomment(line.getcomment());
                    }
                validationRows.push_back(row);

            }



            } else if (line.NumofwORD == 2 ){


            if (opT.opTable.find(line.getWord1()) == opT.opTable.end()) {


                /* start condition if second word is op_code or error */

                if (opT.opTable.find(line.getWord2()) == opT.opTable.end()) {
                    row.errorMessge =" No op_code is exist";
                    row.hasError= true;

                } else {
                    // found
                    if(row.getop_code().compare("null")==0) {
                        row.setop_code(line.getWord2());
                        string temp = line.getWord2();
                        if (opT.opTable.at(temp).at(opT.opTable.at(temp).length() - 1) == '2') {
                            row.format = 2;
                        }
                    }else{
                        row.hasError=true;
                        row.errorMessge="syntax error : repeated op_code ";
                    }
                    row.setLabel(line.getWord1());
                    if(line.getcomment()!= "null"){
                        row.setcomment(line.getcomment());
                    }
                    validationRows.push_back(row);

                }

                /* end of the condition */
            } else {
                // found
                if(row.getop_code().compare("null")==0) {
                    row.setop_code(line.getWord1());
                    string temp = line.getWord1();
                    if (opT.opTable.at(temp).at(opT.opTable.at(temp).length()  - 1) == '2') {
                        row.format = 2;
                    }
                }else{
                    row.hasError=true;
                    row.errorMessge="syntax error : repeated op_code ";
                }

                if (opT.opTable.find(line.getWord2()) == opT.opTable.end()){
                row.setOperand(line.getWord2());} else{

                    row.errorMessge = "syntax error  repeated opcode";
                }



                if(line.getcomment()!= "null"){
                    row.setcomment(line.getcomment());
                }
                validationRows.push_back(row);

            }

        }else if (line.NumofwORD == 3){
            cout<<endl;
            cout << line.getWord1()<<" "<<"testtesttestets"<<endl;
            if (opT.opTable.find(line.getWord2()) == opT.opTable.end()) {
                row.errorMessge =" No op_code is exist or in a wrong position";
                row.hasError= true;

            } else {

                // found
                if(row.getop_code().compare("null")==0) {
                    row.setop_code(line.getWord2());
                    string temp = line.getWord2();
                    if (opT.opTable.at(temp).at(opT.opTable.at(temp).length() - 1) == '2') {
                        row.format = 2;
                    }
                }else{
                    row.hasError=true;
                    row.errorMessge="syntax error : repeated op_code ";
                }


                row.setLabel(line.getWord1());



                row.setOperand(line.getWord3());
                if(line.getcomment()!= "null"){
                    row.setcomment(line.getcomment());
                }
                validationRows.push_back(row);

            }


        }


    }
            // second  check if there is only one word so if it's not an op_code there is an error here
       /* else if (temp.size() == 1) {

            if (opT.opTable.find(temp.at("word1")) == opT.opTable.end()) {
                // not found
//                row.setErrorMessage(" No op_code is exist");
            } else {
                // found
                row.setop_code(temp.at("word1"));
                validationRows.push_back(row);

            }



//third check if size is 2 so if not one of them is op_code there is error
//so it will be on of three (label,op),(op,operand),(operand,comment) and the last one is an error

        } else if (temp.size() == 2) {

            // first(third) check is op is the firsr word

            if (opT.opTable.find(temp.at("word1")) != opT.opTable.end()) {
                // found
                row.setop_code(temp.at("word1"));

                if (temp.find("word2") != temp.end()) {
                    row.setOperand(temp.at("word2"));
                }else{   row.setcomment(temp.at("comment")); }


            }
 // second(third) check if op_code is the second word
        else if (opT.opTable.find(temp.at("word2")) != opT.opTable.end()){

                // found
                row.setLabel(temp.at("word1"));
                row.setop_code(temp.at("word2"));


        }
        // if not case of the above then there is error
        else {

//                row.setErrorMessage("undefined op_code field");

            }

            // Fourth if size = 3 so there is 2 possible cases
            // (label,op,operand)
            } else if(temp.size() == 3){

            if (opT.opTable.find(temp.at("word1")) != opT.opTable.end()) {
                // found
                row.setop_code(temp.at("word1"));
                row.setOperand(temp.at("word2"));
                row.setcomment(temp.at("comment"));

            }
                // second(Fourth) check if op_code is the second word
            else if (opT.opTable.find(temp.at("word2")) != opT.opTable.end()){

                // found
                row.setLabel(temp.at("word1"));
                row.setop_code(temp.at("word2"));
                if (temp.find("word3") != temp.end()){
                    row.setOperand(temp.at("word3"));

                } else {row.setcomment(temp.at("comment"));}

            }




        } else if (temp.size() ==4){

            if (opT.opTable.find(temp.at("word2")) != opT.opTable.end()){

                row.setLabel(temp.at("word1"));
                row.setop_code(temp.at("word2"));
                row.setOperand(temp.at("word3"));
                row.setcomment(temp.at("comment"));



            }else{

//                row.setErrorMessage("undefined op_code");
            }



        }
        validationRows.push_back(row);


    }

*/    }



