/*
 * In our AST Decl nodes are used to represent and manage
 * declarations. There are 4 subclasses of the base class, specialized
 * for declarations of variables, functions, classes, and interfaces.
 * Some error classes are also defined (see parser.y for the
 * rationale).
 *
 * Assignment 3: You will need to extend the Decl classes to implement
 * semantic processing including detection of declaration conflicts
 * and managing scoping issues.
 */

#ifndef _ast_decl_h
#define _ast_decl_h

#include "ast.h"
#include "list.h"
#include "ast_stmt.h"

class Type;
class NamedType;
class Identifier;
class Stmt;

void yyerror(const char *msg);

class Decl : public Node
{
  protected:
    Identifier *id;
    List<Type*>* types;
    SymbolTable* scopeTable;

  public:
    Decl() : id(NULL) {}
    Decl(Identifier *name);
    bool IsCompatible(Type* compatee, SymbolTable* s);
    virtual Decl* GetExtendScope() { return NULL; }
    virtual List<Decl*>* GetImplementScope() { return NULL; }
    virtual bool isInterface() { return false; }
    virtual List<VarDecl*>* GetFormals() { return NULL; }
    virtual List<Decl*>* GetMembers() { return NULL; }
    virtual SymbolTable* GetScope() { return NULL; }
    virtual Identifier* GetID() { return id; }
    virtual List<Type*>* GetTypes() { return types; }
    virtual Type* GetType() { return NULL; }
    virtual const char* GetDeclName() { return id->GetName(); }
    friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id; }
};

class VarDecl : public Decl
{
  protected:
    Type *type;

  public:
    VarDecl() : type(NULL) {}
    VarDecl(Identifier *name, Type *type);
    Type* GetType() { return type; }
    void BuildScope(SymbolTable* s);
    const char *GetPrintNameForNode() { return "VarDecl"; }
    void PrintChildren(int indentLevel);
};

class ClassDecl : public Decl
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;
    Decl* extendedScope;
    List<Decl*>* implementedScope;
    SymbolTable* localScope;

  public:

    ClassDecl(Identifier *name, NamedType *extends,
              List<NamedType*> *implements, List<Decl*> *members);
    void BuildScope(SymbolTable* s);
    void Check();
    List<Decl*>* GetMembers() { return members; }
    SymbolTable* GetScope() { return this->localScope; }
    Decl* GetExtendScope() { return extendedScope; }
    List<Decl*>* GetImplementScope() { return implementedScope; }
    bool CheckOverriding(int i, Decl* extendC, SymbolTable* parentT);
    const char *GetPrintNameForNode() { return "ClassDecl"; }
    void PrintChildren(int indentLevel);
};

class VarDeclError : public VarDecl
{
  public:
    VarDeclError() : VarDecl() { yyerror(this->GetPrintNameForNode()); };
    const char *GetPrintNameForNode() { return "VarDeclError"; }
};

class InterfaceDecl : public Decl
{
  protected:
    List<Decl*> *members;

  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    const char *GetPrintNameForNode() { return "InterfaceDecl"; }
    void BuildScope(SymbolTable* s);
    void Check();
    bool isInterface() { return true; }
    List<Decl*>* GetMembers() { return members; }
    void PrintChildren(int indentLevel);
};

class FnDecl : public Decl
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    SymbolTable* formalsTable;

  public:
    FnDecl() : Decl(), formals(NULL), returnType(NULL), body(NULL) {}
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    List<VarDecl*>* GetFormals() { return formals; }
    void BuildScope(SymbolTable* s);
    Type* GetType() { return returnType; }
    void Check();
    const char* GetDeclName() { return id->GetName(); }
    const char *GetPrintNameForNode() { return "FnDecl"; }
    void PrintChildren(int indentLevel);
};

class FormalsError : public FnDecl
{
  public:
    FormalsError() : FnDecl() { yyerror(this->GetPrintNameForNode()); }
    const char *GetPrintNameForNode() { return "FormalsError"; }
};

#endif
