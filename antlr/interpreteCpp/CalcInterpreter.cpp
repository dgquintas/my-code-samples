/* $ANTLR 2.7.6 (20070206): "CalcInterpreter.g" -> "CalcInterpreter.cpp"$ */
#include "CalcInterpreter.hpp"
#include <antlr/Token.hpp>
#include <antlr/AST.hpp>
#include <antlr/NoViableAltException.hpp>
#include <antlr/MismatchedTokenException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/BitSet.hpp>
#line 1 "CalcInterpreter.g"
#line 11 "CalcInterpreter.cpp"
CalcInterpreter::CalcInterpreter()
	: ANTLR_USE_NAMESPACE(antlr)TreeParser() {
}

void CalcInterpreter::program(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST program_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST __t2 = _t;
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp1_AST_in = _t;
		match(_t,PROGRAM_AST);
		_t = _t->getFirstChild();
		{ // ( ... )+
		int _cnt4=0;
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
				if ( _cnt4>=1 ) { goto _loop4; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(_t);}
			}
			}
			_cnt4++;
		}
		_loop4:;
		}  // ( ... )+
		_t = __t2;
		_t = _t->getNextSibling();
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		if ( _t != ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = _t->getNextSibling();
	}
	_retTree = _t;
}

void CalcInterpreter::declaration(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST declaration_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST id = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST __t6 = _t;
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp2_AST_in = _t;
		match(_t,DECL);
		_t = _t->getFirstChild();
		type(_t);
		_t = _retTree;
		id = _t;
		match(_t,IDENTIFIER);
		_t = _t->getNextSibling();
		_t = __t6;
		_t = _t->getNextSibling();
#line 51 "CalcInterpreter.g"
		store[id->getText()] = 0.0;
#line 81 "CalcInterpreter.cpp"
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		if ( _t != ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = _t->getNextSibling();
	}
	_retTree = _t;
}

void CalcInterpreter::statement(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
	ANTLR_USE_NAMESPACE(antlr)RefAST statement_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST id = ANTLR_USE_NAMESPACE(antlr)nullAST;
#line 54 "CalcInterpreter.g"
	float v = 0;
#line 96 "CalcInterpreter.cpp"
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case BECOMES:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t8 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp3_AST_in = _t;
			match(_t,BECOMES);
			_t = _t->getFirstChild();
			id = _t;
			match(_t,IDENTIFIER);
			_t = _t->getNextSibling();
			v=expr(_t);
			_t = _retTree;
			_t = __t8;
			_t = _t->getNextSibling();
#line 56 "CalcInterpreter.g"
			store[id->getText()] = v;
			
#line 118 "CalcInterpreter.cpp"
			break;
		}
		case PRINT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t9 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp4_AST_in = _t;
			match(_t,PRINT);
			_t = _t->getFirstChild();
			v=expr(_t);
			_t = _retTree;
			_t = __t9;
			_t = _t->getNextSibling();
#line 59 "CalcInterpreter.g"
			cout << v << endl;
#line 133 "CalcInterpreter.cpp"
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

void CalcInterpreter::type(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
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

float  CalcInterpreter::expr(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
#line 62 "CalcInterpreter.g"
	float val;
#line 188 "CalcInterpreter.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
#line 62 "CalcInterpreter.g"
	float x, y; val = 0;
#line 192 "CalcInterpreter.cpp"
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case INT:
		case FLOAT:
		case IDENTIFIER:
		{
			val=operand(_t);
			_t = _retTree;
			break;
		}
		case PLUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t11 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp7_AST_in = _t;
			match(_t,PLUS);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			y=expr(_t);
			_t = _retTree;
			_t = __t11;
			_t = _t->getNextSibling();
#line 64 "CalcInterpreter.g"
			val = x + y;
#line 220 "CalcInterpreter.cpp"
			break;
		}
		case MINUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t12 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp8_AST_in = _t;
			match(_t,MINUS);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			y=expr(_t);
			_t = _retTree;
			_t = __t12;
			_t = _t->getNextSibling();
#line 65 "CalcInterpreter.g"
			val = x - y;
#line 237 "CalcInterpreter.cpp"
			break;
		}
		case MUL:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t13 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp9_AST_in = _t;
			match(_t,MUL);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			y=expr(_t);
			_t = _retTree;
			_t = __t13;
			_t = _t->getNextSibling();
#line 66 "CalcInterpreter.g"
			val = x * y;
#line 254 "CalcInterpreter.cpp"
			break;
		}
		case DIV:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t14 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp10_AST_in = _t;
			match(_t,DIV);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			y=expr(_t);
			_t = _retTree;
			_t = __t14;
			_t = _t->getNextSibling();
#line 67 "CalcInterpreter.g"
			val = x / y;
#line 271 "CalcInterpreter.cpp"
			break;
		}
		case POW:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t15 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp11_AST_in = _t;
			match(_t,POW);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			y=expr(_t);
			_t = _retTree;
			_t = __t15;
			_t = _t->getNextSibling();
#line 68 "CalcInterpreter.g"
			val = powf(x,y);
#line 288 "CalcInterpreter.cpp"
			break;
		}
		case MOD:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t16 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp12_AST_in = _t;
			match(_t,MOD);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			y=expr(_t);
			_t = _retTree;
			_t = __t16;
			_t = _t->getNextSibling();
#line 69 "CalcInterpreter.g"
			val = fmodf(x,y);
#line 305 "CalcInterpreter.cpp"
			break;
		}
		case SIGN_MINUS:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t17 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp13_AST_in = _t;
			match(_t,SIGN_MINUS);
			_t = _t->getFirstChild();
			x=expr(_t);
			_t = _retTree;
			_t = __t17;
			_t = _t->getNextSibling();
#line 70 "CalcInterpreter.g"
			val = -x;
#line 320 "CalcInterpreter.cpp"
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
	return val;
}

float  CalcInterpreter::operand(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
#line 73 "CalcInterpreter.g"
	float val = 0;
#line 341 "CalcInterpreter.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefAST operand_AST_in = (_t == ANTLR_USE_NAMESPACE(antlr)RefAST(ASTNULL)) ? ANTLR_USE_NAMESPACE(antlr)nullAST : _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST id = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST i = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST f = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case IDENTIFIER:
		{
			id = _t;
			match(_t,IDENTIFIER);
			_t = _t->getNextSibling();
#line 74 "CalcInterpreter.g"
			val = store[id->getText()];
#line 358 "CalcInterpreter.cpp"
			break;
		}
		case INT:
		{
			i = _t;
			match(_t,INT);
			_t = _t->getNextSibling();
#line 75 "CalcInterpreter.g"
			val = atoi(i->getText().c_str());
#line 368 "CalcInterpreter.cpp"
			break;
		}
		case FLOAT:
		{
			f = _t;
			match(_t,FLOAT);
			_t = _t->getNextSibling();
#line 76 "CalcInterpreter.g"
			val = atof(f->getText().c_str());
#line 378 "CalcInterpreter.cpp"
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
	return val;
}

void CalcInterpreter::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* CalcInterpreter::tokenNames[] = {
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



