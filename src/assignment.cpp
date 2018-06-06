#include "../headers/assignment.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Assignment::~Assignment()
    {
        
    }

    Symbol* Assignment::codeGen(CodeGenContext& context)
    {
		if (ident == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 31, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}
       
		if (ident != nullptr && !context.existIdenLocals(ident->getName()))
		{
			if (context.getError() == 0)
				return Error::call(context, 21, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
		}
        
        Symbol* symbol = context.findIdentLocals(ident->getName());
        Symbol* sym_expr = expr->codeGen(context);

		if ((symbol->type != sym_expr->type) && !(symbol->type == Type::DOUBLE && sym_expr->type == Type::INTEGER))
		{
			if (context.getError() == 0)
				return Error::call(context, 23, april_errors->file_name, april_errors->line, "name: " + symbol->name);
			else
				return nullptr;
		}

        if (symbol->type == Type::DOUBLE && sym_expr->type == Type::INTEGER)
            symbol->value._dval = sym_expr->value._ival;
        else
            symbol->value = sym_expr->value;
        
        //std::cout <<*sym_expr<< " " << *symbol<< std::endl;

        symbol->prox = sym_expr->prox;
        symbol->down = sym_expr->down;

        return symbol; //devuelve la expresion OJO
    }
}