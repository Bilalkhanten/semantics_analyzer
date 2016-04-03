/*
 * Implementation of type node classes.
 */

#include <string.h>
#include "ast_type.h"
#include "ast_decl.h"

/*
 * Class constants
 * ---------------
 *
 * These are public constants for the built-in base types (int,
 * double, etc.)  They can be accessed with the syntax
 * Type::intType. This allows you to directly access them and share
 * the built-in types where needed rather that creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error");

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
}

bool Type::IsCompatible(Type* compatee, SymbolTable* locScope){
    Type* t_left = this;
    Type* t_compatee = compatee;
    Assert(t_left != NULL && t_compatee != NULL);
    if(strcmp(t_left->GetTypeName(), t_compatee->GetTypeName()) == 0){
        return true;
    }
    else{
        Decl* thisClass;
        Decl* otherClass;
        SymbolTable* current = new SymbolTable();
        SymbolTable* parentT = new SymbolTable();
        current = locScope;
        bool found = false;
        Assert(locScope != NULL);

        while(current != NULL && !found){
            thisClass = current->CheckDecl(t_left->GetTypeName());
            if(thisClass != NULL){
                found = true;
            }
            parentT = current;
            current = current->GetParentTable();
        }
        Decl* extends = thisClass->GetExtendScope();
        if(extends){
            if(extends->GetDeclName() == t_left->GetTypeName()){
                return true;
            }
            else{
                found = false;
                List<Decl*>* implements = thisClass->GetImplementScope();
                if(implements != NULL){
                    for(int i = 0; i < implements->NumElements(); i++){
                        const char* temp = implements->Nth(i)->GetDeclName();
                        if(strcmp(temp, t_compatee->GetTypeName()) == 0){
                            found = true;
                        }
                    }
                }
                current = locScope;
                while(!found && (extends || (implements->NumElements() > 0))){
                    if(extends){
                        if(strcmp(extends->GetDeclName(), t_compatee->GetTypeName()) == 0){
                            found = true;
                            return true;
                        }
                    }

                    for(int i = 0; i < implements->NumElements(); i++){
                        const char* temp = implements->Nth(i)->GetDeclName();
                        if(strcmp(temp, t_compatee->GetTypeName()) == 0){
                            found = true;
                            return true;
                        }
                    }

                    if(extends){
                        implements = extends->GetImplementScope();
                        if(implements == NULL){
                            implements = new List<Decl*>();
                        }
                        extends = extends->GetExtendScope();
                    }
                    else{
                        break;
                    }
                }
                if(!found){
                    ReportError::NotCompatible(thisClass, t_compatee);
                    return false;
                }
                return true;
            }
        }

        found = false;
        List<Decl*>* implements = thisClass->GetImplementScope();
        if(implements != NULL){
            for(int i = 0; i < implements->NumElements(); i++){
                const char* temp = implements->Nth(i)->GetDeclName();
                if(strcmp(temp, t_compatee->GetTypeName()) == 0){
                    found = true;
                }
            }
            if(!found){
                ReportError::NotCompatible(thisClass, t_compatee);
                return false;
            }
            return true;
        }
        return false;
    }
}


void Type::PrintChildren(int indentLevel) {
    printf("%s", typeName);
}

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
}

void NamedType::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}

void ArrayType::PrintChildren(int indentLevel) {
    elemType->Print(indentLevel+1);
}

int ArrayType::GetNumberOfDims() {
    Type* t = elemType;

    this->numberOfDims = 0;

    if(t->isArray() || isArray()){
        numberOfDims = 1;
        while(t->isArray()){
            this->numberOfDims++;
            t = t->GetType();
        }
    }

    return numberOfDims;
}

const char* ArrayType::GetTypeName(){
    return elemType->GetTypeName();
}
