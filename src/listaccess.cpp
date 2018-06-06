#include "../headers/listaccess.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/stringarray.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    ListAccess::~ListAccess()
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

        if (expr_index != nullptr)
        {
            delete expr_index;
            expr_index = nullptr;
        }
    }

    Symbol* ListAccess::codeGen(CodeGenContext& context)
    {       
        if (ident == nullptr && expr == nullptr)
        {
            if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else 
				return nullptr;
        }

        if (ident != nullptr && !context.existIdenLocals(ident->getName()))
        {
			if (context.getError() == 0)
				return Error::call(context, 32, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }

        Symbol* sym_expr = nullptr;
        if (ident != nullptr && context.findIdentLocals(ident->getName())->type == Type::STRING)
        {
            StringArray* tmp = new StringArray(ident, expr_index);
            sym_expr = tmp->codeGen(context);
            return sym_expr;
        }
 
        Symbol* sym_index = expr_index->codeGen(context);
        if (sym_index->type != Type::INTEGER)
        {
			if (context.getError() == 0)
				return Error::call(context, 161, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        if (ident != nullptr) { sym_expr = context.findIdentLocals(ident->getName()); }
        else {sym_expr = expr->codeGen(context);}
        if (sym_expr == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        if (sym_expr->type != Type::LIST)
        {
			if (context.getError() == 0)
				return Error::call(context, 71, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        int i = 0; 
        sym_expr = sym_expr->prox;
        for (; i < sym_index->value._ival && sym_expr != nullptr; i += 1)
            sym_expr = sym_expr->prox;
        
        if (sym_expr == nullptr && i != sym_index->value._ival)
        {
			if (context.getError() == 0)
				return Error::call(context, 72, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        if (sym_expr->type == Type::LIST_DOWN && sym_expr->down != nullptr)
            sym_expr = sym_expr->down;

        return sym_expr;
    }
};