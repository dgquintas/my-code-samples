/* $ANTLR 2.7.6 (20060528): "expression.g" -> "ExpressionParser.cpp"$ */
#include "ExpressionParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "expression.g"
#line 8 "ExpressionParser.cpp"
ExpressionParser::ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

ExpressionParser::ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,1)
{
}

ExpressionParser::ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

ExpressionParser::ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,1)
{
}

ExpressionParser::ExpressionParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,1)
{
}

void ExpressionParser::imaginaryTokenDefinitions() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST imaginaryTokenDefinitions_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp9_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp9_AST = astFactory->create(LT(1));
		astFactory->addASTChild(currentAST, tmp9_AST);
		match(SIGN_MINUS);
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp10_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp10_AST = astFactory->create(LT(1));
		astFactory->addASTChild(currentAST, tmp10_AST);
		match(SIGN_PLUS);
		imaginaryTokenDefinitions_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_0);
	}
	returnAST = imaginaryTokenDefinitions_AST;
}

void ExpressionParser::start() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST start_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		expr();
		astFactory->addASTChild( currentAST, returnAST );
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp11_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp11_AST = astFactory->create(LT(1));
		astFactory->addASTChild(currentAST, tmp11_AST);
		match(SEMI);
		start_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_0);
	}
	returnAST = start_AST;
}

void ExpressionParser::expr() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		sumExpr();
		astFactory->addASTChild( currentAST, returnAST );
		expr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_1);
	}
	returnAST = expr_AST;
}

void ExpressionParser::sumExpr() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST sumExpr_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		prodExpr();
		astFactory->addASTChild( currentAST, returnAST );
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == PLUS || LA(1) == MINUS)) {
				{
				switch ( LA(1)) {
				case PLUS:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp12_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp12_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp12_AST);
					match(PLUS);
					break;
				}
				case MINUS:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp13_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp13_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp13_AST);
					match(MINUS);
					break;
				}
				default:
				{
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				}
				}
				prodExpr();
				astFactory->addASTChild( currentAST, returnAST );
			}
			else {
				goto _loop7;
			}
			
		}
		_loop7:;
		} // ( ... )*
		sumExpr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_2);
	}
	returnAST = sumExpr_AST;
}

void ExpressionParser::prodExpr() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST prodExpr_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		powExpr();
		astFactory->addASTChild( currentAST, returnAST );
		{ // ( ... )*
		for (;;) {
			if (((LA(1) >= MUL && LA(1) <= MOD))) {
				{
				switch ( LA(1)) {
				case MUL:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp14_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp14_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp14_AST);
					match(MUL);
					break;
				}
				case DIV:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp15_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp15_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp15_AST);
					match(DIV);
					break;
				}
				case MOD:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp16_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp16_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp16_AST);
					match(MOD);
					break;
				}
				default:
				{
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				}
				}
				powExpr();
				astFactory->addASTChild( currentAST, returnAST );
			}
			else {
				goto _loop11;
			}
			
		}
		_loop11:;
		} // ( ... )*
		prodExpr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_3);
	}
	returnAST = prodExpr_AST;
}

void ExpressionParser::powExpr() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST powExpr_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		signedAtom();
		astFactory->addASTChild( currentAST, returnAST );
		{
		switch ( LA(1)) {
		case POW:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp17_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp17_AST = astFactory->create(LT(1));
			astFactory->makeASTRoot(currentAST, tmp17_AST);
			match(POW);
			powExpr();
			astFactory->addASTChild( currentAST, returnAST );
			break;
		}
		case SEMI:
		case PLUS:
		case MINUS:
		case MUL:
		case DIV:
		case MOD:
		case RPAREN:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		powExpr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_4);
	}
	returnAST = powExpr_AST;
}

void ExpressionParser::signedAtom() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST signedAtom_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)RefToken  m = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefAST m_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)RefToken  p = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefAST p_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case MINUS:
		{
			m = LT(1);
			m_AST = astFactory->create(m);
			astFactory->makeASTRoot(currentAST, m_AST);
			match(MINUS);
#line 16 "expression.g"
			m_AST->setType(SIGN_MINUS);
#line 276 "ExpressionParser.cpp"
			break;
		}
		case PLUS:
		{
			p = LT(1);
			p_AST = astFactory->create(p);
			match(PLUS);
#line 17 "expression.g"
			p_AST->setType(SIGN_PLUS);
#line 286 "ExpressionParser.cpp"
			break;
		}
		case INT:
		case LPAREN:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		atom();
		astFactory->addASTChild( currentAST, returnAST );
		signedAtom_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_5);
	}
	returnAST = signedAtom_AST;
}

void ExpressionParser::atom() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST atom_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		switch ( LA(1)) {
		case INT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp18_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp18_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp18_AST);
			match(INT);
			atom_AST = currentAST.root;
			break;
		}
		case LPAREN:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp19_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp19_AST = astFactory->create(LT(1));
			astFactory->makeASTRoot(currentAST, tmp19_AST);
			match(LPAREN);
			sumExpr();
			astFactory->addASTChild( currentAST, returnAST );
			match(RPAREN);
			atom_AST = currentAST.root;
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_5);
	}
	returnAST = atom_AST;
}

void ExpressionParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory )
{
	factory.setMaxNodeType(17);
}
const char* ExpressionParser::tokenNames[] = {
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

const unsigned long ExpressionParser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet ExpressionParser::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long ExpressionParser::_tokenSet_1_data_[] = { 64UL, 0UL, 0UL, 0UL };
// SEMI 
const ANTLR_USE_NAMESPACE(antlr)BitSet ExpressionParser::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long ExpressionParser::_tokenSet_2_data_[] = { 32832UL, 0UL, 0UL, 0UL };
// SEMI RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet ExpressionParser::_tokenSet_2(_tokenSet_2_data_,4);
const unsigned long ExpressionParser::_tokenSet_3_data_[] = { 33216UL, 0UL, 0UL, 0UL };
// SEMI PLUS MINUS RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet ExpressionParser::_tokenSet_3(_tokenSet_3_data_,4);
const unsigned long ExpressionParser::_tokenSet_4_data_[] = { 36800UL, 0UL, 0UL, 0UL };
// SEMI PLUS MINUS MUL DIV MOD RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet ExpressionParser::_tokenSet_4(_tokenSet_4_data_,4);
const unsigned long ExpressionParser::_tokenSet_5_data_[] = { 40896UL, 0UL, 0UL, 0UL };
// SEMI PLUS MINUS MUL DIV MOD POW RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet ExpressionParser::_tokenSet_5(_tokenSet_5_data_,4);


