#include "../headers/vardeclarationdeduce.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    VarDeclarationDeduce::~VarDeclarationDeduce()
    {
        if (ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }

        if (expr != nullptr)
        {
            delete expr;
            expr = nullptr;
        }
    }

    Symbol* VarDeclarationDeduce::codeGen(CodeGenContext& context)
    {
        if (context.existIdenGlobals(ident->getName()) || context.existIdenLocals(ident->getName()))
        {
			if (context.getError() == 0)
				return Error::call(context, 1, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        Symbol* sym_expr = expr->codeGen(context);

        if (sym_expr == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        if (sym_expr->type == Type::UNDEFINED)
        {
			if (context.getError() == 0)
				return Error::call(context, 61, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }

        Symbol* sym = new Symbol{};
        sym->name = ident->getName();
        sym->type = sym_expr->type;
        sym->is_variable = true;
        sym->is_constant = false;
        sym->value = sym_expr->value;
        sym->prox = sym_expr->prox;
        sym->down = sym_expr->down;
        context.getCurrentBlock()->locals.push_back(sym);
        
        return sym;
    }
}