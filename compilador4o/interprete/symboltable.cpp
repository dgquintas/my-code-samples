#include "symboltable.h"

LabelNode::LabelNode(int i)
  : _instr(i)
{}

int
LabelNode::getInstr() const
{
  return _instr;
}

SymbolType 
LabelNode::type()
{
  return SLabel;
}

////////////////////////////////////////

STNode*
SymbolTable::lookup(string str)
{
  map<string, STNode*, less<string> >::iterator it;
  if( (it = _table.find(str)) != _table.end() )
    return (*it).second;
  else
    return NULL;
}

int
SymbolTable::lookupLabel(string etiqueta)
{
  STNode* nodo;
  nodo = lookup(etiqueta);
  if( nodo && (nodo->type() == SLabel) )
    return dynamic_cast<LabelNode*>(nodo)->getInstr();
  else
    return -1;
}
    
    

void
SymbolTable::addEntry(string str, STNode* nodo)
{
  _table[str] = nodo;
  return;
}

  
