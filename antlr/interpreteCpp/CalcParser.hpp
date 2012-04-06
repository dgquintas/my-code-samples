#ifndef INC_CalcParser_hpp_
#define INC_CalcParser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.6 (20070206): "Calc.g" -> "CalcParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "CalcTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 16 "Calc.g"


#include <set>
#include <utility>
#include <iostream>

using namespace std;


#line 22 "CalcParser.hpp"
class CUSTOM_API CalcParser : public ANTLR_USE_NAMESPACE(antlr)LLkParser, public CalcTokenTypes
{
#line 1 "Calc.g"
#line 26 "CalcParser.hpp"
public:
	void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
protected:
	CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k);
public:
	CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf);
protected:
	CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k);
public:
	CalcParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer);
	CalcParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state);
	int getNumTokens() const
	{
		return CalcParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return CalcParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return CalcParser::tokenNames;
	}
	public: void program();
	public: void declarations();
	public: void statements();
	public: void declaration();
	public: void statement();
	public: void type();
	public: void assignment();
	public: void printStatement();
	public: void lvalue();
	public: void expr();
	public: void sumExpr();
	public: void prodExpr();
	public: void powExpr();
	public: void signedOperand();
	public: void operand();
public:
	ANTLR_USE_NAMESPACE(antlr)RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	ANTLR_USE_NAMESPACE(antlr)RefAST returnAST;
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 32;
#else
	enum {
		NUM_TOKENS = 32
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_4;
	static const unsigned long _tokenSet_5_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_5;
	static const unsigned long _tokenSet_6_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_6;
	static const unsigned long _tokenSet_7_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_7;
	static const unsigned long _tokenSet_8_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_8;
};

#endif /*INC_CalcParser_hpp_*/
