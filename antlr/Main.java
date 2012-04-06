import java.io.*;
import antlr.CommonAST;
import antlr.collections.AST;
import antlr.debug.misc.ASTFrame;
public class Main {
  public static void main(String args[]) {
    try {
      DataInputStream input = new DataInputStream(System.in);

      ExpressionLexer lexer = new ExpressionLexer(input); 

      ExpressionParser parser = new ExpressionParser(lexer);

      ExpressionTreeWalker walker = new ExpressionTreeWalker();
      while(true){
        parser.start();

        CommonAST parseTree = (CommonAST)parser.getAST();
        System.out.println(parseTree.toStringList());
        //ASTFrame frame = new ASTFrame("The tree", parseTree);
        //frame.setVisible(true);

        double r = walker.expr(parseTree);
        System.out.println("Value: "+r);

      }

    } catch(Exception e) { System.err.println("Exception: "+e); }
  }
}
