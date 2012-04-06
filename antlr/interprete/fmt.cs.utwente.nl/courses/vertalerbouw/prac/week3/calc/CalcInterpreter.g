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
    import java.io.*;
}

// {{{--- CalcInterpreter ----------------------------------------------

{ import java.util.*; }

class CalcInterpreter extends TreeParser;

options {
    importVocab = Calc;                 // use the vocabulary "Calc"
    buildAST = false;                   // AST does not have to be transformed
}

{ 
    Map<String,Integer> store = new HashMap<String,Integer>();   
}

program
    :   #(PROGRAM_AST (declaration | statement)+)
    ;
    
declaration
    :   #(VAR id:IDENTIFIER type)
        { store.put(id.getText(), 0); }           // initialize on 0
    ;

statement { int v = 0; }
    :   #(BECOMES id:IDENTIFIER v=expr)
        { store.put(id.getText(), v); }
    |   #(PRINT v=expr)
        { System.out.println("" + v); }
    ;
    
expr returns [int val] { int x, y; val = 0; }
    :   val=operand
    |   #(PLUS x=expr y=expr)   { val = x + y; }
    |   #(MINUS x=expr y=expr)  { val = x - y; }
    ;
    
operand returns [int val = 0]
    :   id:IDENTIFIER   { val = store.get(id.getText());       } 
    |   n:NUMBER        { val = Integer.parseInt(n.getText()); }
    ;
    
type
    :   INTEGER
    ;

// }}}--- CalcInterpreter

