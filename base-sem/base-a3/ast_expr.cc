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
bool Expr::IsCompatible(Expr* compatee, SymbolTable* localScope){
    return GetType()->IsCompatible(compatee->GetType(), this->localScope);
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
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();

    if(strcmp(t_left->GetTypeName(), t_right->GetTypeName()) == 0){
        return t_left;
    }
    else{
        //Error
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
         if (t_Right->GetTypeName() != Type::boolType->GetTypeName() || t_Left->GetTypeName() != Type::boolType->GetTypeName()){
            ReportError::IncompatibleOperands(op, t_Left, t_Right);
            return;
         }
        else{
            return;
        }
    }

    else {
        if (t_Right->GetTypeName() != Type::boolType->GetTypeName()){
            ReportError::IncompatibleOperand(op, t_Right);
            return;
        }
        else{
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
    if(t_Left->isArray() && right->isNewArray()){
        if(strcmp(t_Left->GetTypeName(), right->GetType()->GetTypeName()) != 0){
            ReportError::IncompatibleOperands(op, t_Left, right->GetType());
            return;
        }
        if(t_Left->GetNumberOfDims() == 1){
            return;
        }
        else if((t_Left->GetNumberOfDims() - left->GetNumOfAccess()) == 1){
            return;
        }

    }
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
            if (!right->IsCompatible(left, localScope)) {
                ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
                return;
            }
            else{
                return;
            }
        }
    }

    if(t_Left->isArray()){
        if(t_Right->isArray()){
            if((t_Left->GetNumberOfDims() != t_Right->GetNumberOfDims()) && !left->isArrayAccess()){
                    ReportError::IncompatibleOperands(op, t_Left, t_Right);
                    return;
            }
            if (strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) != 0) {
                ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
                return;
            }
            else if (!left->isArrayAccess()){
                if(t_Left->GetNumberOfDims() != t_Right->GetNumberOfDims()){
                    ReportError::IncompatibleOperands(op, t_Left, t_Right);
                }
                return;
            }
        }
        if(strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) == 0 && left->isArrayAccess()){
            if((t_Left->GetNumberOfDims() - left->GetNumOfAccess()) == (t_Right->GetNumberOfDims()-right->GetNumOfAccess())){
                return;
            }
            else {
                ReportError::IncompatibleOperands(op, t_Left, t_Right);
                return;
            }
        }
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
            return;
        }
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
        return;
    }

    if (strcmp(t_Left->GetTypeName(), t_Right->GetTypeName()) != 0) {
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
        return;
    }
}

Type* AssignExpr::GetType() {
    Assert(left != NULL && right != NULL);
    cout << "here easg" << endl;
    if(left == NULL){
        return right->GetType();
    }
    Type* t_left = left->GetType();
    Type* t_right = right->GetType();
    Assert(t_left != NULL && t_right != NULL);
    if(strcmp(t_left->GetTypeName(), t_right->GetTypeName()) == 0){
        cout << "here easg" << endl;
        return t_left;
    }
    else{
        //Error
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
    SymbolTable* parentT = new SymbolTable();
    current = localScope;

    while(current != NULL){
        Decl* d = current->CheckDecl(field->GetName());
        if(d != NULL){
            return d->GetType();
        }
        parentT = current;
        current = current->GetParentTable();
    }

    if(base){
        Type* classType = base->GetType();
        current = localScope;

        Decl* classD = parentT->CheckDecl(classType->GetTypeName());
        if(classD != NULL){
            bool found = false;
            Decl* decl = classD->GetScope()->CheckDecl(field->GetName());
            if(decl != NULL){
                return decl->GetType();
            }

            Decl* ext = classD->GetExtendScope();
            Decl* ex;

            while(ext != NULL && !found){
                ex = ext->GetScope()->CheckDecl(field->GetName());
                if(ex != NULL){
                    return ex->GetType();
                    found = true;
                }
                ext = ext->GetExtendScope();
            }
            if(!found){
                ReportError::IdentifierNotDeclared(field, LookingForVariable);
                return Type::errorType;
            }
            return ex->GetType();
        }
    }
    //Error: Did not find the declaration.
    return Type::errorType;
}

void FieldAccess::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
  }

/**
* Make changes for variables in extended class.
**/
void FieldAccess::Check(){
    Assert(localScope != NULL);

    Decl* n = localScope->CheckDecl(field->GetName());
    SymbolTable* current = new SymbolTable();
    current = localScope;
    bool found = false;

    if(base){
        if(!base->isThis()){
            Type* classType = base->GetType();
            SymbolTable* classT = new SymbolTable();
            classT = current;
            while(current->GetParentTable() != NULL){

                classT = current;
                current = current->GetParentTable();
            }
            Decl* cDecl = classT->GetClassDecl();
            Assert(cDecl != NULL);
            if(strcmp(classType->GetTypeName(), cDecl->GetDeclName()) != 0){
                Decl* d = cDecl->GetScope()->CheckDecl(field->GetName());

                if(d != NULL){
                    return;
                }
                else{
                    Decl* ext = cDecl->GetExtendScope();
                    //cout << "lkgliugIUNULL" << endl;
                    if(ext == NULL){
                        //cout << "lkgliugIUNULL" << endl;
                        ReportError::IdentifierNotDeclared(field, LookingForVariable);
                        return;
                    }
                    else{
                        bool found  =  false;

                        while(ext != NULL && !found){
                            Decl* ex = ext->GetScope()->CheckDecl(field->GetName());
                            if(ex != NULL){
                                found = true;
                            }
                            ext = ext->GetExtendScope();
                        }
                        if(!found){
                             ReportError::IdentifierNotDeclared(field, LookingForVariable);
                            return;
                        }
                        return;
                    }
                }
            }//end if
            else{
                return;
            }
        }
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

            found = true;
            while(extends != NULL && !found){
                Decl* temp = extends->GetScope()->CheckDecl(field->GetName());
                if(temp != NULL){
                    found = true;
                    return;
                }
                extends = extends->GetExtendScope();
            }

            ReportError::FieldNotFoundInBase(field, Type::errorType);
            return;
        }
        else{
            return;
        }

        Type* t = base->GetType();
        Assert(t != NULL);
        if(base->isThis()){
        }
        else{
            ReportError::FieldNotFoundInBase(field, Type::errorType);
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

void Call::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope = s;
    if (base != NULL) base->BuildScope(localScope);
    for(int i = 0; i < actuals->NumElements(); i++){
        actuals->Nth(i)->BuildScope(localScope);
    }
}

void Call::Check() {
    for (int i = 0; i < actuals->NumElements(); i++){
        actuals->Nth(i)->Check();
    }
    Decl* decl = NULL;
    if (base) {
        SymbolTable* current = new SymbolTable();
        Type* classType = base->GetType();
        current = localScope;
        bool found = false;
        cout << "kuaegliugweluogt; w/" << endl;
        if(classType->isArray()){
            const char* libraryFunc = "length";

            if(strcmp(field->GetName(), libraryFunc) != 0){
                ReportError::ArrFuncMismatch(this, field->GetName());
            }

            if(actuals->NumElements() != 0){
                ReportError::NumArgsMismatch(field, 0, actuals->NumElements());
            }
            returnType = classType;
            return;
        }
        else if(!(classType->isNamedType())){
            ReportError::NonNamedTypeFunc(this, base->GetType());
            return;
        }
        else{
            cout << "kkhgjhgjeer" << endl;
            cout << "kuaegliugweluogt; w/" << endl;
            Decl* d;
            found = false;
            SymbolTable* classT;
            SymbolTable* extended;

            while(current->GetParentTable() != NULL){
                if(current->GetClassDecl() != NULL){
                    classT = current;
                }
                current = current->GetParentTable();
            }
            cout << "kuaegliugweluogt; w/" << endl;
            if(classT != NULL && base->isThis()){
                d = classT->CheckDecl(classType->GetTypeName());
                if(d == NULL){
                    ReportError::FieldNotFoundInBase(new Identifier(*this->location, classType->GetTypeName()), classType);
                    return;
                }
                returnType = d->GetType();
                return;
            }
            cout << "kuaegliugweluogt; w/" << endl;
            SymbolTable* parentT = new SymbolTable();
            while(current != NULL){
                parentT = current;
                current = current->GetParentTable();
            }
            current = localScope;
            found = false;
            while(current != NULL && !found){
                d = current->CheckDecl(classType->GetTypeName());
                if(d != NULL){
                    found = true;
                }
                current = current->GetParentTable();
            }
            if(!found){
                ReportError::IdentifierNotDeclared(new Identifier(*this->location, classType->GetTypeName()), LookingForClass);
                return;
            }
            cout << "kuaegliugweluogt; w/" << endl;
            //cout << parentT->GetName() << " 2308718 " <<endl;
            Decl* func = parentT->CheckDecl(classType->GetTypeName());
            if(func != NULL){
                found = false;
                Decl* ext = func->GetExtendScope();
                cout << "kuaegliugweluogt; w/" << endl;
                if(ext == NULL){
                     cout << "kuaegliugweluogt; w/" <<endl;
                     Iterator<Decl*> it = func->GetScope()->getHashTablePointer()->GetIterator();
                     Decl* d = it.GetNextValue();
                     cout << d->GetDeclName() <<endl;

                     while(d != NULL){
                        d = it.GetNextValue();
                        if(d != NULL){
                        cout << d->GetDeclName() <<endl;
                        }
                     }

                    cout << field->GetName() << endl;
                    if(func->GetScope()->CheckDecl(field->GetName())){
                        Decl* t = func->GetScope()->CheckDecl(field->GetName());
                        cout << "kuaegliugweluogt; w/1092498127409 " << t->GetDeclName() << endl;
                        returnType = t->GetType();
                        Assert(t->GetType() != NULL);
                        cout << "herherere" << endl;
                        Assert(returnType!=NULL);
                        cout << returnType->GetTypeName() << endl;
                        return;
                     }
                     else{
                        cout << "kuaegliugweluogt; w/1-92901270847128" << endl;
                        List<Decl*>* implement = func->GetImplementScope();
                        if(implement != NULL){
                            for(int i = 0; i < implement->NumElements(); i++){
                                SymbolTable* s = implement->Nth(i)->GetScope();
                                Decl* funct = s->CheckDecl(field->GetName());
                                if(funct != NULL){
                                    List<VarDecl*>* vDecl = func->GetFormals();
                                    for(int i = 0; i < actuals->NumElements(); i++){
                                        Type* actualsT = actuals->Nth(i)->GetType();
                                        Type* varDeclT = vDecl->Nth(i)->GetType();
                                        if(strcmp(actualsT->GetTypeName(), varDeclT->GetTypeName()) != 0){
                                            if(actualsT->isNamedType() && varDeclT->isNamedType()){
                                                if(actuals->Nth(i)->GetType()->IsCompatible(varDeclT->GetType(), localScope)){
                                                    continue;
                                                }
                                                ReportError::NotCompatible(vDecl->Nth(i), actualsT);
                                                return;
                                            }
                                            ReportError::ArgMismatch(this, i, actualsT, varDeclT);
                                            return;
                                        }
                                    }
                                    returnType = func->GetType();
                                    return;
                                }
                            }
                        }
                    }
                    ReportError::FieldNotFoundInBase(new Identifier(*this->location, field->GetName()), classType);
                    return;
                }// ext != NULL
                Assert(ext != NULL);
                extended = ext->GetScope();

                while(extended != NULL && !found){
                    func = extended->GetClassDecl()->GetScope()->CheckDecl(field->GetName());
                    if(func != NULL){
                        found = true;
                    }
                    Decl* temp = extended->GetClassDecl()->GetExtendScope();
                    if(temp){
                         extended = temp->GetScope();
                    }
                    else{
                        extended = NULL;
                    }
                }
                if(!found){
                    ReportError::FieldNotFoundInBase(new Identifier(*this->location, field->GetName()), classType);
                    return;
                }
            }
            else{
                //Error no class
                return;
            }

            List<VarDecl*>* vDecl = func->GetFormals();
            for(int i = 0; i < actuals->NumElements(); i++){
                Type* actualsT = actuals->Nth(i)->GetType();
                Type* varDeclT = vDecl->Nth(i)->GetType();
                if(strcmp(actualsT->GetTypeName(), varDeclT->GetTypeName()) != 0){
                    if(actualsT->isNamedType() && varDeclT->isNamedType()){
                        if(actuals->Nth(i)->GetType()->IsCompatible(varDeclT->GetType(), localScope)){
                            continue;
                        }
                        ReportError::NotCompatible(vDecl->Nth(i), actualsT);
                        return;
                    }
                    ReportError::ArgMismatch(this, i, actualsT, varDeclT);
                    return;
                }
            }
            returnType = func->GetType();
            return;
        }
    }
    else {
        SymbolTable* current = new SymbolTable();
        current = localScope;
        bool found = false;

        while(current != NULL && !found){
            decl = current->CheckDecl(field->GetName());
            if(decl != NULL){
                found = true;
            }
            current = current->GetParentTable();
        }
        if(!found){
            ReportError::IdentifierNotDeclared(field, LookingForFunction);
            return;
        }
        else{
            List<VarDecl*>* vDecl = decl->GetFormals();
            if(actuals->NumElements() != vDecl->NumElements()){
                ReportError::NumArgsMismatch(field, vDecl->NumElements(), actuals->NumElements());
                return;
            }
            else{
                for(int i = 0; i < actuals->NumElements(); i++){
                    Type* actualsT = actuals->Nth(i)->GetType();
                    Type* varDeclT = vDecl->Nth(i)->GetType();

                    if(strcmp(actualsT->GetTypeName(), varDeclT->GetTypeName()) != 0){
                        if(actualsT->isNamedType() && varDeclT->isNamedType()){
                            if(actuals->Nth(i)->GetType()->IsCompatible(varDeclT->GetType(), localScope)){
                                continue;
                            }
                            ReportError::NotCompatible(vDecl->Nth(i), varDeclT);
                            return;
                        }
                        ReportError::ArgMismatch(this, i, actualsT, varDeclT);
                        return;
                    }
                }
                returnType = decl->GetType();
                return;
            }
        }//end else
    }//end else
}

Type* Call::GetType(){
    return returnType;
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
    if (strcmp(elemType->GetTypeName(), Type::voidType->GetTypeName()) == 0){
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

