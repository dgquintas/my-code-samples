#ifndef INC_ExpressionLexer_hpp_
#define INC_ExpressionLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.6 (20060528): "expression.g" -> "ExpressionLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "ExpressionParserTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
class CUSTOM_API ExpressionLexer : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public ExpressionParserTokenTypes
{
#line 1 "expression.g"
#line 15 "ExpressionLexer.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	ExpressionLexer(ANTLR_USE_NAMESPACE(std)istream& in);
	ExpressionLexer(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	ExpressionLexer(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mPLUS(bool _createToken);
	public: void mMINUS(bool _createToken);
	public: void mMUL(bool _createToken);
	public: void mDIV(bool _createToken);
	public: void mMOD(bool _createToken);
	public: void mPOW(bool _createToken);
	public: void mSEMI(bool _createToken);
	public: void mLPAREN(bool _createToken);
	public: void mRPAREN(bool _createToken);
	protected: void mDIGIT(bool _createToken);
	public: void mINT(bool _createToken);
	public: void mWS(bool _createToken);
private:
	
};

#endif /*INC_ExpressionLexer_hpp_*/
