#include "../headers/vardeclarationglobal.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    VarDeclarationGlobal::~VarDeclarationGlobal()
    {
        if (ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }

        if (type != nullptr)
        {
            delete type;
            type = nullptr;
        }

        if (expr != nullptr)
        {
            delete expr;
            expr = nullptr;
        }
    }

    Symbol* VarDeclarationGlobal::codeGen(CodeGenContext& context)
    {
        if (context.scope_type != Scope::BLOCK)
        {
			if (context.getError() == 0)
				return Error::call(context, 9, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }

        if (context.existIdenGlobals(ident->getName()) != nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 8, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        
        if (context.typeOf(type->getName()) == Type::UNDEFINED)
        {
			if (context.getError() == 0)
				return Error::call(context, 61, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }

        Type tmp_type = context.typeOf(type->getName());
        Symbol* sym_expr = expr->codeGen(context);
        if (sym_expr == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }

        if ((tmp_type != sym_expr->type) && !(tmp_type == Type::DOUBLE && sym_expr->type == Type::INTEGER))
        {
			if (context.getError() == 0)
				return Error::call(context, 23, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        
        Symbol* sym = new Symbol{};
        sym->name = ident->getName();
        sym->type = tmp_type;
        
        if (sym->type == Type::DOUBLE && sym_expr->type == Type::INTEGER)
            sym->value._dval = sym_expr->value._ival;
        else
            sym->value = sym_expr->value;

        sym->is_constant = false;
        sym->is_variable = true;
        sym->prox = sym_expr->prox;
        sym->down = sym_expr->down;
        context.getGlobals().push_back(sym);
        return sym;
    }
}