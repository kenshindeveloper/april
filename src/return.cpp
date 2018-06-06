#include "../headers/return.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Return::~Return()
    {
        
    }

    Symbol* Return::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        
        if (sym_expr == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        if (sym_expr->type == Type::UNDEFINED)
        {
			if (context.getError() == 0)
				return Error::call(context, 32, april_errors->file_name, april_errors->line, sym_expr->name);
			else
				return nullptr;
        }

        context.stopRootBlock();
        return sym_expr;
    }
}