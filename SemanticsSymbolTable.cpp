#include "SemanticsSymbolTable.h"

SemanticsSymbolTable::SemanticsSymbolTable()
{
    h = new Hashtable();
}

Hashtable<Node*>* SemanticsSymbolTable::getHashTable(){
    return this.h;
}
