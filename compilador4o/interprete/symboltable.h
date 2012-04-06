#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <string>
#include <map>
#include <functional>

using namespace std;

class Code;

typedef enum{ SLabel} SymbolType;

class STNode
{
  public:
    virtual SymbolType type() = 0;
};

class LabelNode: public STNode
{
  public:
    LabelNode(int i);
    int getInstr() const;
    SymbolType type();
  private:
    int _instr;
};

class SymbolTable
{
  public:
    STNode* lookup(string);
    int lookupLabel(string);
    void addEntry(string, STNode *);

  private:
    map<string, STNode*, less<string> > _table;
};

#endif
