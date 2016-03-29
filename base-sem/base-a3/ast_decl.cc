/*
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"


Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this);
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

void VarDecl::PrintChildren(int indentLevel) {
   type->Print(indentLevel+1);
   id->Print(indentLevel+1);
}

void VarDecl::BuildScope(SymbolTable* s){
    scopeTable = new SymbolTable();
    types = new List<Type*>();

    scopeTable = s;
    types->Append(type);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

void ClassDecl::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
    if (extends) extends->Print(indentLevel+1, "(extends) ");
    implements->PrintAll(indentLevel+1, "(implements) ");
    members->PrintAll(indentLevel+1);
}

void ClassDecl::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);

    SymbolTable* current = new SymbolTable();
    current = s;
    bool found = false;
    localScope->SetClassDecl(this);

    for(int i = 0; i < members->NumElements(); i++){
        Decl* curr = members->Nth(i);
        Decl* n = localScope->CheckDecl(curr);
        bool overwrite = false;
        if(n != NULL){
            ReportError::DeclConflict(curr, n);
            return;
        }
        localScope->AddDecl(curr, overwrite);
    }

    if(extends){
        extendedScope = new SymbolTable();
        while(current != NULL && !found){
            Decl* n = current->CheckDecl(extends);
            if(n != NULL){
                found = true;
                extendedScope = current;
                break;
            }
            current = current->GetParentTable();
        }
        if(!found){
            ReportError::IdentifierNotDeclared(extends->GetID(), LookingForClass)
                return;
        }
    }

    if(implements){
        implementedScope = new List<SymbolTable*>();
        current = s;
        found = false;
        Decl* n;
        int count = implements->NumElements();

        for (int i = 0; i <implements->NumElements(); i++){
            current = s;
            while(current != NULL && !found){
                n = current->CheckDecl(implements->Nth(i));
                if(n != NULL){
                    found = true;
                    break;
                }
                current = current->GetParentTable();
            }
            if(!found){
                //Throw error, missing implementation of an interface
                ReportError::IdentifierNotDeclared(implements->Nth(i)->GetID(), LookingForInterface);
            }
            else{
                implementedScope->Append(current);
            }
        }
    }

    for(int i = 0; i < members->NumElements(); i++){
        members->Nth(i)->BuildScope(localScope);
    }
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
    members->PrintAll(indentLevel+1);
}

void InterfaceDecl::BuildScope(SymbolTable* s){
    scopeTable = new SymbolTable();
    scopeTable->SetParentTable(s);

    for (int i = 0; i < members->NumElements(); i++){
        Decl* d = members->Nth(i);
        Decl* n = scopeTable->CheckDecl(d->GetDeclName());
        bool overwrite = false;
        if (n != NULL){
            //Throw error
            ReportError::DeclConflict(d, n);
            return;
        }
        scopeTable->AddDecl(d, overwrite);
    }
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) {
    (body=b)->SetParent(this);
}

void FnDecl::PrintChildren(int indentLevel) {
	if (returnType) returnType->Print(indentLevel+1, "(return type) ");
	if (id) id->Print(indentLevel+1);
	if (formals) formals->PrintAll(indentLevel+1, "(formals) ");

    if (body) body->Print(indentLevel+1, "(body) ");
}

void FnDecl::BuildScope(SymbolTable* parentScope){
    formalsTable = new SymbolTable();
    types = new List<Type*>();
    formalsTable->SetParentTable(parentScope);
    for (int i = 0; i < formals->NumElements(); i++){
        Decl* n = formalsTable->CheckDecl(formals->Nth(i));

        bool overwrite = false;
        if(n != NULL){
            //Throw error and return
            ReportError::DeclConflict(this, n);
        }
        types->Append(formals->Nth(i)->GetType());
        formalsTable->AddDecl(formals->Nth(i), overwrite);
    }

    if(body != NULL){
        body->BuildScope(formalsTable);
    }
}

void FnDecl::Check(){
    if(body != NULL){
        body->Check();
    }
}

