#include <iostream>

#include "CalcLexer.hpp"
#include "CalcParser.hpp"
#include "CalcChecker.hpp"
#include "CalcInterpreter.hpp"

using namespace std;
using namespace antlr;


int main() {
  CalcLexer  lexer(cin);
  CalcParser parser(lexer);

  ASTFactory ast_factory;
  parser.initializeASTFactory(ast_factory);
  parser.setASTFactory(&ast_factory);
  parser.program();
  RefAST tree = parser.getAST();
//  cout << tree->toStringTree() << endl;
  // System.out.println("Calc: parsed the program.");

  CalcChecker checker;
  checker.program(tree);

  // System.out.println("Calc: checked the program.");

  CalcInterpreter interpreter; 
  interpreter.program(tree);


}    

