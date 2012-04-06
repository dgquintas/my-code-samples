// [file: Calc.java, started: 5-Apr-2003]
//
// Driver for Calc compiler.
//
// CHANGES
//      2003.04.05  ruys  Started (VB 2003).
//      2004.04.12  ruys  Modifications for VB 2004.
//                         -  AST is not longer re-built by Treeparsers.
//                         -  CalcChecker can now throw a CalcException.

import java.io.*;
import antlr.*;
import antlr.collections.AST;
import antlr.debug.misc.*;              // needed for ASTFrame

/**
 * Program that creates and starts the Calc lexer, parser, etc.
 * @author  Theo Ruys
 * @version 2004.04.12
 */
public class Calc {
    private static boolean  opt_showAST         = false,
                            opt_showASTFrame    = false,
                            opt_noChecker       = false,
                            opt_noInterpreter   = false;
    
    public static void parseOptions(String[] args) {
        for (int i=0; i<args.length; i++) {
            if (args[i].equals("-showAST"))
                opt_showAST = true;
            else if (args[i].equals("-showASTFrame"))
                opt_showASTFrame = true;
            else if (args[i].equals("-noChecker"))
                opt_noChecker = true;
            else if (args[i].equals("-noInterpreter"))
                opt_noInterpreter = true;
            else {
                System.err.println("error: unknown option '" + args[i] + "'");
                System.err.println("valid options: -showAST -showASTFrame " +
                                   "-noChecker -noInterpreter");
                System.exit(1);
            }
        }
    }
        
    public static void main(String[] args) {
        parseOptions(args);
        
        try {
            CalcLexer  lexer  = new CalcLexer(new DataInputStream(System.in));
            CalcParser parser = new CalcParser(lexer);
            
            parser.program();
            AST tree = parser.getAST();
            // System.out.println("Calc: parsed the program.");
            
            if (! opt_noChecker) { // check the AST
                CalcChecker checker = new CalcChecker();
                checker.program(tree);
                // System.out.println("Calc: checked the program.");
            }

            if (! opt_noInterpreter) { // interpret the AST               
                CalcInterpreter interpreter = new CalcInterpreter();
                interpreter.program(tree);
                // System.out.println("Calc: interpreted the program.");
            }

            if (opt_showAST) {
                String s = tree.toStringList();
                System.out.println("AST = " + s);
            }
            
            if (opt_showASTFrame) {
                ASTFrame frame = new ASTFrame("Calc Program as AST", tree);
                frame.setSize(500,500);
                frame.setVisible(true);
            } 
            
        } catch (CalcException e) { 
            System.err.print("ERROR: CalcException thrown by compiler: ");
            System.err.println(e.getMessage());
            e.printStackTrace();
        } catch (Exception e) { 
            System.err.print("ERROR: uncaught exception thrown by compiler: ");
            System.err.println(e.getMessage());
            e.printStackTrace();
        }
    }    
}

