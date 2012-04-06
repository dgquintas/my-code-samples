// [file: Calc.g, started: 4-Apr-2003]
//
// :tabSize=4:indentSize=4:
// -folding=explicit-collapseFolds=1-
//
// VB prac week3.
// Simple calculator with memory variables.
//
// CHANGES
//      2003.04.04  ruys  Started (VB 2003).
//      2004.04.12  ruys  Modifications for VB 2004.
//      2006.04.22  ruys  Updated for Java 5.
//
// @author   Theo Ruys
// @version  2004.04.12

header {
    import java.io.*;
}

// {{{--- Parser -------------------------------------------------------

class CalcParser extends Parser ;

options {
    k = 1;                              // # tokens lookahead
    exportVocab = Calc;                 // call the vocabulary "Calc"
    buildAST = true;                    // build an AST
}

// Imaginary tokens that are used for AST construction.

tokens {
    PROGRAM_AST;
}

// {{{--- Parser: production rules -------------------------------------

program
    :   declarations statements EOF!
        { #program = #([PROGRAM_AST, "program"], #program) ; }
            // Without a special root node, the ASTFrame will only
            // contain the first explicit node.
    ;
    
declarations
    :   (declaration SEMICOLON!)*
    ;
    
statements
    :   (statement SEMICOLON!)+
    ;

declaration
    :   VAR^ IDENTIFIER COLON! type
    ;
    
statement
    :   assignment
    |   printStatement
    ;

assignment
    :   lvalue BECOMES^ expr
    ;

printStatement
    :   PRINT^ LPAREN! expr RPAREN!
    ;

lvalue
    :   IDENTIFIER
    ;
    
expr
    :   operand ( (PLUS^ | MINUS^) operand )*
    ;

operand
    :   IDENTIFIER
    |   NUMBER
    |   LPAREN! expr RPAREN!
    ;

type
    :   INTEGER
    ;
    
// }}}--- Parser: production rules
// }}}--- Parser
// {{{--- Lexer --------------------------------------------------------

class CalcLexer extends Lexer;

options {
    k = 2;                              // needed for WS (for instance) 
    charVocabulary = '\3'..'\377';      // use ASCII character set
    exportVocab = Calc;                 // call the vocabulary "Calc"
    caseSensitive = true;               // lower and upper case is significant 
    caseSensitiveLiterals = true;       // literals are case sensitive
    testLiterals = false;               // do not check the tokens table by default
}

tokens {
    VAR         =   "var" ;
    PRINT       =   "print" ;
    INTEGER     =   "integer" ;
}

// operators

BECOMES         :   ":=" ;
PLUS            :   '+' ;
MINUS           :   '-' ;
COLON           :   ':' ;
SEMICOLON       :   ';' ;
LPAREN          :   '(' ;
RPAREN          :   ')' ;

protected
LOWER           :   ('a'..'z') ;

protected
UPPER           :   ('A'..'Z') ;

protected
DIGIT           :   ('0'..'9') ;

// The option testLiterals is only set to true for the rule IDENTIFIER!  
// Consequently, after matching the rule, ANTRL will look in the tokens 
// table to check whether the string found is an IDENTIFIER or a TOKEN.
IDENTIFIER
    options { testLiterals = true; }
    :   (LOWER | UPPER) (LOWER | UPPER | DIGIT)*
    ;

NUMBER
    :   (DIGIT)+
    ;


// Comments -- ignored
COMMENT
    :   "//" (~'\n')* '\n' 
        { newline(); $setType(Token.SKIP); }
    ;

// Whitespace -- ignored
WS
    :   ( ' '
        |	'\t'
        |	'\f'
        // handle newlines
        |   (	"\r\n"  // Evil DOS
            |	'\r'    // Macintosh
            |	'\n'    // Unix (the right way)
            )
            { newline(); }
        )
        { $setType(Token.SKIP); }
    ;

// }}}--- Lexer
// {{{--- CalcChecker --------------------------------------------------

{ import java.util.*; }

class CalcChecker extends TreeParser;

options {
    buildAST = false;               // AST does not have to be transformed
    defaultErrorHandler = false;    // turn-off ANTLR's error handler to
                                    // propagate CalcExceptions to main
}

{ 
    Set<String> idset = new HashSet<String>();   
    
    public boolean  isDeclared(String s)     { return idset.contains(s); }
    public void     declare(String s)        { idset.add(s);             }
}

program
    :   #(PROGRAM_AST (declaration | statement)+)
    ;
    
declaration
    :   #(VAR id:IDENTIFIER type)
        {   if (isDeclared(id.getText()))
                throw new CalcException(id.getText() + " is already declared");
            else 
                declare(id.getText()); 
        }
    ;
 
statement 
    :   #(BECOMES id:IDENTIFIER expr)
        {   if (!isDeclared(id.getText()))
                throw new CalcException(id.getText() + " is not declared");
        }
     |   #(PRINT expr)
    ;
    
expr 
    :   operand
    |   #(PLUS expr expr)
    |   #(MINUS expr expr)
    ;
    
operand
    :   id:IDENTIFIER 
        {   if (!isDeclared(id.getText()))
                throw new CalcException(id.getText() + " is not declared");
        }
    |   n:NUMBER 
    ;
    
type
    :   INTEGER
    ;

// }}}--- CalcChecker

