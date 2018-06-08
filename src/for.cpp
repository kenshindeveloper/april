#include "../headers/for.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    For::~For()
    {
        if (block != nullptr)
        {
            delete block;
            block = nullptr;
        }
    }

    Symbol* For::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
		if (sym_expr == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 62, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}

		if (sym_expr->type != Type::BOOLEAN)
		{
			if (context.getError() == 0)
				return Error::call(context, 62, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}

        Symbol* result = nullptr;
        block->type_scope = BlockScope::FOR;
        block->prev = context.getCurrentBlock();
		Block* tmp_block = context.getCurrentBlock();
        context.setCurrentBlock(block);
       
		if (!sym_expr->value._bval)
		{
			result = new Symbol{};
			result->type = Type::INTEGER;
			result->value._ival = 0;
			result->is_constant = true;
			result->is_variable = false;
		}

        while (sym_expr->value._bval && !block->stop)
        {

            result = block->codeGen(context);
            if (result == nullptr)
                return nullptr;
                
            if (!block->stop)
                sym_expr = expr->codeGen(context);
                
        }

        block->stop = false;
        //context.popCurrentBlock();
		//--------------------
		if (context.getStackFunc() == nullptr || (context.getStackFunc() != nullptr && !context.getStackFunc()->top()->isTmp()))
		{
			context.popCurrentBlock();
			block->prev = nullptr;
		}
		else
			block->prev = tmp_block;

        return result;     
    }
}