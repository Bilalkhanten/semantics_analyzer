/*
 * The Stmt class and its subclasses are used to represent statements
 * in the AST.  For each statment in the language (for, if, return,
 * etc.) there is a corresponding node class for that construct.  Some
 * error classes are also provided.
 *
 * Assignment 3: You will need to extend the Stmt classes to implement
 * semantic analysis for rules pertaining to statements.
 */

#ifndef _ast_stmt_h
#define _ast_stmt_h

#include "list.h"
#include "ast.h"
#include "hashtable.h"

class Decl;
class VarDecl;
class FnDecl;
class Expr;
class IntConstant;
class NamedType;

void yyerror(const char *msg);

class SymbolTable {
  private:
    Hashtable<Node*>* symbolTable;
    SymbolTable* parentTable;

  public:
    SymbolTable();
    void SetParentTable(SymbolTable* parentTable) { this->parentTable = parentTable;}
    SymbolTable* GetParentTable() { return parentTable; }
    Node* CheckDecl(Decl* d);
    Node* CheckDecl(NamedType* d);
    Node* CheckDecl(const char* d);
    void AddDecl(Decl* newEntry, bool overwrite);
    Hashtable<Node*>* getHashTablePointer();
};

class Program : public Node
{
  protected:
     List<Decl*> *decls;
     SymbolTable* globalSymbolTable;

  public:
     Program(List<Decl*> *declList);
     void Check();
     void BuildScope();
     bool needsSymbolTable() { return true; }
     const char *GetPrintNameForNode() { return "Program"; }
     void PrintChildren(int indentLevel);
};

class Stmt : public Node
{
  protected:
     SymbolTable* localScope;

  public:
     Stmt() : Node() { }
     Stmt(yyltype loc) : Node(loc) {}
};

class StmtBlock : public Stmt
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;

  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    void BuildScope(SymbolTable* s);
    const char *GetPrintNameForNode() { return "StmtBlock"; }
    void PrintChildren(int indentLevel);
};


class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;

  public:
    ConditionalStmt() : Stmt(), test(NULL), body(NULL) {}
    ConditionalStmt(Expr *testExpr, Stmt *body);
    void BuildScope(SymbolTable* s);
};

class LoopStmt : public ConditionalStmt
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
};

class ForStmt : public LoopStmt
{
  protected:
    Expr *init, *step;

  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    const char *GetPrintNameForNode() { return "ForStmt"; }
    void BuildScope(SymbolTable* s);
    void PrintChildren(int indentLevel);
};

class WhileStmt : public LoopStmt
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    const char *GetPrintNameForNode() { return "WhileStmt"; }
    void BuildScope(SymbolTable* s);
    void PrintChildren(int indentLevel);
};

class IfStmt : public ConditionalStmt
{
  protected:
    Stmt *elseBody;

  public:
    IfStmt() : ConditionalStmt(), elseBody(NULL) {}
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    const char *GetPrintNameForNode() { return "IfStmt"; }
    void BuildScope(SymbolTable* s);
    void PrintChildren(int indentLevel);
};

class IfStmtExprError : public IfStmt
{
  public:
    IfStmtExprError() : IfStmt() { yyerror(this->GetPrintNameForNode()); }
    const char *GetPrintNameForNode() { return "IfStmtExprError"; }
};

class BreakStmt : public Stmt
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    const char *GetPrintNameForNode() { return "BreakStmt"; }
};

class ReturnStmt : public Stmt
{
  protected:
    Expr *expr;

  public:
    ReturnStmt(yyltype loc, Expr *expr);
    const char *GetPrintNameForNode() { return "ReturnStmt"; }
    void PrintChildren(int indentLevel);
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;

  public:
    PrintStmt(List<Expr*> *arguments);
    const char *GetPrintNameForNode() { return "PrintStmt"; }
    void PrintChildren(int indentLevel);
};

class SwitchLabel : public Stmt
{
  protected:
    IntConstant *label;
    List<Stmt*> *stmts;

  public:
    SwitchLabel(IntConstant *label, List<Stmt*> *stmts);
    SwitchLabel(List<Stmt*> *stmts);
    void PrintChildren(int indentLevel);
    void BuildScope(SymbolTable* s);
};

class Case : public SwitchLabel
{
  public:
    Case(IntConstant *label, List<Stmt*> *stmts) : SwitchLabel(label, stmts) {}
    const char *GetPrintNameForNode() { return "Case"; }
};

class Default : public SwitchLabel
{
  public:
    Default(List<Stmt*> *stmts) : SwitchLabel(stmts) {}
    const char *GetPrintNameForNode() { return "Default"; }
};

class SwitchStmt : public Stmt
{
  protected:
    Expr *expr;
    List<Case*> *cases;
    Default *def;

  public:
    SwitchStmt() : expr(NULL), cases(NULL), def(NULL) {}
    SwitchStmt(Expr *expr, List<Case*> *cases, Default *def);
    const char *GetPrintNameForNode() { return "SwitchStmt"; }
    void PrintChildren(int indentLevel);
};

class SwitchStmtError : public SwitchStmt
{
  public:
    SwitchStmtError(const char * msg) { yyerror(msg); }
    const char *GetPrintNameForNode() { return "SwitchStmtError"; }
};

#endif
