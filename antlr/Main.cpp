#include<iostream>
#include "ExpressionLexer.hpp"
#include "ExpressionParser.hpp"
#include "ExpressionTreeWalker.hpp"

using namespace std;
using namespace antlr;

int main(){
  ExpressionLexer lexer(cin); 

  ExpressionParser parser(lexer);

  ExpressionTreeWalker walker;
  while(true){

    ASTFactory ast_factory;
    parser.initializeASTFactory(ast_factory);
    parser.setASTFactory(&ast_factory);

    parser.start();
    RefAST parseTree = parser.getAST();
    cout << parseTree->toStringTree() << endl;

    double r = walker.start(parseTree);
    cout << "Value: " << r << endl;
  }
}
