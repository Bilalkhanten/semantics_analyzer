/*
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <typeinfo>

/**
    Class Animal{}
    Class Dog implements Animal{}
    //CHECK IF RIGHT(COMPATEE) IS COMPATIBLE WITH LEFT
    //Use like this
    Animal a = (Dog)b;
    //We check to see if b is compatible with an assignment to the type of a.
    b.IsCompatible(a);
**/
bool Expr::IsCompatible(Expr* compatee){
    Type* t_left = this->GetType();
    Type* t_compatee = compatee->GetType();

    if(strcmp(t_left->GetTypeName(), t_compatee->GetTypeName()) == 0){
        return true;
    }
    else{
        cout << "uhlgiua.a" << endl;
        Decl* thisClass;
        Decl* otherClass;
        SymbolTable* current = new SymbolTable();
        SymbolTable* parentT = new SymbolTable();
        current = localScope;
        bool found = false;

        while(current != NULL && !found){
            //cout << t_compatee << endl;
            thisClass = current->CheckDecl(t_left->GetTypeName());
            if(thisClass != NULL){
                found = true;
            }
            parentT = current;
            current = current->GetParentTable();
        }
        cout << "uhlgiua.a" << endl;
        Decl* extends = thisClass->GetExtendScope();
        if(extends){
            if(extends->GetDeclName() == t_left->GetTypeName()){
                cout <<"found a good one" << endl << endl;
                return true;
            }
            else{
                found = false;
                List<Decl*>* implements = thisClass->GetImplementScope();
                if(implements != NULL){
                    for(int i = 0; i < implements->NumElements(); i++){
                        const char* temp = implements->Nth(i)->GetDeclName();
                        cout << " " << implements->Nth(i)->GetDeclName() << endl;
                        if(strcmp(temp, t_compatee->GetTypeName()) == 0){
                            cout <<"found a good one2" << endl << endl;
                            found = true;
                        }
                    }
                }
                current = localScope;
                cout << "uhlgiua.a" << endl;
                while(!found && (extends || (implements->NumElements() > 0))){
                    if(extends){
                        if(strcmp(extends->GetDeclName(), t_compatee->GetTypeName()) == 0){
                            cout <<"found a good one1" << endl << endl;
                            found = true;
                            return true;
                        }
                    }

                    for(int i = 0; i < implements->NumElements(); i++){
                        const char* temp = implements->Nth(i)->GetDeclName();
                        cout << " " << implements->Nth(i)->GetDeclName() << endl;
                        if(strcmp(temp, t_compatee->GetTypeName()) == 0){
                            cout <<"found a good one2" << endl << endl;
                            found = true;
                            return true;
                        }
                    }

                    if(extends){
                        cout << "uhlgiua.a" << endl;
                        implements = extends->GetImplementScope();
                        if(implements == NULL){
                            implements = new List<Decl*>();
                        }
                        extends = extends->GetExtendScope();
                        cout << "uhlgiua.a12415235" << endl;
                    }
                    else{
                        break;
                    }
                }
                cout << "uhlgiua.a" << endl;
                if(!found){
                    cout << "uhlgiua.aqwrgwegw22r23" << endl;
                    ReportError::NotCompatible(thisClass, t_compatee);
                    return false;
                }
                cout <<"found a good one3" << endl << endl;
                return true;
            }
        }

        found = false;
        List<Decl*>* implements = thisClass->GetImplementScope();
        cout << "uhlgiua.a" << endl;cout << "uhlgiua.a" << endl;
        if(implements != NULL){
            for(int i = 0; i < implements->NumElements(); i++){
                const char* temp = implements->Nth(i)->GetDeclName();
                if(strcmp(temp, t_compatee->GetTypeName()) == 0){
                    found = true;
                }
            }
            if(!found){
                cout << "uhlgiua.a" << endl;cout << "uhlgiua.a" << endl;
                ReportError::NotCompatible(thisClass, t_compatee);
                return false;
            }
            return true;
        }
        return false;
    }
}

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

    if(strcmp(t_left->GetTypeName(), t_right->GetTypeName()) == 0){
    		cout << "Here1" << endl; cout << "here1" << t_left->GetTypeName() << endl;
        return t_left;
    }
    else{
        //Error
        cout << "Here" << endl; cout << "here" << endl;
        return NULL;
    }
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

void PostfixExpr::Check(){
    Type* t = left->GetType();
    Assert(t != NULL);
    if(t->GetTypeName() != Type::intType->GetTypeName()){
        ReportError::IncompatibleOperand(op, t);
    }
}

void PostfixExpr::PrintChildren(int indentLevel) {
    left->Print(indentLevel+1);
    op->Print(indentLevel+1);
}

void ArithmeticExpr::Check() {

    if (left != NULL)
        left->Check();

    right->Check();
    cout << "herher "
;    Type *t_Left;

    if (left != NULL)
        t_Left = left->GetType();

    Type *t_Right = right->GetType();

    if (left != NULL) {
        if ((t_Right->GetTypeName() != Type::intType->GetTypeName() || t_Left->GetTypeName() != Type::intType->GetTypeName())) {
            if (t_Left->GetTypeName() != Type::doubleType->GetTypeName() || t_Right->GetTypeName() != Type::doubleType->GetTypeName())
                ReportError::IncompatibleOperands(op, t_Left, t_Right);
        }
        else{
            return;
        }
    }

    else {
        if (t_Right->GetTypeName() != Type::intType->GetTypeName() && t_Right->GetTypeName() != Type::doubleType->GetTypeName())
            ReportError::IncompatibleOperand(op, t_Right);
        else
            return;
    }
}

Type* ArithmeticExpr::GetType(){
    Type* t_left;
    Type* t_right;

    if(left != NULL){
        t_left = left->GetType();
        t_right = right->GetType();
        if(t_left == NULL || t_right == NULL){
            return NULL;
        }

        if ((t_right->GetTypeName() != Type::intType->GetTypeName() || t_left->GetTypeName() != Type::intType->GetTypeName())) {
            if (t_left->GetTypeName() != Type::doubleType->GetTypeName() || t_right->GetTypeName() != Type::doubleType->GetTypeName())
                ReportError::IncompatibleOperands(op, t_left, t_right);
            return right->GetType();
        }
        else{
            return right->GetType();
        }
        return right->GetType();
    }
    else{
        return right->GetType();
    }
}

void RelationalExpr::Check() {

    if (left != NULL)
        left->Check();

    right->Check();

    Type *t_Left;

    if (left != NULL)
        t_Left = left->GetType();

    Type *t_Right = right->GetType();

    if (left != NULL) {

        if (((t_Right->GetTypeName() != Type::intType->GetTypeName()) || (t_Left->GetTypeName() != Type::intType->GetTypeName()))){
            if (t_Left->GetTypeName() != Type::doubleType->GetTypeName() || t_Right->GetTypeName() != Type::doubleType->GetTypeName()){
                ReportError::IncompatibleOperands(op, t_Left, t_Right);
            }
            return;
        }
        else {
            return;
        }
    }

    else {
        if (t_Right->GetTypeName() != Type::intType->GetTypeName() && t_Right->GetTypeName() != Type::doubleType->GetTypeName()) {
            ReportError::IncompatibleOperand(op, t_Right);
        }
        else
            return;
    }
}

Type* RelationalExpr::GetType() {
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
        return Type::errorType;
    }
}

void LogicalExpr::Check() {
    if (left != NULL)
        left->Check();

    right->Check();

    Type *t_Left;
    if (left != NULL)
        t_Left = left->GetType();

    Type *t_Right = right->GetType();

    if (left != NULL) {
        cout << t_Right->GetTypeName() << "  " << t_Left->GetTypeName() << endl;
         if (t_Right->GetTypeName() != Type::boolType->GetTypeName() || t_Left->GetTypeName() != Type::boolType->GetTypeName()){
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
            return;
         }
        else{
            cout << "here correct";
            return;
        }
    }

    else {
        if (t_Right->GetTypeName() != Type::boolType->GetTypeName()){
            ReportError::IncompatibleOperand(op, t_Right);
            return;
        }
        else{
            cout << "lshgslhkgdlk" << endl;
            return;
        }
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
        cout << "otheth;alalt" << endl;
        return t_left;
    }
    else{
        //Error
        return t_left;
    }
}

void EqualityExpr::Check() {
    left->Check();
    right->Check();
    Type *t_Left = left->GetType();
    Type *t_Right = right->GetType();

    if (strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) != 0) {
        ReportError::IncompatibleOperands(op, t_Left, t_Right);
        return;
    }
}

Type* EqualityExpr::GetType() {
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();
    if(strcmp(t_left->GetTypeName(), t_right->GetTypeName()) == 0){
        return Type::boolType;
    }
    else{
        //Error
        return Type::errorType;
    }
}

void AssignExpr::Check(){
    left->Check();
    right->Check();

    Assert(left != NULL);

    Type* t_Left = left->GetType();
    Type* t_Right = right->GetType();
    cout << t_Left->GetTypeName() << " " << t_Right->GetTypeName() << endl;
    if (t_Right->GetTypeName() == Type::nullType->GetTypeName())
    {
        NamedType* nt_Left = dynamic_cast<NamedType *>(t_Left);
        if (nt_Left == NULL && t_Left != Type::errorType)
        {
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
        }
        return;
    }

    if(right->GetType()->isNamedType()){
        if(left->GetType()->isNamedType()){
            if (!right->IsCompatible(left)) {
                cout << "erjkhlkGU";
                ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
                return;
            }
            else{
                return;
            }
        }
    }

    if(t_Left->isArray()){
            if(right->isNewArray()){
                cout << "true new arrya";
            }
        if(t_Right->isArray() || right->isNewArray()){
            cout << "true new arrya";
            if((t_Left->GetNumberOfDims() != t_Right->GetNumberOfDims()) && !left->isArrayAccess()){
                    cout << "akjfhau ;foIH PIH Q0" << endl;
                    cout << "not the same number of dims" << endl;
                    ReportError::IncompatibleOperands(op, t_Left, t_Right);
                    return;
            }
            if (strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) != 0) {
                cout << "aUGFLIUqglougqg" << endl;
                ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
                return;
            }
            else if (!left->isArrayAccess()){
                if(t_Left->GetNumberOfDims() != t_Right->GetNumberOfDims()){
                    cout << "akjfhau ;foIH PIH Q0" << endl;
                    cout << "not the same number of dims";
                    ReportError::IncompatibleOperands(op, t_Left, t_Right);
                }
                cout << "kjleglfkjgwe;a" << endl;
                if(right->isNewArray()){
                        cout << "kjleglfkjgwe;a" << endl;
                    if(t_Left->GetNumberOfDims() == 1){
                        cout << "correct" << endl;
                    }
                    else{
                        cout << "incorrect " << endl;
                    }
                }
                return;
            }
        }
        if(strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) == 0 && left->isArrayAccess()){
            cout << left->GetNumOfAccess() << " " << right->GetNumOfAccess() <<  endl;
            if((t_Left->GetNumberOfDims() - left->GetNumOfAccess()) == t_Right->GetNumberOfDims()){
                cout << "Array access is good." << endl;
                return;
            }
            else{
                ReportError::IncompatibleOperands(op, t_Left, t_Right);
                return;
            }
        }
        cout << "hgAILU Gqu;fI;ieng/;eawg" << endl;
        //cout << "aUGFLIUqglougqg" << endl;
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
        return;
    }
    else if(t_Right->isArray()){
        if(right->isArrayAccess()){
            if(strcmp(t_Right->GetTypeName(), t_Left->GetTypeName()) == 0){
                return;
            }
        }
        else if(strcmp(t_Right->GetTypeName(), t_Left->GetTypeName()) == 0){
            cout << "here" << endl;
            return;
        }
        //cout << "aUGFLIUqglougqg" << endl;
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
        return;
    }

    if (strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) != 0) {
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
        return;
    }
}

Type* AssignExpr::GetType() {
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();
    cout <<  t_left->GetTypeName() <<" " << t_right->GetTypeName() << endl;
    if(strcmp(t_left->GetTypeName(), t_right->GetTypeName()) == 0){
        return t_left;
    }
    else{
        //Error
        cout << "here";
        return Type::errorType;
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
    Expr* e = base;
    numberOfAccess = 0;
    while(e != NULL){
        numberOfAccess++;
        e = e->GetBase();
    }

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
    cout << "leglugeUH;weog" << endl;
    return Type::errorType;
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

void ArrayAccess::Check() {
    base->Check();
    subscript->Check();

    if (subscript->GetType()->GetTypeName() != Type::intType->GetTypeName())
    {
        ReportError::SubscriptNotInteger(subscript);
    }

    if (typeid(*base->GetType()) != typeid(ArrayType)) {
        ReportError::BracketsOnNonArray(base);
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

void NewExpr::Check() {
    if (cType) {
        const char *name = this->cType->GetTypeName();
        if (name)
        {
            bool found = false;
            Decl *decl = localScope->CheckDecl(name);
            SymbolTable* current = new SymbolTable();
            current = localScope;

            while(current != NULL && !found){
                decl = current->CheckDecl(name);
                if(decl != NULL){
                    found = true;
                }
                current = current->GetParentTable();
            }
            if(!found){
                ReportError::IdentifierNotDeclared(new Identifier(*this->cType->GetLocation(), name), LookingForClass);
            }
        }
    }
}

Type* NewExpr::GetType(){
    return cType;
}

void NewExpr::PrintChildren(int indentLevel) {
    cType->Print(indentLevel+1);
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this);
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::Check() {
    size->Check();

    if (size->GetType()->GetTypeName() != Type::intType->GetTypeName())
        ReportError::NewArraySizeNotInteger(size);
    if (strcmp(elemType->GetTypeName(), Type::voidType->GetTypeName())){
        ReportError::NewArrayVoidType(elemType);
    }
}

void NewArrayExpr::PrintChildren(int indentLevel) {
    size->Print(indentLevel+1);
    elemType->Print(indentLevel+1);
}

Type* ReadIntegerExpr::GetType(){
    return Type::intType;
}

Type* ReadLineExpr::GetType(){
    return Type::stringType;
}

