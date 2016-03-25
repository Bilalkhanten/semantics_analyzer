/*
 * This file defines the abstract base class Node and the concrete
 * Identifier and Error node subclasses that are used through the tree
 * as leaf nodes. An AST is a hierarchical collection of AST nodes
 * (or, more correctly, of instances of concrete subclassses such as
 * VarDecl, ForStmt, and AssignExpr).
 *
 * Location: Each node maintains its lexical location (line and
 * columns in file), that location can be NULL for those nodes that
 * don't care/use locations. The location is typcially set by the node
 * constructor.  The location is used to provide the context when
 * reporting semantic errors.
 *
 * Parent: Each node has a pointer to its parent. For a Program node,
 * the parent is NULL, for all other nodes it is the pointer to the
 * node one level up in the AST.  The parent is not set in the
 * constructor (during a bottom-up parse we don't know the parent at
 * the time of construction) but instead we wait until assigning the
 * children into the parent node and then set up links in both
 * directions. The parent link is typically not used during parsing,
 * but is more important in later phases.
 *
 * Printing: The only interesting behavior of the node classes for
 * Assignment 2 is the bility to print the tree using an in-order
 * walk.  Each node class is responsible for printing itself/children
 * by overriding the virtual PrintChildren() and GetPrintNameForNode()
 * member functions. All the classes we provide already implement
 * these member functions, so your job is to construct the nodes and
 * wire them up during parsing. Once that's done, printing is a snap!
 * Recursive printing is no longer required for Assignment 3, but the
 * code is kept so that you can still use this code to verify the
 * solution for Assignment 2.
 *
 * Semantic analysis: For Assignment 3 you are adding the "Check"
 * behavior to the ast node classes. Your semantic analyzer should do
 * a walk on the AST, and when visiting each node, verify the
 * particular semantic rules that apply to that construct.
 */

#ifndef _ast_h
#define _ast_h

#include <stdlib.h>   // for NULL
#include "location.h"
#include <iostream>
#include "hashtable.h"
using namespace std;

class SymbolTable;

class Node  {
  protected:
    yyltype *location;
    Node *parent;

  public:
    Node(yyltype loc);
    Node();
    virtual ~Node() {}

    yyltype *GetLocation()   { return location; }
    void SetParent(Node *p)  { parent = p; }
    Node *GetParent()        { return parent; }
    bool needsSymbolTable()  { return false;}
    virtual void Check() { }
    virtual void BuildScope() { }
    virtual void BuildScope(SymbolTable* parentScope) { }
    virtual const char *GetPrintNameForNode() = 0;

    // Print() is deliberately _not_ virtual
    // subclasses should override PrintChildren() instead
    void Print(int indentLevel, const char *label = NULL);
    virtual void PrintChildren(int indentLevel)  {}
};


class Identifier : public Node
{
  protected:
    char *name;

  public:
    Identifier(yyltype loc, const char *name);
    const char *GetName() { return name; }
    const char *GetPrintNameForNode()   { return "Identifier"; }
    void PrintChildren(int indentLevel);
    friend ostream& operator<<(ostream& out, Identifier *id) { return out << id->name; }
};

// This node class is designed to represent a portion of the tree that
// encountered syntax errors during parsing. The partial completed
// tree is discarded along with the states being popped, and an
// instance of the Error class can stand in as the placeholder in the
// AST when your parser can continue after an error.
class Error : public Node
{
  public:
    Error() : Node() {}
    const char *GetPrintNameForNode()   { return "Error"; }
};



#endif
