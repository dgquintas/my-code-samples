// $ANTLR 2.7.6 (20070206): "python.g" -> "PythonParser.java"$

import antlr.TokenBuffer;
import antlr.TokenStreamException;
import antlr.TokenStreamIOException;
import antlr.ANTLRException;
import antlr.LLkParser;
import antlr.Token;
import antlr.TokenStream;
import antlr.RecognitionException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.ParserSharedInputState;
import antlr.collections.impl.BitSet;

/** Python 2.3.3 Grammar
 *
 *  Terence Parr and Loring Craymer
 *  February 2004
 *
 *  This grammar was derived automatically from the Python 2.3.3
 *  parser grammar to get a syntactically correct ANTLR grammar
 *  for Python.  Then Terence hand tweaked it to be semantically
 *  correct; i.e., removed lookahead issues etc...  It is LL(1)
 *  except for the (sometimes optional) trailing commas and semi-colons.
 *  It needs two symbols of lookahead in this case.
 *
 *  Starting with Loring's preliminary lexer for Python, I modified it
 *  to do my version of the whole nasty INDENT/DEDENT issue just so I
 *  could understand the problem better.  This grammar requires
 *  PythonTokenStream.java to work.  Also I used some rules from the
 *  semi-formal grammar on the web for Python (automatically
 *  translated to ANTLR format by an ANTLR grammar, naturally <grin>).
 *  The lexical rules for python are particularly nasty and it took me
 *  a long time to get it "right"; i.e., think about it in the proper
 *  way.  Resist changing the lexer unless you've used ANTLR a lot. ;)
 *
 *  I (Terence) tested this by running it on the jython-2.1/Lib
 *  directory of 40k lines of Python.
 *
 *  REQUIRES ANTLR 2.7.3rc3 at least (to resolve a FOLLOW bug).
 */
public class PythonParser extends antlr.LLkParser       implements PythonParserTokenTypes
 {

protected PythonParser(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
}

public PythonParser(TokenBuffer tokenBuf) {
  this(tokenBuf,2);
}

protected PythonParser(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
}

public PythonParser(TokenStream lexer) {
  this(lexer,2);
}

public PythonParser(ParserSharedInputState state) {
  super(state,2);
  tokenNames = _tokenNames;
}

	public final void single_input() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NEWLINE:
			{
				match(NEWLINE);
				break;
			}
			case NAME:
			case LPAREN:
			case LITERAL_print:
			case LITERAL_del:
			case LITERAL_pass:
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			case LITERAL_import:
			case LITERAL_from:
			case LITERAL_global:
			case LITERAL_exec:
			case LITERAL_assert:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				simple_stmt();
				break;
			}
			case LITERAL_def:
			case LITERAL_if:
			case LITERAL_while:
			case LITERAL_for:
			case LITERAL_try:
			case LITERAL_class:
			{
				compound_stmt();
				match(NEWLINE);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		}
	}
	
	public final void simple_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			small_stmt();
			{
			_loop30:
			do {
				if ((LA(1)==SEMI) && (_tokenSet_1.member(LA(2)))) {
					match(SEMI);
					small_stmt();
				}
				else {
					break _loop30;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case SEMI:
			{
				match(SEMI);
				break;
			}
			case NEWLINE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			match(NEWLINE);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_2);
		}
	}
	
	public final void compound_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LITERAL_if:
			{
				if_stmt();
				break;
			}
			case LITERAL_while:
			{
				while_stmt();
				break;
			}
			case LITERAL_for:
			{
				for_stmt();
				break;
			}
			case LITERAL_try:
			{
				try_stmt();
				break;
			}
			case LITERAL_def:
			{
				funcdef();
				break;
			}
			case LITERAL_class:
			{
				classdef();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void file_input() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			_loop4:
			do {
				switch ( LA(1)) {
				case NEWLINE:
				{
					match(NEWLINE);
					break;
				}
				case LITERAL_def:
				case NAME:
				case LPAREN:
				case LITERAL_print:
				case LITERAL_del:
				case LITERAL_pass:
				case LITERAL_break:
				case LITERAL_continue:
				case LITERAL_return:
				case LITERAL_yield:
				case LITERAL_raise:
				case LITERAL_import:
				case LITERAL_from:
				case LITERAL_global:
				case LITERAL_exec:
				case LITERAL_assert:
				case LITERAL_if:
				case LITERAL_while:
				case LITERAL_for:
				case LITERAL_try:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				case LITERAL_class:
				{
					stmt();
					break;
				}
				default:
				{
					break _loop4;
				}
				}
			} while (true);
			}
			match(Token.EOF_TYPE);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		}
	}
	
	public final void stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_print:
			case LITERAL_del:
			case LITERAL_pass:
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			case LITERAL_import:
			case LITERAL_from:
			case LITERAL_global:
			case LITERAL_exec:
			case LITERAL_assert:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				simple_stmt();
				break;
			}
			case LITERAL_def:
			case LITERAL_if:
			case LITERAL_while:
			case LITERAL_for:
			case LITERAL_try:
			case LITERAL_class:
			{
				compound_stmt();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void eval_input() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			{
			_loop7:
			do {
				if ((LA(1)==NEWLINE)) {
					match(NEWLINE);
				}
				else {
					break _loop7;
				}
				
			} while (true);
			}
			testlist();
			{
			_loop9:
			do {
				if ((LA(1)==NEWLINE)) {
					match(NEWLINE);
				}
				else {
					break _loop9;
				}
				
			} while (true);
			}
			match(Token.EOF_TYPE);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		}
	}
	
	public final void testlist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			test();
			{
			_loop164:
			do {
				if ((LA(1)==COMMA) && (_tokenSet_4.member(LA(2)))) {
					match(COMMA);
					test();
				}
				else {
					break _loop164;
				}
				
			} while (true);
			}
			{
			if ((LA(1)==COMMA) && (_tokenSet_5.member(LA(2)))) {
				match(COMMA);
			}
			else if ((_tokenSet_5.member(LA(1))) && (_tokenSet_6.member(LA(2)))) {
			}
			else {
				throw new NoViableAltException(LT(1), getFilename());
			}
			
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		}
	}
	
	public final void funcdef() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_def);
			match(NAME);
			parameters();
			match(COLON);
			suite();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void parameters() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LPAREN);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case STAR:
			case DOUBLESTAR:
			{
				varargslist();
				break;
			}
			case RPAREN:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			match(RPAREN);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		}
	}
	
	public final void suite() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_print:
			case LITERAL_del:
			case LITERAL_pass:
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			case LITERAL_import:
			case LITERAL_from:
			case LITERAL_global:
			case LITERAL_exec:
			case LITERAL_assert:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				simple_stmt();
				break;
			}
			case NEWLINE:
			{
				match(NEWLINE);
				match(INDENT);
				{
				int _cnt92=0;
				_loop92:
				do {
					if ((_tokenSet_8.member(LA(1)))) {
						stmt();
					}
					else {
						if ( _cnt92>=1 ) { break _loop92; } else {throw new NoViableAltException(LT(1), getFilename());}
					}
					
					_cnt92++;
				} while (true);
				}
				match(DEDENT);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_2);
		}
	}
	
	public final void varargslist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			{
				defparameter();
				{
				_loop15:
				do {
					if ((LA(1)==COMMA) && (LA(2)==NAME||LA(2)==LPAREN)) {
						match(COMMA);
						defparameter();
					}
					else {
						break _loop15;
					}
					
				} while (true);
				}
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					{
					switch ( LA(1)) {
					case STAR:
					{
						match(STAR);
						match(NAME);
						{
						switch ( LA(1)) {
						case COMMA:
						{
							match(COMMA);
							match(DOUBLESTAR);
							match(NAME);
							break;
						}
						case COLON:
						case RPAREN:
						{
							break;
						}
						default:
						{
							throw new NoViableAltException(LT(1), getFilename());
						}
						}
						}
						break;
					}
					case DOUBLESTAR:
					{
						match(DOUBLESTAR);
						match(NAME);
						break;
					}
					case COLON:
					case RPAREN:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					break;
				}
				case COLON:
				case RPAREN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case STAR:
			{
				match(STAR);
				match(NAME);
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					match(DOUBLESTAR);
					match(NAME);
					break;
				}
				case COLON:
				case RPAREN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case DOUBLESTAR:
			{
				match(DOUBLESTAR);
				match(NAME);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_9);
		}
	}
	
	public final void defparameter() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			fpdef();
			{
			switch ( LA(1)) {
			case ASSIGN:
			{
				match(ASSIGN);
				test();
				break;
			}
			case COLON:
			case RPAREN:
			case COMMA:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_10);
		}
	}
	
	public final void fpdef() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			{
				match(NAME);
				break;
			}
			case LPAREN:
			{
				match(LPAREN);
				fplist();
				match(RPAREN);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_11);
		}
	}
	
	public final void test() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			{
				and_test();
				{
				_loop95:
				do {
					if ((LA(1)==LITERAL_or)) {
						match(LITERAL_or);
						and_test();
					}
					else {
						break _loop95;
					}
					
				} while (true);
				}
				break;
			}
			case LITERAL_lambda:
			{
				lambdef();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		}
	}
	
	public final void fplist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			fpdef();
			{
			_loop25:
			do {
				if ((LA(1)==COMMA) && (LA(2)==NAME||LA(2)==LPAREN)) {
					match(COMMA);
					fpdef();
				}
				else {
					break _loop25;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				break;
			}
			case RPAREN:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_13);
		}
	}
	
	public final void small_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				expr_stmt();
				break;
			}
			case LITERAL_print:
			{
				print_stmt();
				break;
			}
			case LITERAL_del:
			{
				del_stmt();
				break;
			}
			case LITERAL_pass:
			{
				pass_stmt();
				break;
			}
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			{
				flow_stmt();
				break;
			}
			case LITERAL_import:
			case LITERAL_from:
			{
				import_stmt();
				break;
			}
			case LITERAL_global:
			{
				global_stmt();
				break;
			}
			case LITERAL_exec:
			{
				exec_stmt();
				break;
			}
			case LITERAL_assert:
			{
				assert_stmt();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void expr_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			testlist();
			{
			switch ( LA(1)) {
			case PLUSEQUAL:
			case MINUSEQUAL:
			case STAREQUAL:
			case SLASHEQUAL:
			case PERCENTEQUAL:
			case AMPEREQUAL:
			case VBAREQUAL:
			case CIRCUMFLEXEQUAL:
			case LEFTSHIFTEQUAL:
			case RIGHTSHIFTEQUAL:
			case DOUBLESTAREQUAL:
			case DOUBLESLASHEQUAL:
			{
				augassign();
				testlist();
				break;
			}
			case ASSIGN:
			{
				{
				int _cnt36=0;
				_loop36:
				do {
					if ((LA(1)==ASSIGN)) {
						match(ASSIGN);
						testlist();
					}
					else {
						if ( _cnt36>=1 ) { break _loop36; } else {throw new NoViableAltException(LT(1), getFilename());}
					}
					
					_cnt36++;
				} while (true);
				}
				break;
			}
			case NEWLINE:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void print_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_print);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				testlist();
				break;
			}
			case RIGHTSHIFT:
			{
				match(RIGHTSHIFT);
				testlist();
				break;
			}
			case NEWLINE:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void del_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_del);
			exprlist();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void pass_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_pass);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void flow_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LITERAL_break:
			{
				break_stmt();
				break;
			}
			case LITERAL_continue:
			{
				continue_stmt();
				break;
			}
			case LITERAL_return:
			{
				return_stmt();
				break;
			}
			case LITERAL_raise:
			{
				raise_stmt();
				break;
			}
			case LITERAL_yield:
			{
				yield_stmt();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void import_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LITERAL_import:
			{
				match(LITERAL_import);
				dotted_as_name();
				{
				_loop54:
				do {
					if ((LA(1)==COMMA)) {
						match(COMMA);
						dotted_as_name();
					}
					else {
						break _loop54;
					}
					
				} while (true);
				}
				break;
			}
			case LITERAL_from:
			{
				match(LITERAL_from);
				dotted_name();
				match(LITERAL_import);
				{
				switch ( LA(1)) {
				case STAR:
				{
					match(STAR);
					break;
				}
				case NAME:
				{
					import_as_name();
					{
					_loop57:
					do {
						if ((LA(1)==COMMA)) {
							match(COMMA);
							import_as_name();
						}
						else {
							break _loop57;
						}
						
					} while (true);
					}
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void global_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_global);
			match(NAME);
			{
			_loop67:
			do {
				if ((LA(1)==COMMA)) {
					match(COMMA);
					match(NAME);
				}
				else {
					break _loop67;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void exec_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_exec);
			expr();
			{
			switch ( LA(1)) {
			case LITERAL_in:
			{
				match(LITERAL_in);
				test();
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					test();
					break;
				}
				case NEWLINE:
				case SEMI:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case NEWLINE:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void assert_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_assert);
			test();
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				test();
				break;
			}
			case NEWLINE:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void augassign() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case PLUSEQUAL:
			{
				match(PLUSEQUAL);
				break;
			}
			case MINUSEQUAL:
			{
				match(MINUSEQUAL);
				break;
			}
			case STAREQUAL:
			{
				match(STAREQUAL);
				break;
			}
			case SLASHEQUAL:
			{
				match(SLASHEQUAL);
				break;
			}
			case PERCENTEQUAL:
			{
				match(PERCENTEQUAL);
				break;
			}
			case AMPEREQUAL:
			{
				match(AMPEREQUAL);
				break;
			}
			case VBAREQUAL:
			{
				match(VBAREQUAL);
				break;
			}
			case CIRCUMFLEXEQUAL:
			{
				match(CIRCUMFLEXEQUAL);
				break;
			}
			case LEFTSHIFTEQUAL:
			{
				match(LEFTSHIFTEQUAL);
				break;
			}
			case RIGHTSHIFTEQUAL:
			{
				match(RIGHTSHIFTEQUAL);
				break;
			}
			case DOUBLESTAREQUAL:
			{
				match(DOUBLESTAREQUAL);
				break;
			}
			case DOUBLESLASHEQUAL:
			{
				match(DOUBLESLASHEQUAL);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		}
	}
	
	public final void exprlist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			expr();
			{
			_loop160:
			do {
				if ((LA(1)==COMMA) && (_tokenSet_15.member(LA(2)))) {
					match(COMMA);
					expr();
				}
				else {
					break _loop160;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				break;
			}
			case NEWLINE:
			case SEMI:
			case LITERAL_in:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_16);
		}
	}
	
	public final void break_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_break);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void continue_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_continue);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void return_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_return);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				testlist();
				break;
			}
			case NEWLINE:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void raise_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_raise);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				test();
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					test();
					{
					switch ( LA(1)) {
					case COMMA:
					{
						match(COMMA);
						test();
						break;
					}
					case NEWLINE:
					case SEMI:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					break;
				}
				case NEWLINE:
				case SEMI:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case NEWLINE:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void yield_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_yield);
			testlist();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_14);
		}
	}
	
	public final void dotted_as_name() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			dotted_name();
			{
			switch ( LA(1)) {
			case NAME:
			{
				match(NAME);
				match(NAME);
				break;
			}
			case NEWLINE:
			case COMMA:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_17);
		}
	}
	
	public final void dotted_name() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(NAME);
			{
			_loop64:
			do {
				if ((LA(1)==DOT)) {
					match(DOT);
					match(NAME);
				}
				else {
					break _loop64;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_18);
		}
	}
	
	public final void import_as_name() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(NAME);
			{
			switch ( LA(1)) {
			case NAME:
			{
				match(NAME);
				match(NAME);
				break;
			}
			case NEWLINE:
			case COMMA:
			case SEMI:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_17);
		}
	}
	
	public final void expr() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			xor_expr();
			{
			_loop106:
			do {
				if ((LA(1)==VBAR)) {
					match(VBAR);
					xor_expr();
				}
				else {
					break _loop106;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_19);
		}
	}
	
	public final void if_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_if);
			test();
			match(COLON);
			suite();
			{
			_loop76:
			do {
				if ((LA(1)==LITERAL_elif)) {
					match(LITERAL_elif);
					test();
					match(COLON);
					suite();
				}
				else {
					break _loop76;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case LITERAL_else:
			{
				match(LITERAL_else);
				match(COLON);
				suite();
				break;
			}
			case EOF:
			case NEWLINE:
			case LITERAL_def:
			case NAME:
			case LPAREN:
			case LITERAL_print:
			case LITERAL_del:
			case LITERAL_pass:
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			case LITERAL_import:
			case LITERAL_from:
			case LITERAL_global:
			case LITERAL_exec:
			case LITERAL_assert:
			case LITERAL_if:
			case LITERAL_while:
			case LITERAL_for:
			case LITERAL_try:
			case DEDENT:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			case LITERAL_class:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void while_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_while);
			test();
			match(COLON);
			suite();
			{
			switch ( LA(1)) {
			case LITERAL_else:
			{
				match(LITERAL_else);
				match(COLON);
				suite();
				break;
			}
			case EOF:
			case NEWLINE:
			case LITERAL_def:
			case NAME:
			case LPAREN:
			case LITERAL_print:
			case LITERAL_del:
			case LITERAL_pass:
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			case LITERAL_import:
			case LITERAL_from:
			case LITERAL_global:
			case LITERAL_exec:
			case LITERAL_assert:
			case LITERAL_if:
			case LITERAL_while:
			case LITERAL_for:
			case LITERAL_try:
			case DEDENT:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			case LITERAL_class:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void for_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_for);
			exprlist();
			match(LITERAL_in);
			testlist();
			match(COLON);
			suite();
			{
			switch ( LA(1)) {
			case LITERAL_else:
			{
				match(LITERAL_else);
				match(COLON);
				suite();
				break;
			}
			case EOF:
			case NEWLINE:
			case LITERAL_def:
			case NAME:
			case LPAREN:
			case LITERAL_print:
			case LITERAL_del:
			case LITERAL_pass:
			case LITERAL_break:
			case LITERAL_continue:
			case LITERAL_return:
			case LITERAL_yield:
			case LITERAL_raise:
			case LITERAL_import:
			case LITERAL_from:
			case LITERAL_global:
			case LITERAL_exec:
			case LITERAL_assert:
			case LITERAL_if:
			case LITERAL_while:
			case LITERAL_for:
			case LITERAL_try:
			case DEDENT:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			case LITERAL_class:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void try_stmt() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_try);
			match(COLON);
			suite();
			{
			switch ( LA(1)) {
			case LITERAL_except:
			{
				{
				int _cnt85=0;
				_loop85:
				do {
					if ((LA(1)==LITERAL_except)) {
						except_clause();
						match(COLON);
						suite();
					}
					else {
						if ( _cnt85>=1 ) { break _loop85; } else {throw new NoViableAltException(LT(1), getFilename());}
					}
					
					_cnt85++;
				} while (true);
				}
				{
				switch ( LA(1)) {
				case LITERAL_else:
				{
					match(LITERAL_else);
					match(COLON);
					suite();
					break;
				}
				case EOF:
				case NEWLINE:
				case LITERAL_def:
				case NAME:
				case LPAREN:
				case LITERAL_print:
				case LITERAL_del:
				case LITERAL_pass:
				case LITERAL_break:
				case LITERAL_continue:
				case LITERAL_return:
				case LITERAL_yield:
				case LITERAL_raise:
				case LITERAL_import:
				case LITERAL_from:
				case LITERAL_global:
				case LITERAL_exec:
				case LITERAL_assert:
				case LITERAL_if:
				case LITERAL_while:
				case LITERAL_for:
				case LITERAL_try:
				case DEDENT:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				case LITERAL_class:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case LITERAL_finally:
			{
				match(LITERAL_finally);
				match(COLON);
				suite();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void classdef() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_class);
			match(NAME);
			{
			switch ( LA(1)) {
			case LPAREN:
			{
				match(LPAREN);
				testlist();
				match(RPAREN);
				break;
			}
			case COLON:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			match(COLON);
			suite();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		}
	}
	
	public final void except_clause() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_except);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				test();
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					test();
					break;
				}
				case COLON:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case COLON:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		}
	}
	
	public final void and_test() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			not_test();
			{
			_loop98:
			do {
				if ((LA(1)==LITERAL_and)) {
					match(LITERAL_and);
					not_test();
				}
				else {
					break _loop98;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_20);
		}
	}
	
	public final void lambdef() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_lambda);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case STAR:
			case DOUBLESTAR:
			{
				varargslist();
				break;
			}
			case COLON:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			match(COLON);
			test();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_12);
		}
	}
	
	public final void not_test() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LITERAL_not:
			{
				match(LITERAL_not);
				not_test();
				break;
			}
			case NAME:
			case LPAREN:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			{
				comparison();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_21);
		}
	}
	
	public final void comparison() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			expr();
			{
			_loop102:
			do {
				if ((_tokenSet_22.member(LA(1)))) {
					comp_op();
					expr();
				}
				else {
					break _loop102;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_21);
		}
	}
	
	public final void comp_op() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LESS:
			{
				match(LESS);
				break;
			}
			case GREATER:
			{
				match(GREATER);
				break;
			}
			case EQUAL:
			{
				match(EQUAL);
				break;
			}
			case GREATEREQUAL:
			{
				match(GREATEREQUAL);
				break;
			}
			case LESSEQUAL:
			{
				match(LESSEQUAL);
				break;
			}
			case ALT_NOTEQUAL:
			{
				match(ALT_NOTEQUAL);
				break;
			}
			case NOTEQUAL:
			{
				match(NOTEQUAL);
				break;
			}
			case LITERAL_in:
			{
				match(LITERAL_in);
				break;
			}
			case LITERAL_not:
			{
				match(LITERAL_not);
				match(LITERAL_in);
				break;
			}
			default:
				if ((LA(1)==LITERAL_is) && (_tokenSet_15.member(LA(2)))) {
					match(LITERAL_is);
				}
				else if ((LA(1)==LITERAL_is) && (LA(2)==LITERAL_not)) {
					match(LITERAL_is);
					match(LITERAL_not);
				}
			else {
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_15);
		}
	}
	
	public final void xor_expr() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			and_expr();
			{
			_loop109:
			do {
				if ((LA(1)==CIRCUMFLEX)) {
					match(CIRCUMFLEX);
					and_expr();
				}
				else {
					break _loop109;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_23);
		}
	}
	
	public final void and_expr() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			shift_expr();
			{
			_loop112:
			do {
				if ((LA(1)==AMPER)) {
					match(AMPER);
					shift_expr();
				}
				else {
					break _loop112;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_24);
		}
	}
	
	public final void shift_expr() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			arith_expr();
			{
			_loop116:
			do {
				if ((LA(1)==RIGHTSHIFT||LA(1)==LEFTSHIFT)) {
					{
					switch ( LA(1)) {
					case LEFTSHIFT:
					{
						match(LEFTSHIFT);
						break;
					}
					case RIGHTSHIFT:
					{
						match(RIGHTSHIFT);
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					arith_expr();
				}
				else {
					break _loop116;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_25);
		}
	}
	
	public final void arith_expr() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			term();
			{
			_loop120:
			do {
				if ((LA(1)==PLUS||LA(1)==MINUS)) {
					{
					switch ( LA(1)) {
					case PLUS:
					{
						match(PLUS);
						break;
					}
					case MINUS:
					{
						match(MINUS);
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					term();
				}
				else {
					break _loop120;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_26);
		}
	}
	
	public final void term() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			factor();
			{
			_loop124:
			do {
				if ((_tokenSet_27.member(LA(1)))) {
					{
					switch ( LA(1)) {
					case STAR:
					{
						match(STAR);
						break;
					}
					case SLASH:
					{
						match(SLASH);
						break;
					}
					case PERCENT:
					{
						match(PERCENT);
						break;
					}
					case DOUBLESLASH:
					{
						match(DOUBLESLASH);
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					factor();
				}
				else {
					break _loop124;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_28);
		}
	}
	
	public final void factor() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case PLUS:
			case MINUS:
			case TILDE:
			{
				{
				switch ( LA(1)) {
				case PLUS:
				{
					match(PLUS);
					break;
				}
				case MINUS:
				{
					match(MINUS);
					break;
				}
				case TILDE:
				{
					match(TILDE);
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				factor();
				break;
			}
			case NAME:
			case LPAREN:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			{
				power();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_29);
		}
	}
	
	public final void power() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			atom();
			{
			_loop129:
			do {
				if ((LA(1)==LPAREN||LA(1)==DOT||LA(1)==LBRACK)) {
					trailer();
				}
				else {
					break _loop129;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case DOUBLESTAR:
			{
				match(DOUBLESTAR);
				factor();
				break;
			}
			case EOF:
			case NEWLINE:
			case COLON:
			case RPAREN:
			case COMMA:
			case STAR:
			case ASSIGN:
			case SEMI:
			case PLUSEQUAL:
			case MINUSEQUAL:
			case STAREQUAL:
			case SLASHEQUAL:
			case PERCENTEQUAL:
			case AMPEREQUAL:
			case VBAREQUAL:
			case CIRCUMFLEXEQUAL:
			case LEFTSHIFTEQUAL:
			case RIGHTSHIFTEQUAL:
			case DOUBLESTAREQUAL:
			case DOUBLESLASHEQUAL:
			case RIGHTSHIFT:
			case LITERAL_in:
			case LITERAL_if:
			case LITERAL_for:
			case LITERAL_or:
			case LITERAL_and:
			case LITERAL_not:
			case LESS:
			case GREATER:
			case EQUAL:
			case GREATEREQUAL:
			case LESSEQUAL:
			case ALT_NOTEQUAL:
			case NOTEQUAL:
			case LITERAL_is:
			case VBAR:
			case CIRCUMFLEX:
			case AMPER:
			case LEFTSHIFT:
			case PLUS:
			case MINUS:
			case SLASH:
			case PERCENT:
			case DOUBLESLASH:
			case RBRACK:
			case RCURLY:
			case BACKQUOTE:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_29);
		}
	}
	
	public final void atom() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LPAREN:
			{
				match(LPAREN);
				{
				switch ( LA(1)) {
				case NAME:
				case LPAREN:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				{
					testlist();
					break;
				}
				case RPAREN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				match(RPAREN);
				break;
			}
			case LBRACK:
			{
				match(LBRACK);
				{
				switch ( LA(1)) {
				case NAME:
				case LPAREN:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				{
					listmaker();
					break;
				}
				case RBRACK:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				match(RBRACK);
				break;
			}
			case LCURLY:
			{
				match(LCURLY);
				{
				switch ( LA(1)) {
				case NAME:
				case LPAREN:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				{
					dictmaker();
					break;
				}
				case RCURLY:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				match(RCURLY);
				break;
			}
			case BACKQUOTE:
			{
				match(BACKQUOTE);
				testlist();
				match(BACKQUOTE);
				break;
			}
			case NAME:
			{
				match(NAME);
				break;
			}
			case INT:
			{
				match(INT);
				break;
			}
			case LONGINT:
			{
				match(LONGINT);
				break;
			}
			case FLOAT:
			{
				match(FLOAT);
				break;
			}
			case COMPLEX:
			{
				match(COMPLEX);
				break;
			}
			case STRING:
			{
				{
				int _cnt136=0;
				_loop136:
				do {
					if ((LA(1)==STRING)) {
						match(STRING);
					}
					else {
						if ( _cnt136>=1 ) { break _loop136; } else {throw new NoViableAltException(LT(1), getFilename());}
					}
					
					_cnt136++;
				} while (true);
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_30);
		}
	}
	
	public final void trailer() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LPAREN:
			{
				match(LPAREN);
				{
				switch ( LA(1)) {
				case NAME:
				case LPAREN:
				case STAR:
				case DOUBLESTAR:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				{
					arglist();
					break;
				}
				case RPAREN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				match(RPAREN);
				break;
			}
			case LBRACK:
			{
				match(LBRACK);
				subscriptlist();
				match(RBRACK);
				break;
			}
			case DOT:
			{
				match(DOT);
				match(NAME);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_30);
		}
	}
	
	public final void listmaker() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			test();
			{
			switch ( LA(1)) {
			case LITERAL_for:
			{
				list_for();
				break;
			}
			case COMMA:
			case RBRACK:
			{
				{
				_loop140:
				do {
					if ((LA(1)==COMMA) && (_tokenSet_4.member(LA(2)))) {
						match(COMMA);
						test();
					}
					else {
						break _loop140;
					}
					
				} while (true);
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				break;
			}
			case RBRACK:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_31);
		}
	}
	
	public final void dictmaker() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			test();
			match(COLON);
			test();
			{
			_loop168:
			do {
				if ((LA(1)==COMMA) && (_tokenSet_4.member(LA(2)))) {
					match(COMMA);
					test();
					match(COLON);
					test();
				}
				else {
					break _loop168;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				break;
			}
			case RCURLY:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_32);
		}
	}
	
	public final void list_for() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_for);
			exprlist();
			match(LITERAL_in);
			testlist();
			{
			switch ( LA(1)) {
			case LITERAL_if:
			case LITERAL_for:
			{
				list_iter();
				break;
			}
			case COMMA:
			case RBRACK:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_33);
		}
	}
	
	public final void arglist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				argument();
				{
				_loop174:
				do {
					if ((LA(1)==COMMA) && (_tokenSet_4.member(LA(2)))) {
						match(COMMA);
						argument();
					}
					else {
						break _loop174;
					}
					
				} while (true);
				}
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					{
					switch ( LA(1)) {
					case STAR:
					{
						match(STAR);
						test();
						{
						switch ( LA(1)) {
						case COMMA:
						{
							match(COMMA);
							match(DOUBLESTAR);
							test();
							break;
						}
						case RPAREN:
						{
							break;
						}
						default:
						{
							throw new NoViableAltException(LT(1), getFilename());
						}
						}
						}
						break;
					}
					case DOUBLESTAR:
					{
						match(DOUBLESTAR);
						test();
						break;
					}
					case RPAREN:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					break;
				}
				case RPAREN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case STAR:
			{
				match(STAR);
				test();
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					match(DOUBLESTAR);
					test();
					break;
				}
				case RPAREN:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case DOUBLESTAR:
			{
				match(DOUBLESTAR);
				test();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_13);
		}
	}
	
	public final void subscriptlist() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			subscript();
			{
			_loop148:
			do {
				if ((LA(1)==COMMA) && (_tokenSet_34.member(LA(2)))) {
					match(COMMA);
					subscript();
				}
				else {
					break _loop148;
				}
				
			} while (true);
			}
			{
			switch ( LA(1)) {
			case COMMA:
			{
				match(COMMA);
				break;
			}
			case RBRACK:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_31);
		}
	}
	
	public final void subscript() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case DOT:
			{
				match(DOT);
				match(DOT);
				match(DOT);
				break;
			}
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				test();
				{
				switch ( LA(1)) {
				case COLON:
				{
					match(COLON);
					{
					switch ( LA(1)) {
					case NAME:
					case LPAREN:
					case LITERAL_not:
					case PLUS:
					case MINUS:
					case TILDE:
					case LBRACK:
					case LCURLY:
					case BACKQUOTE:
					case INT:
					case LONGINT:
					case FLOAT:
					case COMPLEX:
					case STRING:
					case LITERAL_lambda:
					{
						test();
						break;
					}
					case COLON:
					case COMMA:
					case RBRACK:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					{
					switch ( LA(1)) {
					case COLON:
					{
						sliceop();
						break;
					}
					case COMMA:
					case RBRACK:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(LT(1), getFilename());
					}
					}
					}
					break;
				}
				case COMMA:
				case RBRACK:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			case COLON:
			{
				match(COLON);
				{
				switch ( LA(1)) {
				case NAME:
				case LPAREN:
				case LITERAL_not:
				case PLUS:
				case MINUS:
				case TILDE:
				case LBRACK:
				case LCURLY:
				case BACKQUOTE:
				case INT:
				case LONGINT:
				case FLOAT:
				case COMPLEX:
				case STRING:
				case LITERAL_lambda:
				{
					test();
					break;
				}
				case COLON:
				case COMMA:
				case RBRACK:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				{
				switch ( LA(1)) {
				case COLON:
				{
					sliceop();
					break;
				}
				case COMMA:
				case RBRACK:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(LT(1), getFilename());
				}
				}
				}
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_33);
		}
	}
	
	public final void sliceop() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(COLON);
			{
			switch ( LA(1)) {
			case NAME:
			case LPAREN:
			case LITERAL_not:
			case PLUS:
			case MINUS:
			case TILDE:
			case LBRACK:
			case LCURLY:
			case BACKQUOTE:
			case INT:
			case LONGINT:
			case FLOAT:
			case COMPLEX:
			case STRING:
			case LITERAL_lambda:
			{
				test();
				break;
			}
			case COMMA:
			case RBRACK:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_33);
		}
	}
	
	public final void argument() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			test();
			{
			switch ( LA(1)) {
			case ASSIGN:
			{
				match(ASSIGN);
				test();
				break;
			}
			case RPAREN:
			case COMMA:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_35);
		}
	}
	
	public final void list_iter() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			switch ( LA(1)) {
			case LITERAL_for:
			{
				list_for();
				break;
			}
			case LITERAL_if:
			{
				list_if();
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_33);
		}
	}
	
	public final void list_if() throws RecognitionException, TokenStreamException {
		
		
		try {      // for error handling
			match(LITERAL_if);
			test();
			{
			switch ( LA(1)) {
			case LITERAL_if:
			case LITERAL_for:
			{
				list_iter();
				break;
			}
			case COMMA:
			case RBRACK:
			{
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			recover(ex,_tokenSet_33);
		}
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"NEWLINE",
		"\"def\"",
		"NAME",
		"COLON",
		"LPAREN",
		"RPAREN",
		"COMMA",
		"STAR",
		"DOUBLESTAR",
		"ASSIGN",
		"SEMI",
		"PLUSEQUAL",
		"MINUSEQUAL",
		"STAREQUAL",
		"SLASHEQUAL",
		"PERCENTEQUAL",
		"AMPEREQUAL",
		"VBAREQUAL",
		"CIRCUMFLEXEQUAL",
		"LEFTSHIFTEQUAL",
		"RIGHTSHIFTEQUAL",
		"DOUBLESTAREQUAL",
		"DOUBLESLASHEQUAL",
		"\"print\"",
		"RIGHTSHIFT",
		"\"del\"",
		"\"pass\"",
		"\"break\"",
		"\"continue\"",
		"\"return\"",
		"\"yield\"",
		"\"raise\"",
		"\"import\"",
		"\"from\"",
		"DOT",
		"\"global\"",
		"\"exec\"",
		"\"in\"",
		"\"assert\"",
		"\"if\"",
		"\"elif\"",
		"\"else\"",
		"\"while\"",
		"\"for\"",
		"\"try\"",
		"\"finally\"",
		"\"except\"",
		"INDENT",
		"DEDENT",
		"\"or\"",
		"\"and\"",
		"\"not\"",
		"LESS",
		"GREATER",
		"EQUAL",
		"GREATEREQUAL",
		"LESSEQUAL",
		"ALT_NOTEQUAL",
		"NOTEQUAL",
		"\"is\"",
		"VBAR",
		"CIRCUMFLEX",
		"AMPER",
		"LEFTSHIFT",
		"PLUS",
		"MINUS",
		"SLASH",
		"PERCENT",
		"DOUBLESLASH",
		"TILDE",
		"LBRACK",
		"RBRACK",
		"LCURLY",
		"RCURLY",
		"BACKQUOTE",
		"INT",
		"LONGINT",
		"FLOAT",
		"COMPLEX",
		"STRING",
		"\"lambda\"",
		"\"class\"",
		"NUMBER",
		"Int",
		"NonZeroDigit",
		"FloatTrailer",
		"Exponent",
		"Name",
		"STRING_OR_NAME",
		"String",
		"ESC",
		"CONTINUED_LINE",
		"LEADING_WS",
		"COMMENT",
		"WS"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 2L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 36035118808170816L, 2086448L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { 42781722156204402L, 4183600L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	private static final long[] mk_tokenSet_3() {
		long[] data = { 41040095737807218L, 4183600L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_3 = new BitSet(mk_tokenSet_3());
	private static final long[] mk_tokenSet_4() {
		long[] data = { 36028797018964288L, 2086448L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_4 = new BitSet(mk_tokenSet_4());
	private static final long[] mk_tokenSet_5() {
		long[] data = { 149533715588754L, 18432L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_5 = new BitSet(mk_tokenSet_5());
	private static final long[] mk_tokenSet_6() {
		long[] data = { -2251799813685262L, 4194303L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_6 = new BitSet(mk_tokenSet_6());
	private static final long[] mk_tokenSet_7() {
		long[] data = { 128L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_7 = new BitSet(mk_tokenSet_7());
	private static final long[] mk_tokenSet_8() {
		long[] data = { 36536496110436704L, 4183600L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_8 = new BitSet(mk_tokenSet_8());
	private static final long[] mk_tokenSet_9() {
		long[] data = { 640L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_9 = new BitSet(mk_tokenSet_9());
	private static final long[] mk_tokenSet_10() {
		long[] data = { 1664L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_10 = new BitSet(mk_tokenSet_10());
	private static final long[] mk_tokenSet_11() {
		long[] data = { 9856L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_11 = new BitSet(mk_tokenSet_11());
	private static final long[] mk_tokenSet_12() {
		long[] data = { 149533715588754L, 26624L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_12 = new BitSet(mk_tokenSet_12());
	private static final long[] mk_tokenSet_13() {
		long[] data = { 512L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_13 = new BitSet(mk_tokenSet_13());
	private static final long[] mk_tokenSet_14() {
		long[] data = { 16400L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_14 = new BitSet(mk_tokenSet_14());
	private static final long[] mk_tokenSet_15() {
		long[] data = { 320L, 1037872L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_15 = new BitSet(mk_tokenSet_15());
	private static final long[] mk_tokenSet_16() {
		long[] data = { 2199023271952L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_16 = new BitSet(mk_tokenSet_16());
	private static final long[] mk_tokenSet_17() {
		long[] data = { 17424L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_17 = new BitSet(mk_tokenSet_17());
	private static final long[] mk_tokenSet_18() {
		long[] data = { 68719494224L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_18 = new BitSet(mk_tokenSet_18());
	private static final long[] mk_tokenSet_19() {
		long[] data = { -8855466515896686L, 26624L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_19 = new BitSet(mk_tokenSet_19());
	private static final long[] mk_tokenSet_20() {
		long[] data = { 9156732970329746L, 26624L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_20 = new BitSet(mk_tokenSet_20());
	private static final long[] mk_tokenSet_21() {
		long[] data = { 27171131479811730L, 26624L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_21 = new BitSet(mk_tokenSet_21());
	private static final long[] mk_tokenSet_22() {
		long[] data = { -36026597995708416L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_22 = new BitSet(mk_tokenSet_22());
	private static final long[] mk_tokenSet_23() {
		long[] data = { -8855466515896686L, 26625L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_23 = new BitSet(mk_tokenSet_23());
	private static final long[] mk_tokenSet_24() {
		long[] data = { -8855466515896686L, 26627L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_24 = new BitSet(mk_tokenSet_24());
	private static final long[] mk_tokenSet_25() {
		long[] data = { -8855466515896686L, 26631L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_25 = new BitSet(mk_tokenSet_25());
	private static final long[] mk_tokenSet_26() {
		long[] data = { -8855466247461230L, 26639L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_26 = new BitSet(mk_tokenSet_26());
	private static final long[] mk_tokenSet_27() {
		long[] data = { 2048L, 448L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_27 = new BitSet(mk_tokenSet_27());
	private static final long[] mk_tokenSet_28() {
		long[] data = { -8855466247461230L, 26687L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_28 = new BitSet(mk_tokenSet_28());
	private static final long[] mk_tokenSet_29() {
		long[] data = { -8855466247459182L, 27135L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_29 = new BitSet(mk_tokenSet_29());
	private static final long[] mk_tokenSet_30() {
		long[] data = { -8855191369547886L, 28159L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_30 = new BitSet(mk_tokenSet_30());
	private static final long[] mk_tokenSet_31() {
		long[] data = { 0L, 2048L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_31 = new BitSet(mk_tokenSet_31());
	private static final long[] mk_tokenSet_32() {
		long[] data = { 0L, 8192L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_32 = new BitSet(mk_tokenSet_32());
	private static final long[] mk_tokenSet_33() {
		long[] data = { 1024L, 2048L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_33 = new BitSet(mk_tokenSet_33());
	private static final long[] mk_tokenSet_34() {
		long[] data = { 36029071896871360L, 2086448L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_34 = new BitSet(mk_tokenSet_34());
	private static final long[] mk_tokenSet_35() {
		long[] data = { 1536L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_35 = new BitSet(mk_tokenSet_35());
	
	}
