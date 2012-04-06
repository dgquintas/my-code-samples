#ifndef INC_ExpressionParser_hpp_
#define INC_ExpressionParser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.6 (20060528): "expression.g" -> "ExpressionParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "ExpressionParserTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

class CUSTOM_API ExpressionParser : public ANTLR_USE_NAMESPACE(antlr)LLkParser, public ExpressionParserTokenTypes
{
#line 1 "expression.g"
#line 15 "ExpressionParser.hpp"
public:
	void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
protected:
	ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k);
public:
	ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf);
protected:
	ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k);
public:
	ExpressionParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer);
	ExpressionParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state);
	int getNumTokens() const
	{
		return ExpressionParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return ExpressionParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return ExpressionParser::tokenNames;
	}
	public: void imaginaryTokenDefinitions();
	public: void start();
	public: void expr();
	public: void sumExpr();
	public: void prodExpr();
	public: void powExpr();
	public: void signedAtom();
	public: void atom();
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
	static const int NUM_TOKENS = 18;
#else
	enum {
		NUM_TOKENS = 18
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
};

#endif /*INC_ExpressionParser_hpp_*/
