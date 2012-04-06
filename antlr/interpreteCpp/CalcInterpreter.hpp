#ifndef INC_CalcInterpreter_hpp_
#define INC_CalcInterpreter_hpp_

#include <antlr/config.hpp>
#include "CalcInterpreterTokenTypes.hpp"
/* $ANTLR 2.7.6 (20070206): "CalcInterpreter.g" -> "CalcInterpreter.hpp"$ */
#include <antlr/TreeParser.hpp>

#line 19 "CalcInterpreter.g"
 
  #include <iostream>
  #include <map>
  #include <utility>
  #include <cmath>

  using namespace std;

#line 19 "CalcInterpreter.hpp"
class CUSTOM_API CalcInterpreter : public ANTLR_USE_NAMESPACE(antlr)TreeParser, public CalcInterpreterTokenTypes
{
#line 41 "CalcInterpreter.g"
 
    map<string,float> store;   
#line 23 "CalcInterpreter.hpp"
public:
	CalcInterpreter();
	static void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
	int getNumTokens() const
	{
		return CalcInterpreter::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return CalcInterpreter::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return CalcInterpreter::tokenNames;
	}
	public: void program(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void declaration(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void statement(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: void type(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: float  expr(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
	public: float  operand(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
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

#endif /*INC_CalcInterpreter_hpp_*/
