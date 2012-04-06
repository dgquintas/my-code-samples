// [file: CalcInterpreter.g, started: 6-Apr-2003]
//
// :tabSize=4:indentSize=4:
// -folding=explicit-collapseFolds=1-
//
// VB prac week3.
// Simple calculator with memory variables.
// CalcInterpreter (only).
//
// CHANGES
//      2003.04.06  ruys  Started (VB 2003).
//      2004.04.12  ruys  Modifications for VB 2004.
//      2006.04.22  ruys  Updated for Java 5.
//
// @author   Theo Ruys
// @version  2004.04.12


header { 
  #include <iostream>
  #include <map>
  #include <utility>
  #include <cmath>

  using namespace std;
}

options { language = "Cpp"; }

// {{{--- CalcInterpreter ----------------------------------------------



class CalcInterpreter extends TreeParser;

options {
    importVocab = Calc;                 // use the vocabulary "Calc"
    buildAST = false;                   // AST does not have to be transformed
}

{ 
    map<string,float> store;   
}

program
    :   #(PROGRAM_AST (declaration | statement)+)
    ;
    
declaration
    :   #(DECL type id:IDENTIFIER)
        { store[id->getText()] = 0.0; }           // initialize on 0
    ;

statement { float v = 0; }
    :   #(BECOMES id:IDENTIFIER v=expr)
        { store[id->getText()] = v;
        }
    |   #(PRINT v=expr)
        { cout << v << endl; }
    ;
    
expr returns [float val] { float x, y; val = 0; }
    :   val=operand 
    |   #(PLUS x=expr y=expr)   { val = x + y; }
    |   #(MINUS x=expr y=expr)  { val = x - y; }
    |   #(MUL x=expr y=expr)  { val = x * y; }
    |   #(DIV x=expr y=expr)  { val = x / y; }
    |   #(POW x=expr y=expr)  { val = powf(x,y); }
    |   #(MOD x=expr y=expr)  { val = fmodf(x,y); }
    |   #(SIGN_MINUS x=expr)  { val = -x; }
    ;
    
operand returns [float val = 0]
    :   id:IDENTIFIER   { val = store[id->getText()];   } 
    |   i:INT           { val = atoi(i->getText().c_str()); }   
    |   f:FLOAT         { val = atof(f->getText().c_str());  }
    ;
    
type
    :   INT
    |   FLOAT
    ;

// }}}--- CalcInterpreter

