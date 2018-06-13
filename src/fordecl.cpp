#include "headers/fordecl.hpp"
#include "headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	ForDecl::~ForDecl()
	{
	
	}

	Symbol* ForDecl::codeGen(CodeGenContext& context)
	{
		Symbol* result = nullptr;
		block->type_scope = BlockScope::FOR;
		block->prev = context.getCurrentBlock();
		Block* tmp_block = context.getCurrentBlock();
		context.setCurrentBlock(block);
		declaration->codeGen(context);

		Symbol* sym_condition = condition->codeGen(context);
		if (sym_condition == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 62, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}

		if (sym_condition->type != Type::BOOLEAN)
		{
			if (context.getError() == 0)
				return Error::call(context, 62, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}

		if (!sym_condition->value._bval)
		{
			result = new Symbol{};
			result->type = Type::INTEGER;
			result->value._ival = 0;
			result->is_constant = true;
			result->is_variable = false;
		}

		while (sym_condition->value._bval && !block->stop)
		{
			result = block->codeGen(context);
			if (result == nullptr)
				return nullptr;

			if (!block->stop)
			{
				increment->codeGen(context);
				sym_condition = condition->codeGen(context);
			}
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