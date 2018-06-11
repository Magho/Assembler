    //
    // Created by king on 4/26/2018.
    //

    #include <iostream>
    #include <algorithm>
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

            if(line.getWord1().find("=") != std::string::npos || line.getWord1().find("/'") != std::string::npos){

            }else{
                std :: string str = line.getWord1() ;

                std::transform(str.begin(), str.end(),str.begin(), ::tolower);
                line.setWord1(str);

            }
            if(line.getWord2().find("=") != std::string::npos || line.getWord2().find("/'") != std::string::npos){

            }else{

                std :: string str = line.getWord2() ;

                std::transform(str.begin(), str.end(),str.begin(), ::tolower);
    line.setWord2(str);
            }
            if(line.getWord3().find("=") != std::string::npos || line.getWord3().find("'") != std::string::npos){

            }else{

                std :: string str = line.getWord3() ;

                std::transform(str.begin(), str.end(),str.begin(), ::tolower);
                line.setWord3(str);

            }




            TheParsinglist.pop_back();
            if (line.isMoreThanFourWords){
                row.errorMessge = " more than the availaple words";
                row.hasError = true;
            }
            if(    bool isEmptyLine = false){

                row.errorMessge = " empty line";
                row.hasError = true;
            }


            if(line.islabelStartWithNoChar){
                row.errorMessge = "labelStartWithNoChar";
                row.hasError = true;

            }

            // cout<<line.NumofwORD <<"num"<<endl;

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
                        if (opT.opTable.at(line.getWord1()).at(opT.opTable.at(line.getWord1()).length() - 1) == '1'||row.getop_code()=="ltorg" ||row.getop_code()=="rsub"  ) {
                            if(row.getop_code()=="rsub"){
                                row.format=3;
                            }else{
                                row.format = 1;}
                            row.setop_code(line.getWord1());
                        } else if ( line.getWord1()!= "end"){
                            row.hasError=true;
                            row.errorMessge="syntax error : this op code should have operand";
                        }

                    }else{
                        row.hasError=true;
                        row.errorMessge="syntax error : repeated op_code ";


                    }

                    if(line.getcomment()!= "null"){
                        row.setcomment(line.getcomment());
                    }

                }

                validationRows.push_back(row);


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
                            if (opT.opTable.at(temp).at(opT.opTable.at(temp).length() - 1) == '1' || line.getWord2()=="end") {
                                row.format = 1;

                            }else{

                                row.hasError=true;
                                row.errorMessge="syntax error : this opcode should have operand it's not format 1 ";
                            }



                        }else{
                            row.hasError=true;
                            row.errorMessge="syntax error : repeated op_code ";
                            //   validationRows.push_back(row);

                        }
                        row.setLabel(line.getWord1());
                        if(line.getcomment()!= "null"){
                            row.setcomment(line.getcomment());
                        }
                        //  validationRows.push_back(row);

                    }

                    /* end of the condition */
                } else {

                    // found
                    if(row.getop_code().compare("null")==0) {
                        row.setop_code(line.getWord1());
                        string temp = line.getWord1();
                        if (opT.opTable.at(temp).at(opT.opTable.at(temp).length()  - 1) == '2') {
                            row.format = 2;

                            if (temp == "tixr" || temp == "clear"){

                                if(line.getWord2().length()>1 ){
                                    row.hasError=true;
                                    row.errorMessge="syntax error : this opcode should has a register as operand";


                                }else{

                                    if(line.getWord2()!="a" && line.getWord2()!="x" &&
                                       line.getWord2()!="b" && line.getWord2()!="l" &&
                                       line.getWord2()!="s" &&line.getWord2()!="t" &&
                                       line.getWord2()!="f" ){

                                        row.hasError=true;
                                        row.errorMessge="syntax error : this opcode should has a register as operand";

                                    }

                                }

                            }




                        }


                        if(line.getWord1()=="resw"  || line.getWord1()=="resb" || line.getWord1()=="word"){
                            bool flag = false;
                            for(int i=0; i<line.getWord2().length();i++){
                                if(isalpha(line.getWord2().at(0))){
                                    flag = true ;
                                    break;
                                }}
                            if(flag){
                                row.errorMessge = "after this opcode there should be integer";
                                row.hasError= true;
                            }
                        }

                        if(line.getWord1()=="byte"){

                            if(line.getWord2().length()<4 &&(line.getWord2().at(0)!='c' || line.getWord2().at(0)!='x') ||line.getWord2().at(line.getWord2().length()-1)!='\'' ||line.getWord2().at(1)!='\'' ){
                                row.errorMessge="syntax error  not  the right format c'sds'";
                                row.hasError=true;
                            }
                        }





                    }else{
                        row.hasError=true;
                        row.errorMessge="syntax error : repeated op_code ";
                    }

                    if (opT.opTable.find(line.getWord2()) == opT.opTable.end()){

                        if(line.getWord1()=="addr" || line.getWord1()=="compr" ||
                           line.getWord1()=="divr" ||line.getWord1()=="mulr"||
                           line.getWord1()=="rmo"|| line.getWord1()=="shiftl" ||
                           line.getWord1()=="shiftr"|| line.getWord1()=="subr" ) {

                            if (line.getWord2().find(',') == std::string::npos) {
                                row.hasError= true;
                                row.errorMessge = "syntax error  un correct way to type operand in that position";
                            }else{
                                if(line.getWord2().length() >3){
                                    row.hasError= true;
                                    row.errorMessge = "syntax error  this should be two registers in the way r1,r2";
                                } else{
                                    if(line.getWord2().at(0)!='a' && line.getWord2().at(0)!='x' &&
                                       line.getWord2().at(0)!='b' && line.getWord2().at(0)!='l' &&
                                       line.getWord2().at(0)!='s' &&line.getWord2().at(0)!='t' &&
                                       line.getWord2().at(0)!='f' ){
                                        row.hasError= true;
                                        row.errorMessge = "syntax error  this should be two registers in the way r1,r2";
                                    } else if(line.getWord2().at(2)!='a' && line.getWord2().at(2)!='x' &&
                                              line.getWord2().at(2)!='b' && line.getWord2().at(2)!='l' &&
                                              line.getWord2().at(2)!='s' &&line.getWord2().at(2)!='t' &&
                                              line.getWord2().at(2)!='f' ){
                                        row.hasError= true;
                                        row.errorMessge = "syntax error  this should be two registers in the way r1,r2";
                                    }

                                }
                                row.setOperand(line.getWord2());
                            }
                        } else{
                            row.setOperand(line.getWord2());
                        }


                        row.setOperand(line.getWord2());} else{
                        row.hasError= true;
                        row.errorMessge = "syntax error  repeated opcode";
                    }



                    if(line.getcomment()!= "null"){
                        row.setcomment(line.getcomment());
                    }
                    //validationRows.push_back(row);

                }
                validationRows.push_back(row);
            }else if (line.NumofwORD == 3){

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

                            if (temp == "tixr" || temp == "clear"){

                                if(line.getWord3().length()>1 ){
                                    row.hasError=true;
                                    row.errorMessge="syntax error : this opcode should has a register as operand";


                                }else{

                                    if(line.getWord3()!="a" && line.getWord3()!="x" &&
                                       line.getWord3()!="b" && line.getWord3()!="l" &&
                                       line.getWord3()!="s" &&line.getWord3()!="t" &&
                                       line.getWord3()!="f" ){

                                        row.hasError=true;
                                        row.errorMessge="syntax error : this opcode should has a register as operand";

                                    }

                                }

                            }

                        }
                    }else{
                        row.hasError=true;
                        row.errorMessge="syntax error : repeated op_code ";
                    }


                    if (opT.opTable.find(line.getWord3()) == opT.opTable.end() && opT.opTable.find(line.getWord1()) == opT.opTable.end() ){

                        if(line.getWord2()=="addr" || line.getWord2()=="compr" ||
                           line.getWord2()=="divr" ||line.getWord2()=="mulr"||
                           line.getWord2()=="rmo"|| line.getWord2()=="shiftl" ||
                           line.getWord2()=="shiftr"|| line.getWord2()=="subr" ) {

                            if (line.getWord3().find(',') == std::string::npos) {
                                row.hasError= true;
                                row.errorMessge = "syntax error  un correct way to type operand in that position";
                            }else{

                                if(line.getWord3().length() >3){
                                    row.hasError= true;
                                    row.errorMessge = "syntax error  this should be two registers in the way r1,r2";
                                } else{
                                    if(line.getWord3().at(0)!='a' && line.getWord3().at(0)!='x' &&
                                       line.getWord3().at(0)!='b' && line.getWord3().at(0)!='l' &&
                                       line.getWord3().at(0)!='s' &&line.getWord3().at(0)!='t' &&
                                       line.getWord3().at(0)!='f' ){
                                        row.hasError= true;
                                        row.errorMessge = "syntax error  this should be two registers in the way r1,r2";
                                    } else if(line.getWord3().at(2)!='a' && line.getWord3().at(2)!='x' &&
                                              line.getWord3().at(2)!='b' && line.getWord3().at(2)!='l' &&
                                              line.getWord3().at(2)!='s' &&line.getWord3().at(2)!='t' &&
                                              line.getWord3().at(2)!='f' ){
                                        row.hasError= true;
                                        row.errorMessge = "syntax error  this should be two registers in the way r1,r2";
                                    }

                                }




                                //////////////////////////////////////
                                row.setOperand(line.getWord3());
                            }
                        } else{
                            row.setOperand(line.getWord3());
                        }


                        row.setLabel(line.getWord1());
                        if(line.getcomment()!= "null"){
                            row.setcomment(line.getcomment());
                        }

                    } else{
                        row.hasError= true;
                        row.setOperand(line.getWord3());
                        row.setLabel(line.getWord1());

                        row.errorMessge = "syntax error  opcode in false position";
                    }
                }

                if(line.getWord2()=="resw"  || line.getWord2()=="resb" || line.getWord2()=="word"){
                    bool flag = false;
                    for(int i=0; i<line.getWord3().length();i++){
                        if(isalpha(line.getWord3().at(0))){
                            flag = true ;
                            break;
                        }}
                    if(flag){
                        row.errorMessge = "after this opcode there should be integer";
                        row.hasError= true;
                    }
                }

                if(line.getWord2()=="byte"){

                    if(line.getWord3().length()<4 &&(line.getWord3().at(0)!='c' && line.getWord3().at(0)!='x' && line.getWord3().at(0)!='C' && line.getWord3().at(0)!='X' ) ||line.getWord3().at(line.getWord3().length()-1)!='\'' ||line.getWord3().at(1)!='\'' ){
                        row.errorMessge="syntax error  not  the right format c'sds'";
                        row.hasError=true;

                    }
                }





                validationRows.push_back(row);


            }
            if (row.getOperand().at(0) == '='){

                if(row.getOperand().at(2) != '\'' ||row.getOperand().at(row.getOperand().size()-1)!= '\'' ||
                   ((row.getOperand().at(1) != 'x'&&row.getOperand().at(1) != 'X') &&(row.getOperand().at(1) != 'c'&&row.getOperand().at(1) != 'C')&&(row.getOperand().at(1) != 'w'&&row.getOperand().at(1) != 'W')  ) ){

                    row.hasError=true;
                    row.errorMessge = "syntax error in literal";
                    if(row.getOperand().at(row.getOperand().size()-1)!= '\'' ){
                        cout<< row.getOperand().at(2)<<"opaaa"<<endl;

                    }
                    validationRows.pop_back();
                    validationRows.push_back(row);
                }


            }
            if( row.getOperand().find("+") != std::string::npos   || row.getOperand().find("-") != std::string::npos || row.getOperand().find("*") != std::string::npos || row.getOperand().find("/") != std::string::npos){
                row.isExpression = true;
                validationRows.back().isExpression=true;

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
    */ }