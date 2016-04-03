/*
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"

using namespace std;

SymbolTable::SymbolTable(){
    this->symbolTable = new Hashtable<Decl*>();
}

Hashtable<Decl*>* SymbolTable::getHashTablePointer(){
    return this->symbolTable;
}

void SymbolTable::AddDecl(Decl* newEntry, bool overwrite){
    symbolTable->Enter(newEntry->GetDeclName(), newEntry, overwrite);
}

Decl* SymbolTable::CheckDecl(const char* t){
    return symbolTable->Lookup(t);
}

Decl* SymbolTable::CheckDecl(Decl* d){
    return symbolTable->Lookup(d->GetDeclName());
}

Decl* SymbolTable::CheckDecl(NamedType* t){
    return symbolTable->Lookup(t->GetTypeName());
}

void SymbolTable::SetBreakCheck(Stmt* d){
    this->breakCheck = d;
}

void SymbolTable::SetClassDecl(ClassDecl* d){
    this->decl = d;
}

void SymbolTable::SetFnDecl(FnDecl* d){
    this->fnDecl = d;
}

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    /* Assignment 3
     * ============
     * Here is where the semantic analyzer is kicked off.  The general
     * idea is to perform a tree traversal of the entire program,
     * examining all constructs for compliance with the semantic
     * rules.  Each node can have its own way of checking itself,
     * which makes for a great use of inheritance and polymorphism in
     * the node classes.
     */
     SymbolTable* symbolT = new SymbolTable();
     if(needsSymbolTable() == true){
        this->globalSymbolTable = symbolT;
     }
     globalSymbolTable =  new SymbolTable();
     //Build the symbol table
     BuildScope();
     //Check everything
     for (int i = 0; i < decls->NumElements(); i++){
        decls->Nth(i)->Check();
     }
}

void Program::BuildScope(){
    this->globalSymbolTable->SetParentTable(NULL);
    for (int i = 0; i < decls->NumElements(); i++){
        Decl* d = decls->Nth(i);
        Decl* n = this->globalSymbolTable->CheckDecl(d->GetDeclName());
        bool overwrite = false;
        if(n != NULL){
            ReportError::DeclConflict(d, n);
            //Throw error and return
            //return;
        }
        this->globalSymbolTable->AddDecl(d, overwrite);
    }

    for (int i = 0; i < decls->NumElements(); i++){
        decls->Nth(i)->BuildScope(this->globalSymbolTable);
    }
}

void Program::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    printf("\n");
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}

void StmtBlock::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);
    for(int i = 0; i < decls->NumElements(); i++){
        Decl* n = localScope->CheckDecl(decls->Nth(i)->GetDeclName());
        bool overwrite = false;
        if(n != NULL){
            //Throw error and return
            ReportError::DeclConflict(decls->Nth(i), n); //Not sure what to throw here so throwing this.
            return;
        }
        localScope->AddDecl(decls->Nth(i), overwrite);
    }
    for(int i = 0; i < stmts->NumElements(); i++){
        stmts->Nth(i)->BuildScope(localScope);
    }
}

void StmtBlock::Check(){
    for(int i = 0; i < stmts->NumElements(); i++){
        stmts->Nth(i)->Check();
    }
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this);
    (body=b)->SetParent(this);
}

void ConditionalStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);

    test->BuildScope(s);
    body->BuildScope(s);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) {
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) {
    init->Print(indentLevel+1, "(init) ");
    test->Print(indentLevel+1, "(test) ");
    step->Print(indentLevel+1, "(step) ");
    body->Print(indentLevel+1, "(body) ");
}

void ForStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);
    localScope->SetBreakCheck(this);

    init->BuildScope(s);
    test->BuildScope(s);
    step->BuildScope(s);
    body->BuildScope(s);
}

void ForStmt::Check(){
    init->Check();
    test->Check();
    Type* t = test->GetType();
    if(t->GetTypeName() != Type::boolType->GetTypeName()){
        ReportError::TestNotBoolean(test);
    }

    step->Check();

    body->Check();
}

void WhileStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(body) ");
}

void WhileStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);
    localScope->SetBreakCheck(this);

    test->BuildScope(localScope);
    body->BuildScope(localScope);
}

void WhileStmt::Check(){
    Assert(test->GetType() != NULL);
    if(test->GetType()->GetTypeName() != Type::boolType->GetTypeName()){
        ReportError::TestNotBoolean(test);
    }
    test->Check();
    body->Check();
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(then) ");
    if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}

void IfStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);
    test->BuildScope(s);
    body->BuildScope(s);

    if(elseBody){
        elseBody->BuildScope(s);
    }
}

void IfStmt::Check(){
    test->Check();
    body->Check();

    if(test->GetType()->GetTypeName() != Type::boolType->GetTypeName()){
        ReportError::TestNotBoolean(test);
    }

    if(elseBody){
        elseBody->Check();
    }
}

void BreakStmt::Check(){
    SymbolTable* current = new SymbolTable();
    current = localScope;
    bool found = false;
    while(current != NULL && !found){
        Stmt* s = current->GetBreakCheck();
        if(s != NULL){
            if(s->canBreak()){
                found = true;
            }
        }
        current = current->GetParentTable();
    }

    if(!found){
        ReportError::BreakOutsideLoop(this);
    }
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) {
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope = s;

    expr->BuildScope(s);
}

void ReturnStmt::Check(){
    expr->Check();

    SymbolTable* current = localScope;
    if(current->GetParentTable() == NULL){
        //Error: return used outside a function.
        cout << "Error: return used outside a function." << endl;
        return;
    }

    FnDecl* decl;
    bool found = false;
    while(current != NULL && !found){
        decl = current->GetFnDecl();
        if(decl != NULL){
            found = true;
        }
        current = current->GetParentTable();
    }
    if(!found){
        //return not used in a function
    }
    if(expr->isEmpty()){
        if(decl->GetType() == Type::voidType){
            return;
        }
        else{
            ReportError::ReturnMismatch(this, expr->GetType(), decl->GetType());
            return;
        }
    }


    Type* t = expr->GetType();
    if(t == NULL){
        return;
    }
    else{
        if( t->GetTypeName() == decl->GetType()->GetTypeName()){
            return;
        }
        else{
            ReportError::ReturnMismatch(this, t, decl->GetType());
            return;
        }
    }
}


void ReturnStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
}

PrintStmt::PrintStmt(List<Expr*> *a) {
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope = s;

    for(int i = 0; i < args->NumElements(); i++){
        args->Nth(i)->BuildScope(s);
    }
}

void PrintStmt::Check(){
    for(int i = 0; i < args->NumElements(); i++){
        Type* t = args->Nth(i)->GetType();
        if(t != Type::intType && t != Type::boolType && t != Type::stringType){
            ReportError::PrintArgMismatch(args->Nth(i), i, t);
        }
    }
}

void PrintStmt::PrintChildren(int indentLevel) {
    args->PrintAll(indentLevel+1, "(args) ");
}

SwitchLabel::SwitchLabel(IntConstant *l, List<Stmt*> *s) {
    Assert(l != NULL && s != NULL);
    (label=l)->SetParent(this);
    (stmts=s)->SetParentAll(this);
}

SwitchLabel::SwitchLabel(List<Stmt*> *s) {
    Assert(s != NULL);
    label = NULL;
    (stmts=s)->SetParentAll(this);
}

void SwitchLabel::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);
    for(int i = 0; i < stmts->NumElements(); i++){
        stmts->Nth(i)->BuildScope(s);
    }
}

void SwitchLabel::Check(){
    for(int i = 0; i < stmts->NumElements(); i++){
        stmts->Nth(i)->Check();
    }
}

void SwitchLabel::PrintChildren(int indentLevel) {
    if (label) label->Print(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}

SwitchStmt::SwitchStmt(Expr *e, List<Case*> *c, Default *d) {
    Assert(e != NULL && c != NULL && c->NumElements() != 0 );
    (expr=e)->SetParent(this);
    (cases=c)->SetParentAll(this);
    def = d;
    if (def) def->SetParent(this);
}

void SwitchStmt::BuildScope(SymbolTable* s){
    localScope = new SymbolTable();
    localScope->SetParentTable(s);
    localScope->SetBreakCheck(this);

    expr->BuildScope(s);

    if(def) def->BuildScope(localScope);
    for (int i = 0; i < cases->NumElements(); i++){
        cases->Nth(i)->BuildScope(localScope);
    }
}

void SwitchStmt::Check(){
    if(expr->GetType()->GetTypeName() != Type::intType->GetTypeName()){
        ReportError::SwitchStmtNotInt(expr);
        return;
    }

    expr->Check();
    if(def) def->Check();
    for(int i = 0; i < cases->NumElements(); i++){
        cases->Nth(i)->Check();
    }
}

void SwitchStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
    cases->PrintAll(indentLevel+1);
    if (def) def->Print(indentLevel+1);
}
