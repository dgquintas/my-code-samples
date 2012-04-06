#ifndef INC_ExpressionParserTokenTypes_hpp_
#define INC_ExpressionParserTokenTypes_hpp_

/* $ANTLR 2.7.6 (20060528): "expression.g" -> "ExpressionParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API ExpressionParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		SIGN_MINUS = 4,
		SIGN_PLUS = 5,
		SEMI = 6,
		PLUS = 7,
		MINUS = 8,
		MUL = 9,
		DIV = 10,
		MOD = 11,
		POW = 12,
		INT = 13,
		LPAREN = 14,
		RPAREN = 15,
		DIGIT = 16,
		WS = 17,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_ExpressionParserTokenTypes_hpp_*/
