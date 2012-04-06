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

#include <set>
#include <utility>
#include <iostream>

using namespace std;

}

options { language = "Cpp"; }

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
    PRINT       =   "print" ;
    INT         =   "int" ;
    FLOAT       =   "float" ;
}

// operators

BECOMES         :   '=' ;
PLUS            :   '+' ;
MINUS           :   '-' ;
MUL             : '*' ;
DIV             : '/' ;
MOD             : '%' ;
POW             : '^' ;
COLON           :   ':' ;
SEMICOLON       :   ';' ;
LPAREN          :   '(' ;
RPAREN          :   ')' ;

/* for matrices */
LBRACKET        :   '[' ;
RBRACKET        :   ']' ; 
COMMA           :   ',' ;

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
    :   ((DIGIT)+'.')=>
        ((DIGIT)+'.'(DIGIT)+) { $setType(FLOAT); }
    |   (DIGIT)+ { $setType(INT); }
    ;


// Comments -- ignored
COMMENT
    :   "//" (~'\n')* '\n' 
        { newline(); 
        $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); 
        }
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
        { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
    ;

// }}}--- Lexer


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
    DECL;
    SIGN_MINUS;
    SIGN_PLUS;
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
    :   type IDENTIFIER
        { #declaration = #([DECL, "declaration"], #declaration) ; }
    ;
    
statement
    :   assignment
    |   printStatement
    ;

assignment
    :   lvalue BECOMES^ expr
    ;

printStatement
    :   PRINT^ expr 
    ;

lvalue
    :   IDENTIFIER
    ;
    
expr
    : sumExpr
    ;

sumExpr
    : prodExpr ( (PLUS^ | MINUS^) prodExpr )*
    ;

prodExpr
    : powExpr ( (MUL^ | DIV^ | MOD^) powExpr)* 
    ;

powExpr
    : signedOperand (POW^ powExpr)? ;

signedOperand
    : ( m:MINUS^ {#m->setType(SIGN_MINUS);}
      | p:PLUS!  {#p->setType(SIGN_PLUS);}
      )? operand;

operand
    :   IDENTIFIER
    |   INT
    |   FLOAT
    |   LPAREN! expr RPAREN!
    ;

type
    :   INT
    |   FLOAT
    ;
    
// }}}--- Parser: production rules
// }}}--- Parser
// {{{--- CalcChecker --------------------------------------------------

class CalcChecker extends TreeParser;

options {
    buildAST = false;               // AST does not have to be transformed
    defaultErrorHandler = true;    // turn-off ANTLR's error handler to
                                    // propagate CalcExceptions to main
}

{ 
    set<string> idset; 
public:
    bool  isDeclared(string s)     { return (idset.find(s) != idset.end()); }
    void  declare(string s)        { idset.insert(s);             }
}

program
    :   #(PROGRAM_AST (declaration | statement)+)
    ;
    
declaration
    :   #(DECL type id:IDENTIFIER)
        {   if (isDeclared(id->getText())){
                cerr << id->getText() << " is already declared" << endl;
                exit(-1);
            }

            else 
                declare(id->getText()); 
        }
    ;
 
statement 
    :   #(BECOMES id:IDENTIFIER expr)
        {   
            if (!isDeclared(id->getText()))
            {
                cerr << id->getText() << " is not declared" << endl;
                exit(-1);
            }

            //TODO: type checking

        }
     |   #(PRINT expr)
    ;

expr 
    :   operand
    |   #(PLUS expr expr)   { /*TODO: type checking*/ }
    |   #(MINUS expr expr)  { /*TODO: type checking*/ }
    |   #(MUL expr expr)  { /*TODO: type checking*/ }
    |   #(DIV expr expr)  { /*TODO: type checking*/ }
    |   #(POW expr expr)  { /*TODO: type checking*/ }
    |   #(SIGN_MINUS expr)  { /*TODO: type checking*/  }
    ;

operand
    :   id:IDENTIFIER 
        {   if (!isDeclared(id->getText())){
              cerr << id->getText() << " is not declared" << endl;
              exit(-1);
              }
        }
    |   INT
    |   FLOAT
    ;
    
type
    :   INT
    |   FLOAT
    ;

// }}}--- CalcChecker

