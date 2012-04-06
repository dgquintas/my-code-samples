#ifndef INC_CalcChecker_hpp_
#define INC_CalcChecker_hpp_

#include <antlr/config.hpp>
#include "CalcTokenTypes.hpp"
/* $ANTLR 2.7.6 (20070206): "Calc.g" -> "CalcChecker.hpp"$ */
#include <antlr/TreeParser.hpp>

#line 16 "Calc.g"


#include <set>
#include <utility>
#include <iostream>

using namespace std;


#line 20 "CalcChecker.hpp"
class CUSTOM_API CalcChecker : public ANTLR_USE_NAMESPACE(antlr)TreeParser, public CalcTokenTypes
{
#line 218 "Calc.g"
 
    set<string> idset; 
public:
    bool  isDeclared(string s)     { return (idset.find(s) != idset.end()); }
    void  declare(string s)        { idset.insert(s);             }
#line 24 "CalcChecker.hpp"
public:
	CalcChecker();
	static void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
	int getNumTokens() const
	{
		return CalcChecker::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return CalcChecker::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return CalcChecker::tokenNames;
	}
	public: void program(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void declaration(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void statement(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void type(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void expr(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void operand(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
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
	static const int NUM_TOKENS = 32;
#else
	enum {
		NUM_TOKENS = 32
	};
#endif
	
};

#endif /*INC_CalcChecker_hpp_*/
