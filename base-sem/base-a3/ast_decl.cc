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
    localScope->SetName(id->GetName());
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
        while(current != NULL && !found){
            Decl* n = current->CheckDecl(extends);
            if(n != NULL){
                found = true;
                extendedScope = n;
                if(n->GetScope() == NULL){
                    cout << "Not a class: " << n->GetDeclName() << endl;
                    ReportError::IdentifierNotDeclared(extends->GetID(), LookingForClass);
                    extends = NULL;
                }
                else if (n->GetScope()->GetName() == NULL){
                    cout << "Not a class: " << n->GetDeclName() << endl;
                    ReportError::IdentifierNotDeclared(extends->GetID(), LookingForClass);
                    extends = NULL;
                }

                break;
            }
            current = current->GetParentTable();
        }
        if(!found){
            ReportError::IdentifierNotDeclared(extends->GetID(), LookingForClass);
            extends = NULL;
            //return;
        }
    }

    if(implements){
        implementedScope = new List<Decl*>();
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
                    if(!(n->isInterface())){
                        cout << "Not an interface: " << n->GetDeclName() << endl;
                    }
                    break;
                }
                current = current->GetParentTable();
            }
            if(!found){
                //Throw error, missing implementation of an interface
                ReportError::IdentifierNotDeclared(implements->Nth(i)->GetID(), LookingForInterface);
            }
            else{
                implementedScope->Append(n);
            }
        }
    }

    for(int i = 0; i < members->NumElements(); i++){
        members->Nth(i)->BuildScope(localScope);
    }
}

void ClassDecl::Check(){
    if(implements){
        for(int i = 0; i < implementedScope->NumElements(); i++){
            Decl* interfaceD = implementedScope->Nth(i);
            List<Decl*>* listD = interfaceD->GetMembers();
            List<VarDecl*>* classVars = new List<VarDecl*>();
            List<VarDecl*>* interVars = new List<VarDecl*>();

            for(int i = 0; i < listD->NumElements(); i++){
                Decl* declInt = listD->Nth(i);
                Decl* classDecl = localScope->CheckDecl(declInt);
                if(classDecl != NULL){
                    classVars = classDecl->GetFormals();
                    interVars = declInt->GetFormals();

                    if(classVars->NumElements() != interVars->NumElements()){
                        cout << "class: " <<  classVars->Nth(i) << endl;
                        ReportError::InterfaceNotImplemented(this, implements->Nth(i));
                        continue;
                    }

                    for(int i = 0; i < classVars->NumElements(); i++){
                        if(classVars->Nth(i)->GetType() != interVars->Nth(i)->GetType()){
                            ReportError::InterfaceNotImplemented(this, implements->Nth(i));
                            break;
                        }
                    }
                }
                else{
                    ReportError::InterfaceNotImplemented(this, implements->Nth(i));
                }
            }
        }
    }

    if(extends){
        SymbolTable* parentT = localScope->GetParentTable();
        Decl* extendC = parentT->CheckDecl(extends);
        bool found = false;

        for(int i = 0; i < members->NumElements(); i++){
            found = CheckOverriding(i, extendC, parentT); //Add to get a recursive call to extend classes
        }
    }

    for(int i = 0; i < members->NumElements(); i++){
        members->Nth(i)->Check();
    }
}

bool ClassDecl::CheckOverriding(int i, Decl* extendC, SymbolTable* parentT){
    //extendC = parentT->CheckDecl(extends);
    bool found = false;

    Decl* member = members->Nth(i);
    Decl* memberEx = extendC->GetScope()->CheckDecl(member);
    if(member->GetFormals() == NULL){
        cout << "null" << endl;
        if(memberEx != NULL){
            ReportError::OverrideVarError(member, extendC);
        }
        else{
            Decl* extendNext = extendC->GetExtendScope();
            if(extendNext != NULL){
                return CheckOverriding(i, extendNext, parentT);
            }
            else{
                ReportError::OverrideVarError(member, extendC);
            }
        }
        return false;
    }
    if(memberEx != NULL){
        found = true;
        Type* t = member->GetType();
        Type* t1 = memberEx->GetType();
        if(t->GetTypeName() != t1->GetTypeName()){
            ReportError::OverrideMismatch(member);
            return false;
        }
        List<VarDecl*>* vars = member->GetFormals();
        List<VarDecl*>* varsEx = memberEx->GetFormals();
        if(vars->NumElements() != varsEx->NumElements()){
            ReportError::OverrideMismatch(member);
            return false;
        }

        for(int i = 0; i < vars->NumElements(); i++){
            if(vars->Nth(i)->GetType() != varsEx->Nth(i)->GetType()){
                ReportError::OverrideMismatch(member);
                found = false;
                return found;
            }
        }
        return found;
    }
    else{
        Decl* extendNext = extendC->GetExtendScope();
        if(extendNext != NULL){
            return CheckOverriding(i, extendNext, parentT);
        }
        else{
            return false;
        }
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

void InterfaceDecl::Check(){
    for(int i = 0; i < members->NumElements(); i++){
        members->Nth(i)->Check();
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
    formalsTable->SetFnDecl(this);
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
    cout << "endedbodyscope" << endl;
}

void FnDecl::Check(){
    Type* rt = returnType;
    const char* rtName = rt->GetTypeName();
    bool found = false;

    if(rtName != Type::intType->GetTypeName() &&
       rtName != Type::doubleType->GetTypeName() &&
       rtName != Type::boolType->GetTypeName() &&
       rtName != Type::stringType->GetTypeName() &&
       rtName != Type::voidType->GetTypeName()){
        SymbolTable* current = new SymbolTable();
        current = formalsTable->GetParentTable();
        Decl* d = NULL;

        while(current != NULL){
            Decl* d = current->CheckDecl(rtName);
            if(d != NULL){
                found = true;
                break;
            }
            current = current->GetParentTable();
        }
        if(!found){
            ReportError::IdentifierNotDeclared(new Identifier(*this->location, rtName), LookingForClass);
        }
    }

    if(body != NULL){
        Assert(body!=NULL);
        body->Check();
    }
}

