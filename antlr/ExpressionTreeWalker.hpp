#ifndef INC_ExpressionTreeWalker_hpp_
#define INC_ExpressionTreeWalker_hpp_

#include <antlr/config.hpp>
#include "ExpressionParserTokenTypes.hpp"
/* $ANTLR 2.7.6 (20060528): "expression.g" -> "ExpressionTreeWalker.hpp"$ */
#include <antlr/TreeParser.hpp>

class CUSTOM_API ExpressionTreeWalker : public ANTLR_USE_NAMESPACE(antlr)TreeParser, public ExpressionParserTokenTypes
{
#line 1 "expression.g"
#line 13 "ExpressionTreeWalker.hpp"
public:
	ExpressionTreeWalker();
	static void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
	int getNumTokens() const
	{
		return ExpressionTreeWalker::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return ExpressionTreeWalker::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return ExpressionTreeWalker::tokenNames;
	}
	public: double  start(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
public:
	ANTLR_USE_NAMESPACE(antlr)RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	ANTLR_USE_NAMESPACE(antlr)RefAST returnAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST _retTree;
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 18;
#else
	enum {
		NUM_TOKENS = 18
	};
#endif
	
};

#endif /*INC_ExpressionTreeWalker_hpp_*/
