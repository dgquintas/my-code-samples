/* $ANTLR 2.7.6 (20070206): "Calc.g" -> "CalcParser.cpp"$ */
#include "CalcParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "Calc.g"
#line 8 "CalcParser.cpp"
CalcParser::CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

CalcParser::CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,1)
{
}

CalcParser::CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

CalcParser::CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,1)
{
}

CalcParser::CalcParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,1)
{
}

void CalcParser::program() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST program_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		declarations();
		astFactory->addASTChild( currentAST, returnAST );
		statements();
		astFactory->addASTChild( currentAST, returnAST );
		match(ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE);
		program_AST = ANTLR_USE_NAMESPACE(antlr)RefAST(currentAST.root);
#line 139 "Calc.g"
		program_AST = ANTLR_USE_NAMESPACE(antlr)RefAST(astFactory->make((new ANTLR_USE_NAMESPACE(antlr)ASTArray(2))->add(astFactory->create(PROGRAM_AST,"program"))->add(program_AST))) ;
#line 48 "CalcParser.cpp"
		currentAST.root = program_AST;
		if ( program_AST!=ANTLR_USE_NAMESPACE(antlr)nullAST &&
			program_AST->getFirstChild() != ANTLR_USE_NAMESPACE(antlr)nullAST )
			  currentAST.child = program_AST->getFirstChild();
		else
			currentAST.child = program_AST;
		currentAST.advanceChildToEnd();
		program_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_0);
	}
	returnAST = program_AST;
}

void CalcParser::declarations() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST declarations_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == INT || LA(1) == FLOAT)) {
				declaration();
				astFactory->addASTChild( currentAST, returnAST );
				match(SEMICOLON);
			}
			else {
				goto _loop46;
			}
			
		}
		_loop46:;
		} // ( ... )*
		declarations_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_1);
	}
	returnAST = declarations_AST;
}

void CalcParser::statements() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST statements_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		{ // ( ... )+
		int _cnt49=0;
		for (;;) {
			if ((LA(1) == PRINT || LA(1) == IDENTIFIER)) {
				statement();
				astFactory->addASTChild( currentAST, returnAST );
				match(SEMICOLON);
			}
			else {
				if ( _cnt49>=1 ) { goto _loop49; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt49++;
		}
		_loop49:;
		}  // ( ... )+
		statements_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_0);
	}
	returnAST = statements_AST;
}

void CalcParser::declaration() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST declaration_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		type();
		astFactory->addASTChild( currentAST, returnAST );
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp18_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp18_AST = astFactory->create(LT(1));
		astFactory->addASTChild(currentAST, tmp18_AST);
		match(IDENTIFIER);
		declaration_AST = ANTLR_USE_NAMESPACE(antlr)RefAST(currentAST.root);
#line 154 "Calc.g"
		declaration_AST = ANTLR_USE_NAMESPACE(antlr)RefAST(astFactory->make((new ANTLR_USE_NAMESPACE(antlr)ASTArray(2))->add(astFactory->create(DECL,"declaration"))->add(declaration_AST))) ;
#line 140 "CalcParser.cpp"
		currentAST.root = declaration_AST;
		if ( declaration_AST!=ANTLR_USE_NAMESPACE(antlr)nullAST &&
			declaration_AST->getFirstChild() != ANTLR_USE_NAMESPACE(antlr)nullAST )
			  currentAST.child = declaration_AST->getFirstChild();
		else
			currentAST.child = declaration_AST;
		currentAST.advanceChildToEnd();
		declaration_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_2);
	}
	returnAST = declaration_AST;
}

void CalcParser::statement() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST statement_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		switch ( LA(1)) {
		case IDENTIFIER:
		{
			assignment();
			astFactory->addASTChild( currentAST, returnAST );
			statement_AST = currentAST.root;
			break;
		}
		case PRINT:
		{
			printStatement();
			astFactory->addASTChild( currentAST, returnAST );
			statement_AST = currentAST.root;
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
		recover(ex,_tokenSet_2);
	}
	returnAST = statement_AST;
}

void CalcParser::type() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST type_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		switch ( LA(1)) {
		case INT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp19_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp19_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp19_AST);
			match(INT);
			type_AST = currentAST.root;
			break;
		}
		case FLOAT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp20_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp20_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp20_AST);
			match(FLOAT);
			type_AST = currentAST.root;
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
		recover(ex,_tokenSet_3);
	}
	returnAST = type_AST;
}

void CalcParser::assignment() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST assignment_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		lvalue();
		astFactory->addASTChild( currentAST, returnAST );
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp21_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp21_AST = astFactory->create(LT(1));
		astFactory->makeASTRoot(currentAST, tmp21_AST);
		match(BECOMES);
		expr();
		astFactory->addASTChild( currentAST, returnAST );
		assignment_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_2);
	}
	returnAST = assignment_AST;
}

void CalcParser::printStatement() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST printStatement_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp22_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp22_AST = astFactory->create(LT(1));
		astFactory->makeASTRoot(currentAST, tmp22_AST);
		match(PRINT);
		expr();
		astFactory->addASTChild( currentAST, returnAST );
		printStatement_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_2);
	}
	returnAST = printStatement_AST;
}

void CalcParser::lvalue() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST lvalue_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp23_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp23_AST = astFactory->create(LT(1));
		astFactory->addASTChild(currentAST, tmp23_AST);
		match(IDENTIFIER);
		lvalue_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_4);
	}
	returnAST = lvalue_AST;
}

void CalcParser::expr() {
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
		recover(ex,_tokenSet_5);
	}
	returnAST = expr_AST;
}

void CalcParser::sumExpr() {
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
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp24_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp24_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp24_AST);
					match(PLUS);
					break;
				}
				case MINUS:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp25_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp25_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp25_AST);
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
				goto _loop59;
			}
			
		}
		_loop59:;
		} // ( ... )*
		sumExpr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_5);
	}
	returnAST = sumExpr_AST;
}

void CalcParser::prodExpr() {
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
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp26_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp26_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp26_AST);
					match(MUL);
					break;
				}
				case DIV:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp27_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp27_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp27_AST);
					match(DIV);
					break;
				}
				case MOD:
				{
					ANTLR_USE_NAMESPACE(antlr)RefAST tmp28_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
					tmp28_AST = astFactory->create(LT(1));
					astFactory->makeASTRoot(currentAST, tmp28_AST);
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
				goto _loop63;
			}
			
		}
		_loop63:;
		} // ( ... )*
		prodExpr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_6);
	}
	returnAST = prodExpr_AST;
}

void CalcParser::powExpr() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST powExpr_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		signedOperand();
		astFactory->addASTChild( currentAST, returnAST );
		{
		switch ( LA(1)) {
		case POW:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp29_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp29_AST = astFactory->create(LT(1));
			astFactory->makeASTRoot(currentAST, tmp29_AST);
			match(POW);
			powExpr();
			astFactory->addASTChild( currentAST, returnAST );
			break;
		}
		case PLUS:
		case MINUS:
		case MUL:
		case DIV:
		case MOD:
		case SEMICOLON:
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
		recover(ex,_tokenSet_7);
	}
	returnAST = powExpr_AST;
}

void CalcParser::signedOperand() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST signedOperand_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
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
#line 190 "Calc.g"
			m_AST->setType(SIGN_MINUS);
#line 490 "CalcParser.cpp"
			break;
		}
		case PLUS:
		{
			p = LT(1);
			p_AST = astFactory->create(p);
			match(PLUS);
#line 191 "Calc.g"
			p_AST->setType(SIGN_PLUS);
#line 500 "CalcParser.cpp"
			break;
		}
		case INT:
		case FLOAT:
		case LPAREN:
		case IDENTIFIER:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		operand();
		astFactory->addASTChild( currentAST, returnAST );
		signedOperand_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_8);
	}
	returnAST = signedOperand_AST;
}

void CalcParser::operand() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST operand_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		switch ( LA(1)) {
		case IDENTIFIER:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp30_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp30_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp30_AST);
			match(IDENTIFIER);
			operand_AST = currentAST.root;
			break;
		}
		case INT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp31_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp31_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp31_AST);
			match(INT);
			operand_AST = currentAST.root;
			break;
		}
		case FLOAT:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp32_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp32_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp32_AST);
			match(FLOAT);
			operand_AST = currentAST.root;
			break;
		}
		case LPAREN:
		{
			match(LPAREN);
			expr();
			astFactory->addASTChild( currentAST, returnAST );
			match(RPAREN);
			operand_AST = currentAST.root;
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
		recover(ex,_tokenSet_8);
	}
	returnAST = operand_AST;
}

void CalcParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory )
{
	factory.setMaxNodeType(31);
}
const char* CalcParser::tokenNames[] = {
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

const unsigned long CalcParser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long CalcParser::_tokenSet_1_data_[] = { 16777232UL, 0UL, 0UL, 0UL };
// "print" IDENTIFIER 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long CalcParser::_tokenSet_2_data_[] = { 32768UL, 0UL, 0UL, 0UL };
// SEMICOLON 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_2(_tokenSet_2_data_,4);
const unsigned long CalcParser::_tokenSet_3_data_[] = { 16777216UL, 0UL, 0UL, 0UL };
// IDENTIFIER 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_3(_tokenSet_3_data_,4);
const unsigned long CalcParser::_tokenSet_4_data_[] = { 128UL, 0UL, 0UL, 0UL };
// BECOMES 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_4(_tokenSet_4_data_,4);
const unsigned long CalcParser::_tokenSet_5_data_[] = { 163840UL, 0UL, 0UL, 0UL };
// SEMICOLON RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_5(_tokenSet_5_data_,4);
const unsigned long CalcParser::_tokenSet_6_data_[] = { 164608UL, 0UL, 0UL, 0UL };
// PLUS MINUS SEMICOLON RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_6(_tokenSet_6_data_,4);
const unsigned long CalcParser::_tokenSet_7_data_[] = { 171776UL, 0UL, 0UL, 0UL };
// PLUS MINUS MUL DIV MOD SEMICOLON RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_7(_tokenSet_7_data_,4);
const unsigned long CalcParser::_tokenSet_8_data_[] = { 179968UL, 0UL, 0UL, 0UL };
// PLUS MINUS MUL DIV MOD POW SEMICOLON RPAREN 
const ANTLR_USE_NAMESPACE(antlr)BitSet CalcParser::_tokenSet_8(_tokenSet_8_data_,4);


