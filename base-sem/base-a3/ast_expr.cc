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

Type* CompoundExpr::GetType(){
		cout << "Here1" << endl; cout << "here1" << endl;
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();

    if(t_left->IsEquivalentTo(t_right)){
    		cout << "Here1" << endl; cout << "here1" << t_left->GetTypeName() << endl;
        return t_left;
    }
    else{
        //Error
        cout << "Here" << endl; cout << "here" << endl;
        return NULL; //I can't see scrolling // Ok, jw  // Can you try this and see if you get any output?kk
    } // seeing same errors// thats what if figured look below // Maybe it's something to do with method inheritance and did you get any output? // Try this and see if there's any output
}			// add some cout's in Expr::BUildScope and Stmt::BuildScope() in stmt.cc in think.

void CompoundExpr::PrintChildren(int indentLevel) {
   if (left) left->Print(indentLevel+1);
   op->Print(indentLevel+1);
   right->Print(indentLevel+1);
}

void CompoundExpr::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope = s;
    Assert(s != NULL);
    right->BuildScope(s);
    if(left != NULL){
        left->BuildScope(s);
    }
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

void ArithmeticExpr::Check() {

    if (left != NULL)
        left->Check();
    right->Check();

    Type* t_Left = NULL;

    if (left != NULL)
        t_Left = left->GetType();

    Type* t_Right = right->GetType();


    if (t_Left == NULL && left != NULL) {

        SymbolTable* curr = new SymbolTable;
        curr = localScope;

        Type* n = NULL;
        if (left->GetID() != NULL) {
            while(curr != NULL){
                Decl* d = curr->CheckDecl(left->GetID()->GetName());
                if(d != NULL){
                     n = d->GetType();
                }
                curr = curr->GetParentTable();
            }
        }// so change the else stmt?kk yup
        //If left-GetID() == NULL then it means that it may be an expr without an ID
        //So it could actually be of type int or double etc.
        else {
            //what would be written here? You want to get the Type here right? Right
            Type* t = left->GetType();
        } //what do we do with it now//Not sure if this is how let me think for a sec Take your time!
        // I just ran the code as it is now, still same stuff//Do you know which expr's return null?//Now that i think about it something isn't returning properly, it should never be null
        // I think that any expr that deals with classes has to deal with nullType //line ~100 // Can you see the scrolling or is that local?
    }
    else {
        VarDecl* var = dynamic_cast<VarDecl *>(localScope->CheckDecl(left->GetID()->GetName()));
        t_Left = var->GetType();
    }

    if (t_Right == NULL && right != NULL) {

       SymbolTable* curr = new SymbolTable;
        curr = localScope;

        Type* n = NULL;
        if (right->GetID() != NULL) {
            while(curr != NULL){
                Decl* d = curr->CheckDecl(right->GetID()->GetName());
                if(d != NULL){
                     n = d->GetType();
                }
                curr = curr->GetParentTable();
            }
        }
        else {
            ReportError::IdentifierNotDeclared(right->GetID(), LookingForVariable);
        }
    }
    else {
        VarDecl* var = dynamic_cast<VarDecl *>(localScope->CheckDecl(right->GetID()->GetName()));
        t_Left = var->GetType();
    }

    if (left == NULL) {
        if (t_Right != Type::doubleType || t_Right != Type::intType)
        {
            ReportError::IncompatibleOperand(op, t_Right);
        }
    return;
    }

    if (t_Left->IsEquivalentTo(t_Right)) {

        if (t_Left == Type::errorType || t_Right == Type::errorType)
            ;
        else if (t_Left == Type::intType || t_Left == Type::doubleType)
            ;
        else {

            ReportError::IncompatibleOperands(op, t_Left, t_Right);
        }
    }
    else {
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
    }
}


void RelationalExpr::Check() {

    left->Check();
    right->Check();

    Type* t_Left = left->GetType();
    Type* t_Right = right->GetType();

    Identifier* left_Id;
    Decl* left_Decl;

    if (t_Left == NULL && left != NULL) {

        left_Id = left->GetID();

        Assert(left_Id != NULL);

        left_Decl = localScope->CheckDecl(left_Id->GetName());

        if (left_Decl == NULL) {
            ReportError::IdentifierNotDeclared(left_Id, LookingForVariable);
        }
    }
    else {
        VarDecl* var = dynamic_cast<VarDecl *>(left_Decl);
        t_Left = var->GetType();
    }

    if (t_Left->IsEquivalentTo(t_Right)) {

        if (t_Left == Type::nullType || t_Right == Type::nullType)
            ;
        else if (t_Left == Type::intType || t_Left == Type::doubleType)
            ;
        else {
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
        }
    }
    else {
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
    }
}

Type* RelationalExpr::GetType() {
    cout << "here" <<  endl;
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();

    if(t_left->IsEquivalentTo(t_right)){
        return t_left;
    }
    else{
        //Error
        return NULL;
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

Type* LogicalExpr::GetType() {
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();
    Assert(t_left != NULL && t_right != NULL);
    if(t_left->GetTypeName() == t_right->GetTypeName()){
        return t_left;
    }
    else{
        //Error
        return NULL;
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
        return;
    }

    if (t_Left == NULL) {

        Identifier *left_Id = left->GetID();

        Decl *d_Left = localScope->CheckDecl(left_Id->GetName());

        if (d_Left == NULL) {
            ReportError::IdentifierNotDeclared(left_Id, LookingForVariable);
        }
        else {
            VarDecl *var = dynamic_cast<VarDecl *>(d_Left);
            t_Left = var->GetType();
        }
    }

    if (t_Left == Type::voidType || t_Right == Type::voidType) {
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
    }
    else if (t_Left->IsEquivalentTo(t_Right))
        ;
    else {

        NamedType* nt_Left = dynamic_cast<NamedType *>(left->GetType());
        NamedType* nt_Right = dynamic_cast<NamedType *>(right->GetID());

        ClassDecl* left_Decl = dynamic_cast<ClassDecl*>(localScope->CheckDecl(nt_Left));
        ClassDecl* right_Decl = dynamic_cast<ClassDecl*>(localScope->CheckDecl(nt_Right));

        NamedType* n = dynamic_cast<NamedType *>(left_Decl->GetExtendScope()->GetType());
        Decl* d = left_Decl->GetExtendScope();

        for (int i = 0; n != NULL; i++) {

            if (n->IsEquivalentTo(nt_Right)) {
                return;
            }
            else {
                ReportError::IncompatibleOperands(op, t_Left, t_Right);
                return;
            }

            n = dynamic_cast<NamedType *>(d->GetType());
            d = d->GetExtendScope();
        }
    }
}

Type* EqualityExpr::GetType() {
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();

    if(t_left->GetTypeName() == t_right->GetTypeName()){
        return Type::boolType;
    }
    else{
        //Error
        return NULL;
    }
}

void AssignExpr::Check(){
    /**
    left->Check();
    right->Check();**/
}

Type* AssignExpr::GetType() {
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();

    if(t_left->GetTypeName() == t_right->GetTypeName()){
        return t_left;
    }
    else{
        //Error
        return NULL;
    }
}

void AssignExpr::BuildScope(SymbolTable* s){
    left->BuildScope(s);
    right->BuildScope(s);
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this);
    (subscript=s)->SetParent(this);
}

Type* ArrayAccess::GetType(){
    return base->GetType();
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

Type* FieldAccess::GetType(){
    SymbolTable* current = new SymbolTable();
    current = localScope;
    while(current != NULL){
        Decl* d = current->CheckDecl(field->GetName());
        if(d != NULL){
            return d->GetType();
        }
        current = current->GetParentTable();
    }
    //Error: Did not find the declaration.
    return NULL;
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

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

Type* Call::GetType(){

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


