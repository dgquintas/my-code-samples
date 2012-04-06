#ifndef INC_CalcLexer_hpp_
#define INC_CalcLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.6 (20070206): "Calc.g" -> "CalcLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "CalcTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#line 16 "Calc.g"


#include <set>
#include <utility>
#include <iostream>

using namespace std;


#line 22 "CalcLexer.hpp"
class CUSTOM_API CalcLexer : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public CalcTokenTypes
{
#line 1 "Calc.g"
#line 26 "CalcLexer.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	CalcLexer(ANTLR_USE_NAMESPACE(std)istream& in);
	CalcLexer(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	CalcLexer(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mBECOMES(bool _createToken);
	public: void mPLUS(bool _createToken);
	public: void mMINUS(bool _createToken);
	public: void mMUL(bool _createToken);
	public: void mDIV(bool _createToken);
	public: void mMOD(bool _createToken);
	public: void mPOW(bool _createToken);
	public: void mCOLON(bool _createToken);
	public: void mSEMICOLON(bool _createToken);
	public: void mLPAREN(bool _createToken);
	public: void mRPAREN(bool _createToken);
	public: void mLBRACKET(bool _createToken);
	public: void mRBRACKET(bool _createToken);
	public: void mCOMMA(bool _createToken);
	protected: void mLOWER(bool _createToken);
	protected: void mUPPER(bool _createToken);
	protected: void mDIGIT(bool _createToken);
	public: void mIDENTIFIER(bool _createToken);
	public: void mNUMBER(bool _createToken);
	public: void mCOMMENT(bool _createToken);
	public: void mWS(bool _createToken);
private:
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
};

#endif /*INC_CalcLexer_hpp_*/
