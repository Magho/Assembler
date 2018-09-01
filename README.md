# Assembler
the project consist of 2 pases :

## pass 1 :

- #### Specifications:
  1. Parsing SIC/XE code in formatts 2,3 & 4.
  2. Handling directives BYTE,WORD,RESW,RESB,ORG & EQU.
  3. Generate the symbol table.
  4. Generate the source file of code with assigned addresses.
  
- #### Design :
  ###### The main design consist of 4 modules parsing ,validation, executing the pass1 algorithm & printing the output.
  - The parsing module extract the components of each line.
  - The validating module validate the components of every line.
  - Then executing the algorithm and printing the output.
  
- #### Main data structures :
   - Arrays & Lists : contain the components of every line sequenchelly.
   - Maps : made one to one mapping between the operation code & their hexadecimal values & formats
   - Created data structures LIne & Rows : carry the values of the line components.
    
- #### Algorithm :
<img src="https://github.com/Magho/Assembler/blob/master/images/1.png" width="600"> 
- Assumptions :
  - Add comments in free format preceded with “.”
  - Don’t enter literals & expressions.

- #### Sample runs : 
<img src="https://github.com/Magho/Assembler/blob/master/images/2.png" width="400"> <img src="https://github.com/Magho/Assembler/blob/master/images/3.png" width="400"> 

## pass 2 :

- #### Specifications:

  - The assembler is to execute by entering assemble <source-file-name>.
  - The source file for the main program for this phase is to be named assemble.cpp.
  - The output of the assembler should include (at least):
    - Object-code file whose format is the same as the one described in the text book in section 2.1.1 and 2.3.5.
    - A report at the end of pass2. Pass1 and Pass2 errors should be included as part of the assembler report, exhibiting           both the offending line ofsource code and the error.
  - The assembler should support:
    - EQU and ORG statements.
    - Simple expression evaluation. A simple expression includes simple {A -op- B} operand arithmetic, where -op- is one of         +,-,*,/ and no spaces surround the operation, eg. A+B.
    - Literals (Including LTORG) =C’<ASCII-TEXT>’, =X’HEX-TEXT’, =<DECIMAL-TEXT> forms
  
- #### Design :
  ###### The main design consist of 5 main modules parsing ,validation, executing the pass1 algorithm, executing pass 2         algorithm & printing the output
  - The parsing module extract the components of each line.
  - The validating module validate the components of every line.
  - The pass2 module generate the object code for each line and print it in a file.
  - Then executing the algorithm and printing the output.
  
- #### Main data structures :
  - Arrays & Lists & vectors : contain the components of every line sequenchelly.
  - Maps : made one to one mapping between the operation code & their hexadecimal values & formats.
  - Created data structures LIne & Rows : carry the values of the line components.
   
- #### Algorithm :
<img src="https://github.com/Magho/Assembler/blob/master/images/4.png" width="600"> 

- #### Sample runs : 
<img src="https://github.com/Magho/Assembler/blob/master/images/5.png" width="400"> <img src="https://github.com/Magho/Assembler/blob/master/images/6.png" width="400"> 

### a detaield Explanation can be found here [Report 1](https://github.com/Magho/Assembler/blob/master/Report%20pass1.pdf) , [Report 2](https://github.com/Magho/Assembler/blob/master/assembler%202.pdf)


## Running

#### Clone & install
* 
* Clone this repo `https://github.com/Magho/Assembler`
* cd `Assemblerp`
* run `assembler.exe` file

## Authors
  - [Magho](https://github.com/Magho)
  - [AhmedHesham](https://github.com/ahm7)
  - [ritasamir](https://github.com/ritasamir)
  - [Mohamed Kamal](https://github.com/muhammedkamal97)

## License 
[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)
[LICENSE.md](https://github.com/Magho/Assembler/blob/master/LICENSE.md)
