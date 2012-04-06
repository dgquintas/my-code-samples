options { language="Cpp"; }


class ExpressionParser extends Parser;
options { buildAST=true;}
imaginaryTokenDefinitions : 
  SIGN_MINUS
  SIGN_PLUS
;

start      : expr SEMI;
expr       : sumExpr ;
sumExpr    : prodExpr ((PLUS^|MINUS^) prodExpr)*; 
prodExpr   : powExpr ((MUL^|DIV^|MOD^) powExpr)* ;
powExpr    : signedAtom (POW^ powExpr)? ;
signedAtom : ( m:MINUS^ {#m->setType(SIGN_MINUS);}
             | p:PLUS!  {#p->setType(SIGN_PLUS);}
             )? atom;
atom       : INT 
           | LPAREN^ sumExpr RPAREN!
           ;

class ExpressionLexer extends Lexer;

PLUS  : '+' ;
MINUS : '-' ;
MUL   : '*' ;
DIV   : '/' ;
MOD   : '%' ;
POW   : '^' ;
SEMI  : ';' ;
LPAREN: '(' ;
RPAREN: ')' ;

protected DIGIT : '0'..'9' ;
INT   : (DIGIT)+ ;
WS     :
    (' ' 
    | '\t' 
    | '\r' '\n' { newline(); } 
    | '\n'      { newline(); }
    ) 
    { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); } 
  ;
   

{#include <cstdlib>
 #include <cmath>}
class ExpressionTreeWalker extends TreeParser;

start returns [double r]
  { double a,b; r=0; }

  : #(PLUS a=start b=start)  { r=a+b; }
  | #(MINUS a=start b=start) { r=a-b; }
  | #(MUL  a=start b=start)  { r=a*b; }
  | #(DIV  a=start b=start)  { r=a/b; }
  | #(MOD  a=start b=start)  { r=fmod(a,b); }
  | #(POW  a=start b=start)  { r=pow(a,b); }
  | #(LPAREN a=start)       { r=a; }
  | #(SIGN_MINUS a=start)   { r=-1.0 * a; }
  | i:INT { r=atof(i->getText().c_str()); }
  ;
