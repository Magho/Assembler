//
// Created by king on 4/26/2018.
//

#include "validation.h"
#include "Row.h"
#include "optable.h"



void validation ::setParsinglist(list<Line>list1)  {

    TheParsinglist = list1;
}


void validation ::validate() {


    for (int i = 0; i < TheParsinglist.size(); i++) {

        Row row;
        optable opT;
        Line line = TheParsinglist.front();
        TheParsinglist.pop_front();


        // first check if it's a comment line
        if (line.isComment) {

            row.isComment = true;

        }

        else if(line.NumofwORD == 1){

            if (opT.opTable.find(line.getWord1()) == opT.opTable.end()) {
                row.errorMessge =" No op_code is exist";
            } else {
                // found
                row.setop_code(line.getWord1());
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



