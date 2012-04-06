// $ANTLR 2.7.6 (20060528): "Calc.g" -> "CalcChecker.java"$

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

public class CalcChecker extends antlr.TreeParser       implements CalcTokenTypes
 {
 
    Set<String> idset = new HashSet<String>();   
    
    public boolean  isDeclared(String s)     { return idset.contains(s); }
    public void     declare(String s)        { idset.add(s);             }
public CalcChecker() {
	tokenNames = _tokenNames;
}

	public final void program(AST _t) throws RecognitionException {
		
		AST program_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		AST __t55 = _t;
		AST tmp1_AST_in = (AST)_t;
		match(_t,PROGRAM_AST);
		_t = _t.getFirstChild();
		{
		int _cnt57=0;
		_loop57:
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
				if ( _cnt57>=1 ) { break _loop57; } else {throw new NoViableAltException(_t);}
			}
			}
			_cnt57++;
		} while (true);
		}
		_t = __t55;
		_t = _t.getNextSibling();
		_retTree = _t;
	}
	
	public final void declaration(AST _t) throws RecognitionException {
		
		AST declaration_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		
		AST __t59 = _t;
		AST tmp2_AST_in = (AST)_t;
		match(_t,DECL);
		_t = _t.getFirstChild();
		type(_t);
		_t = _retTree;
		id = (AST)_t;
		match(_t,IDENTIFIER);
		_t = _t.getNextSibling();
		_t = __t59;
		_t = _t.getNextSibling();
		if (isDeclared(id.getText()))
		throw new CalcException(id.getText() + " is already declared");
		else 
		declare(id.getText()); 
		
		_retTree = _t;
	}
	
	public final void statement(AST _t) throws RecognitionException {
		
		AST statement_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case BECOMES:
		{
			AST __t61 = _t;
			AST tmp3_AST_in = (AST)_t;
			match(_t,BECOMES);
			_t = _t.getFirstChild();
			id = (AST)_t;
			match(_t,IDENTIFIER);
			_t = _t.getNextSibling();
			expr(_t);
			_t = _retTree;
			_t = __t61;
			_t = _t.getNextSibling();
			if (!isDeclared(id.getText()))
			throw new CalcException(id.getText() + " is not declared");
			
			break;
		}
		case PRINT:
		{
			AST __t62 = _t;
			AST tmp4_AST_in = (AST)_t;
			match(_t,PRINT);
			_t = _t.getFirstChild();
			expr(_t);
			_t = _retTree;
			_t = __t62;
			_t = _t.getNextSibling();
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		_retTree = _t;
	}
	
	public final void type(AST _t) throws RecognitionException {
		
		AST type_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
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
		_retTree = _t;
	}
	
	public final void expr(AST _t) throws RecognitionException {
		
		AST expr_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case IDENTIFIER:
		case INT:
		case FLOAT:
		{
			operand(_t);
			_t = _retTree;
			break;
		}
		case PLUS:
		{
			AST __t64 = _t;
			AST tmp7_AST_in = (AST)_t;
			match(_t,PLUS);
			_t = _t.getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t64;
			_t = _t.getNextSibling();
			break;
		}
		case MINUS:
		{
			AST __t65 = _t;
			AST tmp8_AST_in = (AST)_t;
			match(_t,MINUS);
			_t = _t.getFirstChild();
			expr(_t);
			_t = _retTree;
			expr(_t);
			_t = _retTree;
			_t = __t65;
			_t = _t.getNextSibling();
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		_retTree = _t;
	}
	
	public final void operand(AST _t) throws RecognitionException {
		
		AST operand_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST id = null;
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case IDENTIFIER:
		{
			id = (AST)_t;
			match(_t,IDENTIFIER);
			_t = _t.getNextSibling();
			if (!isDeclared(id.getText()))
			throw new CalcException(id.getText() + " is not declared");
			
			break;
		}
		case INT:
		{
			AST tmp9_AST_in = (AST)_t;
			match(_t,INT);
			_t = _t.getNextSibling();
			break;
		}
		case FLOAT:
		{
			AST tmp10_AST_in = (AST)_t;
			match(_t,FLOAT);
			_t = _t.getNextSibling();
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		_retTree = _t;
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
	
