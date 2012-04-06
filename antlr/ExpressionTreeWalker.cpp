/* $ANTLR 2.7.6 (20060528): "expression.g" -> "ExpressionTreeWalker.cpp"$ */
#include "ExpressionTreeWalker.hpp"
#include <antlr/Token.hpp>
#include <antlr/AST.hpp>
#include <antlr/NoViableAltException.hpp>
#include <antlr/MismatchedTokenException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/BitSet.hpp>
#line 47 "expression.g"
#include <cstdlib>
#include <cmath>
#line 13 "ExpressionTreeWalker.cpp"
ExpressionTreeWalker::ExpressionTreeWalker()
	: ANTLR_USE_NAMESPACE(antlr)TreeParser() {
}

double  ExpressionTreeWalker::start(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
#line 51 "expression.g"
	double r;
#line 21 "ExpressionTreeWalker.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefAST start_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST i = ANTLR_USE_NAMESPACE(antlr)nullAST;
#line 51 "expression.g"
	double a,b; r=0;
#line 26 "ExpressionTreeWalker.cpp"
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case PLUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t33 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp1_AST_in = _t;
			match(_t,PLUS);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			b=start(_t);
			_t = _retTree;
			_t = __t33;
			_t = _t->getNextSibling();
#line 54 "expression.g"
			r=a+b;
#line 46 "ExpressionTreeWalker.cpp"
			break;
		}
		case MINUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t34 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp2_AST_in = _t;
			match(_t,MINUS);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			b=start(_t);
			_t = _retTree;
			_t = __t34;
			_t = _t->getNextSibling();
#line 55 "expression.g"
			r=a-b;
#line 63 "ExpressionTreeWalker.cpp"
			break;
		}
		case MUL:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t35 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp3_AST_in = _t;
			match(_t,MUL);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			b=start(_t);
			_t = _retTree;
			_t = __t35;
			_t = _t->getNextSibling();
#line 56 "expression.g"
			r=a*b;
#line 80 "ExpressionTreeWalker.cpp"
			break;
		}
		case DIV:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t36 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp4_AST_in = _t;
			match(_t,DIV);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			b=start(_t);
			_t = _retTree;
			_t = __t36;
			_t = _t->getNextSibling();
#line 57 "expression.g"
			r=a/b;
#line 97 "ExpressionTreeWalker.cpp"
			break;
		}
		case MOD:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t37 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp5_AST_in = _t;
			match(_t,MOD);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			b=start(_t);
			_t = _retTree;
			_t = __t37;
			_t = _t->getNextSibling();
#line 58 "expression.g"
			r=fmod(a,b);
#line 114 "ExpressionTreeWalker.cpp"
			break;
		}
		case POW:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t38 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp6_AST_in = _t;
			match(_t,POW);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			b=start(_t);
			_t = _retTree;
			_t = __t38;
			_t = _t->getNextSibling();
#line 59 "expression.g"
			r=pow(a,b);
#line 131 "ExpressionTreeWalker.cpp"
			break;
		}
		case LPAREN:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t39 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp7_AST_in = _t;
			match(_t,LPAREN);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			_t = __t39;
			_t = _t->getNextSibling();
#line 60 "expression.g"
			r=a;
#line 146 "ExpressionTreeWalker.cpp"
			break;
		}
		case SIGN_MINUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t40 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp8_AST_in = _t;
			match(_t,SIGN_MINUS);
			_t = _t->getFirstChild();
			a=start(_t);
			_t = _retTree;
			_t = __t40;
			_t = _t->getNextSibling();
#line 61 "expression.g"
			r=-1.0 * a;
#line 161 "ExpressionTreeWalker.cpp"
			break;
		}
		case INT:
		{
			i = _t;
			match(_t,INT);
			_t = _t->getNextSibling();
#line 62 "expression.g"
			r=atof(i->getText().c_str());
#line 171 "ExpressionTreeWalker.cpp"
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(_t);
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		if ( _t != ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = _t->getNextSibling();
	}
	_retTree = _t;
	return r;
}

void ExpressionTreeWalker::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* ExpressionTreeWalker::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"SIGN_MINUS",
	"SIGN_PLUS",
	"SEMI",
	"PLUS",
	"MINUS",
	"MUL",
	"DIV",
	"MOD",
	"POW",
	"INT",
	"LPAREN",
	"RPAREN",
	"DIGIT",
	"WS",
	0
};



