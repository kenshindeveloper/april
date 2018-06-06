#include "../headers/assigbioperator.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* AssigBioperator::codeGen(CodeGenContext& context)
    {
		if (!context.existIdenLocals(ident->getName()))
		{
			if (context.getError() == 0)
				return Error::call(context, 32, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
		}

        Symbol*& symbol = context.findIdentLocals(ident->getName());
        Symbol* sym_expr = expr->codeGen(context);

		if ((symbol->type != sym_expr->type) && !(symbol->type == Type::DOUBLE && sym_expr->type == Type::INTEGER))
		{
			if (context.getError() == 0)
				return Error::call(context, 23, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
		}
        
        Symbol* tmp = new Symbol{};

        switch (ope)
        {
            case OPE::PLUS:
                tmp = *symbol + *sym_expr;
                symbol->value = tmp->value;
                break;
            
            case OPE::MIN:
                tmp = *symbol - *sym_expr;
                symbol->value = tmp->value;
                break;

            case OPE::MUL:
                tmp = *symbol * *sym_expr;
                symbol->value = tmp->value;
                break;

            case OPE::DIV:
                tmp = *symbol / *sym_expr;
                symbol->value = tmp->value;
                break;
        }

        delete tmp;

        return symbol;
    }
}