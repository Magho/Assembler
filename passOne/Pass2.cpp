
//
// Created by magho on 05/06/18.
//

#include "Pass2.h"
#include "parsing.h"
#include "optable.h"
#include "bits/stdc++.h"
#include "optable.h"
#include "litLine.h"
#include <string>
#include <iostream>

void Pass2::pass2Algoritm(vector<Row> listFile,map<string,string> symTable,vector<litLine> litTab) {

    optable optable1;
    optable1.setTable();

    vector<string> objectcodes;
    vector<string> modificationRecords;
    int pc;
    int base = -1;
    int format;
    int n, i, x, b, p, e;
    string nameOfProg;
    int lengthOfProg;
    int startAddressAtEndStatment;
    int startAddressAtStartStatment;

    for (int i = 0; i < listFile.size(); ++i) {
    	try{
        string object_code;
        if (listFile[i].isComment) {

        } else {

            if (startsWith(listFile[i].getop_code(), "byte")) {
                object_code = byte_operand(listFile[i].getOperand());
                string str = object_code;
            	if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                    objectcodes[objectcodes.size()-1] += str;
                }else{
                    string strx = listFile[i].getAddress();
                    for(;6>strx.size();) strx = "0" + strx;
                    objectcodes.push_back(strx);
                    objectcodes[objectcodes.size()-1] += str;
                }
                cout<< object_code<<endl;
                continue;
            } else if  (startsWith(listFile[i].getLabel(), "*")) {
                /// literals
                object_code = byte_operand(listFile[i].getop_code());

            } else if (startsWith(listFile[i].getop_code(), "word")) {
                object_code = word_operand(listFile[i].getOperand());
                string str = object_code;
            	if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                    objectcodes[objectcodes.size()-1] += str;
                }else{
                    string strx = listFile[i].getAddress();
                    for(;6>strx.size();) strx = "0" + strx;
                    objectcodes.push_back(strx);
                    objectcodes[objectcodes.size()-1] += str;
                }

            } else if (startsWith(listFile[i].getop_code(), "start")) {
                object_code = start_operand(startAddressAtStartStatment, nameOfProg, listFile[i]);
                std::string result;
                std::stringstream ss;
                ss <<std::hex <<startAddressAtStartStatment;
                ss >> result;
                if(result.size() < 6){
                    for(;6>result.size();) result = "0" + result;
                }
                objectcodes.push_back("");
                objectcodes.push_back(result);
            } else if (startsWith(listFile[i].getop_code(), "end")) {
                string start = "H"+ nameOfProg;
                for(;7>start.size();) start+=" ";
                std::string result;
                std::stringstream ss;
                ss <<std::hex <<startAddressAtStartStatment;
                ss >> result;
                if(result.size() < 6){
                    for(;6>result.size();) result = "0" + result;
                }
                start += result;
                object_code = end_operand(startAddressAtStartStatment, startAddressAtEndStatment,
                                          lengthOfProg, listFile[i],symTable);

                result = toHex(lengthOfProg,2);
                if(result.size() < 6){
                    for(;6>result.size();) result = "0" + result;
                }
                start += result;
                result = toHex(startAddressAtEndStatment,4);
                if(result.size() < 6){
                    for(;6>result.size();) result = "0" + result;
                }
                string ending = "E"+ result;
                objectcodes[0] = start;
                objectcodes.push_back(ending);

            } else if (startsWith(listFile[i].getop_code(), "base")) {
                object_code = base_operand(listFile[i], base, symTable);


            } else if (startsWith(listFile[i].getop_code(), "ltorg")) {
                object_code = ltorg_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "equ")) {
                object_code = equ_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "org")) {
                object_code = org_operand(listFile[i]);

            } else if (startsWith(listFile[i].getop_code(), "resw")) {
                // TODO need to know that its a resw or resb to escape while writing in file
                object_code = resw_operand(listFile[i]);
                string str = objectcodes[objectcodes.size()-1];
                for(;67>str.size();) str += "#";
                objectcodes[objectcodes.size()-1] = str;

            } else if (startsWith(listFile[i].getop_code(), "resb")) {
                // TODO need to know that its a resw or resb to escape while writing in file
                object_code = resb_operand(listFile[i]);
                string str = objectcodes[objectcodes.size()-1];
                for(;67>str.size();) str += "#";
                objectcodes[objectcodes.size()-1] = str;

            }else if(startsWith(listFile[i].getop_code(),"=")){
            	string opr = listFile[i].getop_code();
            	litLine li;
            	for(int j = 0;j<litTab.size();j++){
            	     if(opr.compare(litTab[j].getLiteral()) == 0){
            	            li = litTab[j];
            	     }
            	}
            	object_code = li.getValue();
            	string str = object_code;
            	if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                    objectcodes[objectcodes.size()-1] += str;
                }else{
                    string strx = listFile[i].getAddress();
                    for(;6>strx.size();) strx = "0" + strx;
                    objectcodes.push_back(strx);
                    objectcodes[objectcodes.size()-1] += str;
                }
        	}else if(startsWith(listFile[i].getOperand(),"=")){
            	string opr = listFile[i].getOperand().substr(0);
            	int operation = std::stoi(optable1.getOptable(listFile[i].getop_code()), nullptr, 16);
            	operation = operation | (1 << 1); // set n's bit
            	operation = operation | (1 << 0); // set i's bit
            	int obj = operation;
            	obj <<= 4;
            	litLine li;
            	for(int j = 0;j<litTab.size();j++){
            		if(opr.compare(litTab[j].getLiteral()) == 0){
            			li = litTab[j];
            		}
            	}
            	int addr = std::stoi(li.getAddress(), nullptr, 16);
            	if (format == 4) {
            		obj |= 1;
            		obj <<= 4*5;
            		obj |= addr;
            		object_code = toHex(obj,4);
            		for(;object_code.size()<8;) object_code = "0"+object_code;
            		string str = object_code;
            		if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                        objectcodes[objectcodes.size()-1] += str;
            		}else{
            		    string strx = listFile[i].getAddress();
            		    for(;6>strx.size();) strx = "0" + strx;
                        objectcodes.push_back(strx);
                        objectcodes[objectcodes.size()-1] += str;
            		}
            		string strx = listFile[i].getAddress();
                    for(;6>strx.size();) strx = "0" + strx;
                    string strr = "M" + strx + "05";
                    modificationRecords.push_back(strr);

            		cout<< std::setfill('0') << std::setw(8)<<object_code<<endl;
            		continue;
     			}
            	int disp = addr - pc;
            	if (!(disp < 2024 && disp >= -2024) && base != -1) {
            		//using base
            		disp = addr - base;
            		obj |= (1 << 2);
            	}else if(!(disp < 2024 && disp >= -2024)){
            		disp = 0;
            	} else {
            		obj |= (1 << 1);
            	}
            	obj <<= 4 * 3;
            	obj |= (disp & ((1 << 12) - 1));
            	object_code = toHex(obj,3);
            	for(;object_code.size()<6;) object_code = "0"+object_code;
            	string str = object_code;
            	if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                    objectcodes[objectcodes.size()-1] += str;
                }else{
                    string strx = listFile[i].getAddress();
                    for(;6>strx.size();) strx = "0" + strx;
                    objectcodes.push_back(strx);
                    objectcodes[objectcodes.size()-1] += str;
                }
            } else {

                int currentAddress = std::stoi(listFile[i].getAddress(), nullptr, 16);
                //format = formatType(listFile[i].getop_code());
                format = listFile[i].format;
                pc = calcPC(currentAddress, format);
                if(format == 2){
                	string opr = optable1.getOptable(listFile[i].getop_code()).substr(0,2);
                	int obj = std::stoi(opr,nullptr,16);
                	if(listFile[i].getOperand().size() == 3){
                		string firstOperand = optable1.getOptable(listFile[i].getOperand().substr(0,1));
                		string secondOperand = optable1.getOptable(listFile[i].getOperand().substr(2,3));
                		obj <<= 4;
                		obj |= std::stoi(firstOperand);
                		obj <<= 4;
                		obj |= std::stoi(secondOperand);
                	}else{
                		string firstOperand = optable1.getOptable(listFile[i].getOperand().substr(0,1));
                		obj <<= 4;
                		obj |= std::stoi(firstOperand);
                		obj <<= 4;
                	}
                	object_code = toHex(obj,2);

                	for(;object_code.size()<4;) object_code = "0"+object_code;
                    string str = object_code;
                    if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <= 60){
                        objectcodes[objectcodes.size()-1] += str;
                    }else{
                        string strx = listFile[i].getAddress();
                        for(;6>strx.size();) strx = "0" + strx;
                        objectcodes.push_back(strx);
                        objectcodes[objectcodes.size()-1] += str;
                    }
                	cout<< std::setfill('0') << std::setw(4)<<object_code<<endl;
                	continue;
                }

                // determine addressing mode
                if (startsWith(listFile[i].getOperand(), "#")) {
                    //immediate
                    string opr = listFile[i].getOperand().substr(1);
                    int operation = std::stoi(optable1.getOptable(listFile[i].getop_code()), nullptr, 16);
                    operation = operation | (1);
                    operation &=  ~(1 << 1);
                    int obj = operation;
                    obj <<= 1 * 4;
                    if (format == 4) {
                    	obj |= 1;
                    	obj <<= 4*5;
                    	if (!isdigit(opr.c_str()[0])) {
                    	   int addr = std::stoi(symTable[opr], nullptr, 16);
                    	   obj |= (addr & ((1 << 20) - 1));
                    	} else {
                    	   obj |= (std::stoi(opr, nullptr,10) & ((1 << 20) - 1));
                    	}
                    }
                    else{
                    	obj <<= 4 * 3;
                    	if (!isdigit(opr.c_str()[0])) {
                    	    int addr = std::stoi(symTable[opr], nullptr, 16);
                    	    obj |= (addr & ((1 << 12) - 1));
                    	} else {
                    	    obj |= (std::stoi(opr, nullptr,10) & ((1 << 12) - 1));
                    	}
                    }
                    object_code = toHex(obj,format);
                    for(;object_code.size()<format*2;) object_code = "0"+object_code;
                        string str = object_code;
                    if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                        objectcodes[objectcodes.size()-1] += str;
                    }else{
                        string strx = listFile[i].getAddress();
                        for(;6>strx.size();) strx = "0" + strx;
                        objectcodes.push_back(strx);
                        objectcodes[objectcodes.size()-1] += str;
                    }


                } else if (startsWith(listFile[i].getOperand(), "@")) {
                    //indirect
                    string opr = listFile[i].getOperand().substr(1);
                    int operation = std::stoi(optable1.getOptable(listFile[i].getop_code()), nullptr, 16);
                    operation = operation | (1 << 1); // set n's bit
                    operation = operation & ~(1);//clear i's bit
                    int obj = operation;
                    obj <<= 4;
                    if (endWith(listFile[i].getOperand(), ",x")) {
                         obj |= (1 << 3);
                         opr = opr.substr(0,opr.size()-2);
                    }
                    int addr = std::stoi(symTable[opr], nullptr, 16);
                    if (format == 4) {
                         obj |= 1;
                         obj <<= 4*5;
                         obj |= addr;
                         object_code = toHex(obj,4);
                         for(;object_code.size()<8;) object_code = "0"+object_code;
                        string str = object_code;
                        if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                            objectcodes[objectcodes.size()-1] += str;
                        }else{
                            string strx = listFile[i].getAddress();
                            for(;6>strx.size();) strx = "0" + strx;
                            objectcodes.push_back(strx);
                            objectcodes[objectcodes.size()-1] += str;
                        }

                        string strx = listFile[i].getAddress();
                        for(;6>strx.size();) strx = "0" + strx;
                        string strr = "M" + strx + "05";
                        modificationRecords.push_back(strr);

                        cout<< std::setfill('0') << std::setw(8)<<object_code<<endl;
                        continue;
                    }
                    int disp = addr - pc;
                    if (!(disp < 2024 && disp >= -2024) && base != -1) {
                        //using base
                        disp = addr - base;
                        obj |= (1 << 2);
                    }else if(!(disp < 2024 && disp >= -2024)){
                    	disp = 0;
                    }else {
                        obj |= (1 << 1);
                    }
                    obj <<= 4 * 3;
                    obj |= (disp & ((1 << 12) - 1));
                    object_code = toHex(obj,3);
                    for(;object_code.size()<6;) object_code = "0"+object_code;
                    string str = object_code;
                    if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                        objectcodes[objectcodes.size()-1] += str;
                    }else{
                        string strx = listFile[i].getAddress();
                        for(;6>strx.size();) strx = "0" + strx;
                        objectcodes.push_back(strx);
                        objectcodes[objectcodes.size()-1] += str;
                    }
                } else {
                    //direct
                	if(listFile[i].getop_code().compare("rsub") == 0){
                		object_code = "4f0000";
                		for(;object_code.size()<6;) object_code = "0"+object_code;
                        string str = object_code;
                        if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <= 60){
                            objectcodes[objectcodes.size()-1] += str;
                        }else{
                            string strx = listFile[i].getAddress();
                            for(;6>strx.size();) strx = "0" + strx;
                            objectcodes.push_back(strx);
                            objectcodes[objectcodes.size()-1] += str;
                        }
                	}else{
						string opr = listFile[i].getOperand().substr(0);
						int operation = std::stoi(optable1.getOptable(listFile[i].getop_code()), nullptr, 16);
						operation = operation | (1 << 1); // set n's bit
						operation = operation | (1 << 0); // set i's bit
						int obj = operation;
						obj <<= 4;
						if (endWith(listFile[i].getOperand(), ",x")) {

							opr = opr.substr(0,opr.size()-2);
							obj |= (1 << 3);//setting x's bit
						}
						int addr = std::stoi(symTable[opr], nullptr, 16);
						if (format == 4) {
							obj |= 1;
							obj <<= 4*5;
							obj |= addr;
							object_code = toHex(obj,4);
							for(;object_code.size()<8;) object_code = "0"+object_code;
                            string str = object_code;
                            if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                                objectcodes[objectcodes.size()-1] += str;
                            }else{
                                string strx = listFile[i].getAddress();
                                for(;6>strx.size();) strx = "0" + strx;
                                objectcodes.push_back(strx);
                                objectcodes[objectcodes.size()-1] += str;
                            }

                            string strx = listFile[i].getAddress();
                            for(;6>strx.size();) strx = "0" + strx;
                            string strr = "M" + strx + "05";
                            modificationRecords.push_back(strr);

							cout<< std::setfill('0') << std::setw(8)<<object_code<<endl;
							continue;
						}

						int disp = addr - pc;
						if (!(disp < 2024 && disp >= -2024) && base != -1) {
							//using base
							disp = addr - base;
							obj |= (1 << 2);
						}else if(!(disp < 2024 && disp >= -2024)){
							disp = 0;
						} else {
							obj |= (1 << 1);
						}
						obj <<= 4 * 3;
						obj |= (disp & ((1 << 12) - 1));
						object_code = toHex(obj,3);
						for(;object_code.size()<6;) object_code = "0"+object_code;
                        string str = object_code;
                        if(objectcodes[objectcodes.size()-1].size()+str.size()-6 <=60){
                            objectcodes[objectcodes.size()-1] += str;
                        }else{
                            string strx = listFile[i].getAddress();
                            for(;6>strx.size();) strx = "0" + strx;
                            objectcodes.push_back(strx);
                            objectcodes[objectcodes.size()-1] += str;
                        }
                	}
                }
            }
        }
        cout<<std::setfill('0') << std::setw(6)<<object_code<<endl;
    	}catch(exception& e){
    	}
    }
    printing(objectcodes,modificationRecords);

}

void Pass2::printing(vector<string> objects,vector<string> modificationRecords ){
    FILE *fp;
    fp = fopen("objectCode.txt","w");
    fprintf(fp,"%s\n",objects[0].c_str());
    for(int i = 1;i<objects.size()-1;i++){
        fprintf(fp,"T");
        string addr = objects[i].substr(0,6);
        fprintf(fp,"%s",addr.c_str());
        int length = 0;
        for(int j = 6;j<objects[i].size();j++){
            if(objects[i].at(j) == '#'){
                break;
            }else{
                length++;
            }
        }
        string lengthHex = toHex(length/2,3);
        for(;lengthHex.size()<2;) lengthHex = "0"+lengthHex;
        fprintf(fp,"%s",lengthHex.c_str());
        for(int j = 6;j<objects[i].size();j++){
            if(objects[i].at(j) == '#'){
                break;
            }else{
                fprintf(fp,"%c",objects[i].at(j));
            }
        }
        fprintf(fp,"\n");
    }
    for (int i = 0 ; i < modificationRecords.size();i++ ) {
        string x = modificationRecords[i].substr(1,modificationRecords[i].size()-3);

        int l = std::stoi(x,nullptr,16) +1;
        x = toHex(l,2);
        for(;x.size()<6;) x = "0" + x;
        x = "M" +x+"05";
        fprintf(fp,"%s",x.c_str());
        fprintf(fp,"\n");
    }
    fprintf(fp,"%s",objects[objects.size()-1].c_str());
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
    ss<<std::setfill('0') << std::setw(6)<<hex << decimal;
    string res ( ss.str() );

    return res.c_str();
}

string Pass2:: byte_operand(string operand){

    string object_code;
    if (startsWith(operand, "c")) {
        //skip c="...."
        string operand_value = operand.substr(2, operand.size()-3);
        object_code = string_to_hex(operand_value);
    } else {
        //start with x
        string operand_value = operand.substr(2, operand.size()-3);
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
        startAddressAtStartStatment = std::stoi(entry.getOperand(), nullptr, 16);
    }
    nameOfProg = entry.getLabel();

    return "null";
}

string Pass2 :: end_operand(int& startAddressAtStartStatment,
		int& startAddressAtEndStatment,
		int& lengthOfProg , Row entry,map<string,string> sym) {

    if (entry.getOperand() != "null" && !isdigit(entry.getOperand().at(0))) {
        startAddressAtEndStatment = std::stoi(sym[entry.getOperand()], nullptr, 16);
    }else if(isdigit(entry.getOperand().at(0))){
        startAddressAtEndStatment = std::stoi(entry.getOperand(),nullptr,16);
    }
    lengthOfProg = std::stoi(entry.getAddress(), nullptr, 16) - startAddressAtStartStatment;
    return "null";
}

string Pass2 :: base_operand(Row entry, int& base, map<string, string> symTable) {
	base = std::stoi(symTable[entry.getOperand()], nullptr,16);
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

    string ss = "beta,x";
    cout<< ss.substr(0, ss.size()-2);


    cout << "***********************************************\n";
    cout << "***********************************************\n";

}

string Pass2::toHex(int i,int format){
	std::string result;
	    std::stringstream ss;
	    ss <<std::hex <<i;
	    ss >> result;
	    return result;
}
