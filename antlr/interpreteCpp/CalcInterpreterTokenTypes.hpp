#ifndef INC_CalcInterpreterTokenTypes_hpp_
#define INC_CalcInterpreterTokenTypes_hpp_

/* $ANTLR 2.7.6 (20070206): "CalcInterpreter.g" -> "CalcInterpreterTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API CalcInterpreterTokenTypes {
#endif
	enum {
		EOF_ = 1,
		PRINT = 4,
		INT = 5,
		FLOAT = 6,
		BECOMES = 7,
		PLUS = 8,
		MINUS = 9,
		MUL = 10,
		DIV = 11,
		MOD = 12,
		POW = 13,
		COLON = 14,
		SEMICOLON = 15,
		LPAREN = 16,
		RPAREN = 17,
		LBRACKET = 18,
		RBRACKET = 19,
		COMMA = 20,
		LOWER = 21,
		UPPER = 22,
		DIGIT = 23,
		IDENTIFIER = 24,
		NUMBER = 25,
		COMMENT = 26,
		WS = 27,
		PROGRAM_AST = 28,
		DECL = 29,
		SIGN_MINUS = 30,
		SIGN_PLUS = 31,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_CalcInterpreterTokenTypes_hpp_*/
