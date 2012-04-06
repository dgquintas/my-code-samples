/* $ANTLR 2.7.6 (20070206): "Calc.g" -> "CalcChecker.cpp"$ */
#include "CalcChecker.hpp"
#include <antlr/Token.hpp>
#include <antlr/AST.hpp>
#include <antlr/NoViableAltException.hpp>
#include <antlr/MismatchedTokenException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/BitSet.hpp>
#line 1 "Calc.g"
#line 11 "CalcChecker.cpp"
CalcChecker::CalcChecker()
	: ANTLR_USE_NAMESPACE(antlr)TreeParser() {
}

void CalcChecker::program(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST program_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST __t71 = _t;
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp1_AST_in = _t;
		match(_t,PROGRAM_AST);
		_t = _t->getFirstChild();
		{ // ( ... )+
		int _cnt73=0;
		for (;;) {
			if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
				_t = ASTNULL;
			switch ( _t->getType()) {
			case DECL:
			{
				declaration(_t);
				_t = _retTree;
				break;
			}
			case PRINT:
			case BECOMES:
			{
				statement(_t);
				_t = _retTree;
				break;
			}
			default:
			{
				if ( _cnt73>=1 ) { goto _loop73; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(_t);}
			}
			}
			_cnt73++;
		}
		_loop73:;
		}  // ( ... )+
		_t = __t71;
		_t = _t->getNextSibling();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		if ( _t != ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = _t->getNextSibling();
	}
	_retTree = _t;
}

void CalcChecker::declaration(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST declaration_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST id = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST __t75 = _t;
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp2_AST_in = _t;
		match(_t,DECL);
		_t = _t->getFirstChild();
		type(_t);
		_t = _retTree;
		id = _t;
		match(_t,IDENTIFIER);
		_t = _t->getNextSibling();
		_t = __t75;
		_t = _t->getNextSibling();
#line 231 "Calc.g"
		if (isDeclared(id->getText())){
		cerr << id->getText() << " is already declared" << endl;
		exit(-1);
		}
		
		else 
		declare(id->getText()); 
		
#line 88 "CalcChecker.cpp"
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		if ( _t != ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = _t->getNextSibling();
	}
	_retTree = _t;
}

void CalcChecker::statement(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST statement_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST id = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case BECOMES:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t77 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp3_AST_in = _t;
			match(_t,BECOMES);
			_t = _t->getFirstChild();
			id = _t;
			match(_t,IDENTIFIER);
			_t = _t->getNextSibling();
			expr(_t);
			_t = _retTree;
			_t = __t77;
			_t = _t->getNextSibling();
#line 243 "Calc.g"
			
			if (!isDeclared(id->getText()))
			{
			cerr << id->getText() << " is not declared" << endl;
			exit(-1);
			}
			
			//TODO: type checking
			
			
#line 130 "CalcChecker.cpp"
			break;
		}
		case PRINT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t78 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp4_AST_in = _t;
			match(_t,PRINT);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			_t = __t78;
			_t = _t->getNextSibling();
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
}

void CalcChecker::type(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST type_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case INT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp5_AST_in = _t;
			match(_t,INT);
			_t = _t->getNextSibling();
			break;
		}
		case FLOAT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp6_AST_in = _t;
			match(_t,FLOAT);
			_t = _t->getNextSibling();
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
}

void CalcChecker::expr(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case INT:
		case FLOAT:
		case IDENTIFIER:
		{
			operand(_t);
			_t = _retTree;
			break;
		}
		case PLUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t80 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp7_AST_in = _t;
			match(_t,PLUS);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t80;
			_t = _t->getNextSibling();
#line 258 "Calc.g"
			/*TODO: type checking*/
#line 223 "CalcChecker.cpp"
			break;
		}
		case MINUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t81 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp8_AST_in = _t;
			match(_t,MINUS);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t81;
			_t = _t->getNextSibling();
#line 259 "Calc.g"
			/*TODO: type checking*/
#line 240 "CalcChecker.cpp"
			break;
		}
		case MUL:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t82 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp9_AST_in = _t;
			match(_t,MUL);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t82;
			_t = _t->getNextSibling();
#line 260 "Calc.g"
			/*TODO: type checking*/
#line 257 "CalcChecker.cpp"
			break;
		}
		case DIV:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t83 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp10_AST_in = _t;
			match(_t,DIV);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t83;
			_t = _t->getNextSibling();
#line 261 "Calc.g"
			/*TODO: type checking*/
#line 274 "CalcChecker.cpp"
			break;
		}
		case POW:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t84 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp11_AST_in = _t;
			match(_t,POW);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t84;
			_t = _t->getNextSibling();
#line 262 "Calc.g"
			/*TODO: type checking*/
#line 291 "CalcChecker.cpp"
			break;
		}
		case SIGN_MINUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t85 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp12_AST_in = _t;
			match(_t,SIGN_MINUS);
			_t = _t->getFirstChild();
			expr(_t);
			_t = _retTree;
			_t = __t85;
			_t = _t->getNextSibling();
#line 263 "Calc.g"
			/*TODO: type checking*/
#line 306 "CalcChecker.cpp"
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
}

void CalcChecker::operand(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST operand_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST id = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case IDENTIFIER:
		{
			id = _t;
			match(_t,IDENTIFIER);
			_t = _t->getNextSibling();
#line 268 "Calc.g"
			if (!isDeclared(id->getText())){
			cerr << id->getText() << " is not declared" << endl;
			exit(-1);
			}
			
#line 342 "CalcChecker.cpp"
			break;
		}
		case INT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp13_AST_in = _t;
			match(_t,INT);
			_t = _t->getNextSibling();
			break;
		}
		case FLOAT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp14_AST_in = _t;
			match(_t,FLOAT);
			_t = _t->getNextSibling();
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
}

void CalcChecker::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* CalcChecker::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"\"print\"",
	"\"int\"",
	"\"float\"",
	"BECOMES",
	"PLUS",
	"MINUS",
	"MUL",
	"DIV",
	"MOD",
	"POW",
	"COLON",
	"SEMICOLON",
	"LPAREN",
	"RPAREN",
	"LBRACKET",
	"RBRACKET",
	"COMMA",
	"LOWER",
	"UPPER",
	"DIGIT",
	"IDENTIFIER",
	"NUMBER",
	"COMMENT",
	"WS",
	"PROGRAM_AST",
	"DECL",
	"SIGN_MINUS",
	"SIGN_PLUS",
	0
};



