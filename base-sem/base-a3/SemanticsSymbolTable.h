#ifndef SEMANTICSSYMBOLTABLE_H
#define SEMANTICSSYMBOLTABLE_H


class SemanticsSymbolTable
{
    public:
        SemanticsSymbolTable();
        HashTable<Node*> getHashTable();
    private:
        Hashtable<Node*> h;
};

#endif // SEMANTICSSYMBOLTABLE_H
