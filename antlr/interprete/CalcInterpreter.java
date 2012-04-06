// $ANTLR 2.7.6 (20060528): "CalcInterpreter.g" -> "CalcInterpreter.java"$

    import java.io.*;

import antlr.TreeParser;
import antlr.Token;
import antlr.collections.AST;
import antlr.RecognitionException;
import antlr.ANTLRException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.collections.impl.BitSet;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;
 import java.util.*; 

public class CalcInterpreter extends antlr.TreeParser       implements CalcInterpreterTokenTypes
 {
 
    Map<String,Float> store = new HashMap<String,Float>();   
public CalcInterpreter() {
	tokenNames = _tokenNames;
}

	public final void program(AST _t) throws RecognitionException {
		
		AST program_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			AST __t2 = _t;
			AST tmp1_AST_in = (AST)_t;
			match(_t,PROGRAM_AST);
			_t = _t.getFirstChild();
			{
			int _cnt4=0;
			_loop4:
			do {
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case DECL:
				{
					declaration(_t);
					_t = _retTree;
					break;
				}
				case BECOMES:
				case PRINT:
				{
					statement(_t);
					_t = _retTree;
					break;
				}
				default:
				{
					if ( _cnt4>=1 ) { break _loop4; } else {throw new NoViableAltException(_t);}
				}
				}
				_cnt4++;
			} while (true);
			}
			_t = __t2;
			_t = _t.getNextSibling();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final void declaration(AST _t) throws RecognitionException {
		
		AST declaration_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		
		try {      // for error handling
			AST __t6 = _t;
			AST tmp2_AST_in = (AST)_t;
			match(_t,DECL);
			_t = _t.getFirstChild();
			type(_t);
			_t = _retTree;
			id = (AST)_t;
			match(_t,IDENTIFIER);
			_t = _t.getNextSibling();
			_t = __t6;
			_t = _t.getNextSibling();
			store.put(id.getText(), 0.0F);
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final void statement(AST _t) throws RecognitionException {
		
		AST statement_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		float v = 0;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case BECOMES:
			{
				AST __t8 = _t;
				AST tmp3_AST_in = (AST)_t;
				match(_t,BECOMES);
				_t = _t.getFirstChild();
				id = (AST)_t;
				match(_t,IDENTIFIER);
				_t = _t.getNextSibling();
				v=expr(_t);
				_t = _retTree;
				_t = __t8;
				_t = _t.getNextSibling();
				store.put(id.getText(), v);
				break;
			}
			case PRINT:
			{
				AST __t9 = _t;
				AST tmp4_AST_in = (AST)_t;
				match(_t,PRINT);
				_t = _t.getFirstChild();
				v=expr(_t);
				_t = _retTree;
				_t = __t9;
				_t = _t.getNextSibling();
				System.out.println("" + v);
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final void type(AST _t) throws RecognitionException {
		
		AST type_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case INT:
			{
				AST tmp5_AST_in = (AST)_t;
				match(_t,INT);
				_t = _t.getNextSibling();
				break;
			}
			case FLOAT:
			{
				AST tmp6_AST_in = (AST)_t;
				match(_t,FLOAT);
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final float  expr(AST _t) throws RecognitionException {
		float val;
		
		AST expr_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		float x, y; val = 0;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case IDENTIFIER:
			case INT:
			case FLOAT:
			{
				val=operand(_t);
				_t = _retTree;
				break;
			}
			case PLUS:
			{
				AST __t11 = _t;
				AST tmp7_AST_in = (AST)_t;
				match(_t,PLUS);
				_t = _t.getFirstChild();
				x=expr(_t);
				_t = _retTree;
				y=expr(_t);
				_t = _retTree;
				_t = __t11;
				_t = _t.getNextSibling();
				val = x + y;
				break;
			}
			case MINUS:
			{
				AST __t12 = _t;
				AST tmp8_AST_in = (AST)_t;
				match(_t,MINUS);
				_t = _t.getFirstChild();
				x=expr(_t);
				_t = _retTree;
				y=expr(_t);
				_t = _retTree;
				_t = __t12;
				_t = _t.getNextSibling();
				val = x - y;
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return val;
	}
	
	public final float  operand(AST _t) throws RecognitionException {
		float val = 0;
		
		AST operand_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		AST i = null;
		AST f = null;
		
		try {      // for error handling
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case IDENTIFIER:
			{
				id = (AST)_t;
				match(_t,IDENTIFIER);
				_t = _t.getNextSibling();
				val = store.get(id.getText());
				break;
			}
			case INT:
			{
				i = (AST)_t;
				match(_t,INT);
				_t = _t.getNextSibling();
				val = Integer.parseInt(i.getText());
				break;
			}
			case FLOAT:
			{
				f = (AST)_t;
				match(_t,FLOAT);
				_t = _t.getNextSibling();
				val = Float.parseFloat(f.getText());
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
		return val;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"PROGRAM_AST",
		"DECL",
		"SEMICOLON",
		"IDENTIFIER",
		"BECOMES",
		"\"print\"",
		"LPAREN",
		"RPAREN",
		"PLUS",
		"MINUS",
		"\"int\"",
		"\"float\"",
		"COLON",
		"LOWER",
		"UPPER",
		"DIGIT",
		"NUMBER",
		"COMMENT",
		"WS"
	};
	
	}
	
