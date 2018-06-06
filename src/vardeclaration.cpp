#include <iostream>
#include "../headers/vardeclaration.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/assignment.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    VarDeclaration::~VarDeclaration()
    {
        if (type != nullptr)
            delete type;
        
        if (ident != nullptr)
            delete ident;

        /*if (expr != nullptr)
            delete expr;*/
    }

    Symbol* VarDeclaration::codeGen(CodeGenContext& context)
    {
        Symbol* symbol = nullptr;
        if ((context.existIdenGlobals(ident->getName()) != nullptr) || (context.scope_type == Scope::BLOCK)?(context.existIdenLocals(ident->getName())):(context.getCurrentFunction()->existIdenLocals(ident->getName())))
        {
			if (context.getError() == 0)
				return Error::call(context, 1, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        
        ident->codeGen(context);
        if (context.scope_type == Scope::BLOCK)
            symbol = context.findIdentLocals(ident->getName());
        else
            symbol = context.getCurrentFunction()->existIdenLocals(ident->getName());

        if (context.typeOf(type->getName()) == Type::UNDEFINED)
        {
			if (context.getError() == 0)
				return Error::call(context, 61, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        
        symbol->type = context.typeOf(type->getName());
        symbol->is_variable = true;
        if (expr)
        {
            Assignment* assig = new Assignment{ident, expr};
            symbol = assig->codeGen(context);            
        }
        
        return symbol;
    }
}