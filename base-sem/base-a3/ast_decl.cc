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
    localScope->SetParentTable(s);

    SymbolTable* current = s;
    bool found = false;
    while(current != NULL && !found){
        Node* n = current->CheckDecl(extends);
        if(n != NULL){
            found = true;
            extendedScope = current;
            break;
        }
        current = current->GetParentTable();
    }
    if(!found){
        //Throw error, missing implementation of a class
        return;
    }

    current = s;
    found = false;
    int count = implements->NumElements();
    while(current != NULL && count != 0 && !found){
        for(int i = 0; i < implements->NumElements(); i++){
            found = false;
            Node* n = current->CheckDecl(implements->Nth(i));
            if(n != NULL){
                count--;
                found = true;
            }
        }
        if(found == true && count == 0){
            implementedScope->Append(current);
            break;
        }
        else if(found == true){
            implementedScope->Append(current);
        }
        else if(count == 0){
            implementedScope->Append(current);
            found = true;
            break;
        }
        current = current->GetParentTable();
    }
    if(!found){
        //Throw error, missing implementation of an interface
        return;
    }

    for(int i = 0; i < members->NumElements(); i++){
        Decl* curr = members->Nth(i);
        Node* n = localScope->CheckDecl(curr);
        bool overwrite = false;
        if(n != NULL){
            //Check for overriding
            //Throw error
            return;
        }
        localScope->AddDecl(curr, overwrite);
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
    formalsTable->SetParentTable(parentScope);
    for (int i = 0; i < formals->NumElements(); i++){
        Node* n = formalsTable->getHashTablePointer()->Lookup(formals->Nth(i)->GetDeclName());
        bool overwrite = false;
        if(n != NULL){
            //Throw error and return
            return;
        }
        formalsTable->AddDecl(formals->Nth(i), overwrite);
    }

    body->BuildScope(formalsTable);
}

