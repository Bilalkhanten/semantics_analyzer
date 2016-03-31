/*
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"


IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

Type* IntConstant::GetType() {
    return Type::intType;
}

void IntConstant::PrintChildren(int indentLevel) {
    printf("%d", value);
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

Type* DoubleConstant::GetType() {
    return Type::doubleType;
}

void DoubleConstant::PrintChildren(int indentLevel) {
    printf("%g", value);
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

Type* BoolConstant::GetType() {
    return Type::boolType;
}

void BoolConstant::PrintChildren(int indentLevel) {
    printf("%s", value ? "true" : "false");
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Type* StringConstant::GetType() {
    return Type::stringType;
}

void StringConstant::PrintChildren(int indentLevel) {
    printf("%s",value);
}

Type* NullConstant::GetType() {
    return Type::nullType;
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) {
    printf("%s",tokenString);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r)
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this);
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r)
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL;
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
   if (left) left->Print(indentLevel+1);
   op->Print(indentLevel+1);
   right->Print(indentLevel+1);
}

void CompoundExpr::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope = s;
    Assert(s != NULL);
    right->SetScope(s);
}

PostfixExpr::PostfixExpr(Expr *l,Operator *o)
    : Expr(Join(l->GetLocation(),o->GetLocation())) {
    Assert(o != NULL && l != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this);
}

void PostfixExpr::PrintChildren(int indentLevel) {
    left->Print(indentLevel+1);
    op->Print(indentLevel+1);
}

Type* ArithmeticExpr::GetType() {
    Type* t_right = right->GetType();
    Type* t_left;
    if(left != NULL){
        t_left = left->GetType();
    }

    if(t_right->IsEquivalentTo(t_left)){
        //Correct
        return t_right;
    }
    else{
        //Error
        return NULL;
    }
}

void ArithmeticExpr::Check() {

    if (left != NULL)
        left->Check();
    right->Check();

    Type* t_Left = NULL;

    if (left != NULL)
        t_Left = left->GetType();

    Type* t_Right = right->GetType();

    Identifier* left_Id = NULL;
    Decl* left_Decl = NULL;

    if (t_Left == NULL && left != NULL) {

        left_Id = left->GetID();

        left_Decl = localScope->CheckDecl(left_Id->GetName());

        if (left_Decl == NULL) {
            retType = Type::errorType;
            ReportError::IdentifierNotDeclared(left_Id, LookingForVariable);
        }
    }
    else {
        VarDecl* var = dynamic_cast<VarDecl *>(left_Decl);
        t_Left = var->GetType();
    }

    Identifier* right_Id = NULL;
    Decl* right_Decl = NULL;

    if (t_Right == NULL && right != NULL) {

        right_Id = right->GetID();

        right_Decl = localScope->CheckDecl(right_Id->GetName());

        if (left_Decl == NULL) {
            retType = Type::errorType;
            ReportError::IdentifierNotDeclared(right_Id, LookingForVariable);
        }
    }
    else {
        VarDecl* var = dynamic_cast<VarDecl *>(right_Decl);
        t_Left = var->GetType();
    }

    if (left == NULL) {
        if (t_Right == Type::doubleType || t_Right == Type::intType)
        {
            retType = t_Right;
        }
        else
        {
            ReportError::IncompatibleOperand(op, t_Right);
            retType = Type::errorType;
        }
        return;
    }

    if (t_Left->IsEquivalentTo(t_Right)) {

        if (t_Left == Type::errorType || t_Right == Type::errorType)
            retType = Type::errorType;
        else if (t_Left == Type::intType || t_Left == Type::doubleType)
            retType = t_Left;
        else {
            retType = Type::errorType;
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
        }
    }
    else {
        retType = Type::errorType;
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
    }
}

void RelationalExpr::Check() {

    left->Check();
    right->Check();

    Type* t_Left = left->GetType();
    Type* t_Right = right->GetType();

    Identifier* left_Id = NULL;
    Decl* left_Decl = NULL;

    if (t_Left == NULL && left != NULL) {

        left_Id = left->GetID();

        left_Decl = localScope->CheckDecl(left_Id->GetName());

        if (left_Decl == NULL) {
            retType = Type::errorType;
            ReportError::IdentifierNotDeclared(left_Id, LookingForVariable);
        }
    }
    else {
        VarDecl* var = dynamic_cast<VarDecl *>(left_Decl);
        t_Left = var->GetType();
    }

    if (t_Left->IsEquivalentTo(t_Right)) {

        if (t_Left == Type::nullType || t_Right == Type::nullType)
            retType = Type::errorType;
        else if (t_Left == Type::intType || t_Left == Type::doubleType)
            retType = Type::boolType;
        else {
            retType = Type::errorType;
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
        }
    }
    else {
        retType = Type::errorType;
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
    }
}

void AssignExpr::Check(){
    left->Check();
    right->Check();
}

void AssignExpr::BuildScope(SymbolTable* s){
    left->BuildScope(s);
    right->BuildScope(s);


}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this);
    (subscript=s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
    base->Print(indentLevel+1);
    subscript->Print(indentLevel+1, "(subscript) ");
  }

FieldAccess::FieldAccess(Expr *b, Identifier *f)
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
}


void FieldAccess::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
  }

void FieldAccess::Check(){
    Assert(localScope != NULL);

    Decl* n = localScope->CheckDecl(field->GetName());
    SymbolTable* current = new SymbolTable();
    current = localScope;
    bool found = false;

    if(base){
        //Get top level class declarations
        SymbolTable* parentT = new SymbolTable();
        SymbolTable* classT = new SymbolTable();

        if(current->GetParentTable() == NULL){
            //this. was used outside a class declaration.
            This* t = new This(*location);
            ReportError::ThisOutsideClassScope(t);
            return;
        }

        while(current->GetParentTable() != NULL && !found){
            if(current->GetClassDecl() != NULL){
                classT = current;
                found = true;
                break;
            }
            current = current->GetParentTable();
            parentT = current;
        }
        if(!found){
            cout << "Error: Not within class scope.";
        }
        found = false;

        if(current->GetClassDecl() == NULL){
            This* t = new This(*location);
            ReportError::ThisOutsideClassScope(t);
            return;
        }

        Decl* n = classT->CheckDecl(field->GetName());
        ClassDecl* c = classT->GetClassDecl();

        if(n == NULL){
            Decl* extends = c->GetExtendScope();
            Decl* temp = extends->GetScope()->CheckDecl(field->GetName());

            if(temp != NULL){
                return;
            }

            List<Decl*>* implements = c->GetImplementScope();
            for (int i = 0; i < implements->NumElements(); i++){
                Decl* implement = implements->Nth(i);
                temp = implement->GetScope()->CheckDecl(field->GetName());
                if(temp != NULL){
                    return;
                }
            }

            ReportError::IdentifierNotDeclared(field, LookingForVariable);
        }

        return;
    }

    while(current != NULL && !found){
        n = current->CheckDecl(field->GetName());
        if(n != NULL){
            found = true;
            break;
        }
        current = current->GetParentTable();
    }

    if(!found){
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
        return;
    }
}

void LogicalExpr::Check() {
    Type *t = Type::boolType;

    if (left != NULL)
        left->Check();

    right->Check();

    Type *t_Left;
    if (left != NULL)
        t_Left = left->GetType();

    Type *t_Right = right->GetType();

    if (left != NULL) {
        if (t_Right->IsEquivalentTo(t) && t_Left->IsEquivalentTo(t))
            return;
        else
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
    }

    else {
        if (t_Right->IsEquivalentTo(t))
            return;
        else
            ReportError::IncompatibleOperand(op, t_Right);
    }
}

void EqualityExpr::Check() {
    left->Check();
    right->Check();

    Type *t_Left = left->GetType();
    Type *t_Right = right->GetType();

    if (t_Right == Type::nullType && t_Left != Type::nullType) {

        NamedType* t_Left_Named = dynamic_cast<NamedType *>(t_Left);
        if (t_Left_Named == NULL)
            ReportError::IncompatibleOperands(op, t_Left, t_Right);

        retType = Type::boolType;
        return;
    }

    if (t_Left == NULL) {

        Identifier *left_Id = left->GetID();

        Decl *d_Left = localScope->CheckDecl(left_Id->GetName());

        if (d_Left == NULL) {
            retType = Type::errorType;
            ReportError::IdentifierNotDeclared(left_Id, LookingForVariable);
        }
        else {
            VarDecl *var = dynamic_cast<VarDecl *>(d_Left);
            t_Left = var->GetType();
        }
    }

    if (t_Left == Type::voidType || t_Right == Type::voidType) {
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
        retType = Type::errorType;
    }
    else if (t_Left->IsEquivalentTo(t_Right))
        retType = Type::boolType;
    else {

        NamedType* nt_Left = dynamic_cast<NamedType *>(left->GetType());
        NamedType* nt_Right = dynamic_cast<NamedType *>(right->GetID());

        ClassDecl* left_Decl = dynamic_cast<ClassDecl*>(localScope->CheckDecl(nt_Left));
        ClassDecl* right_Decl = dynamic_cast<ClassDecl*>(localScope->CheckDecl(nt_Right));

        NamedType* n = dynamic_cast<NamedType *>(left_Decl->GetExtendScope()->GetType());
        Decl* d = left_Decl->GetExtendScope();

        for (int i = 0; n != NULL; i++) {

            if (n->IsEquivalentTo(nt_Right)) {
                retType = Type::boolType;
                return;
            }
            else {
                ReportError::IncompatibleOperands(op, t_Left, t_Right);
                retType = Type::errorType;
                return;
            }

            n = dynamic_cast<NamedType *>(d->GetType());
            d = d->GetExtendScope();
        }
    }
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

 void Call::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
    actuals->PrintAll(indentLevel+1, "(actuals) ");
  }


NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) {
    cType->Print(indentLevel+1);
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this);
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) {
    size->Print(indentLevel+1);
    elemType->Print(indentLevel+1);
}


