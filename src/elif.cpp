#include "../headers/elif.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april 
{
	ElIf::~ElIf()
	{
		if (_then != nullptr)
		{
			delete _then;
			_then = nullptr;
		}

		if (_else != nullptr)
		{
			delete _else;
			_else = nullptr;
		}
		
		/*for (Statement* stmt : *stmt_list)
			delete stmt;
		
		stmt_list->clear();*/
	}

	Symbol* ElIf::exprBlock(CodeGenContext& context)
	{
		Symbol* sym_expr = expr->codeGen(context);

		if (sym_expr == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}

		Symbol* result = nullptr;

		if (sym_expr->type != Type::BOOLEAN)
		{
			if (context.getError() == 0)
				return Error::call(context, 62, april_errors->file_name, april_errors->line, sym_expr->name);
			else
				return nullptr;
		}

		if (sym_expr->value._bval == true)
		{
			_then->type_scope = BlockScope::IF;
			_then->prev = context.getCurrentBlock();
			Block* tmp_block = context.getCurrentBlock();
			context.setCurrentBlock(_then);

			result = _then->codeGen(context);


			_then->locals.clear();
			if (context.getStackFunc() == nullptr || (context.getStackFunc() != nullptr && !context.getStackFunc()->top()->isTmp()))
			{
				context.popCurrentBlock();
				_then->prev = nullptr;
			}
			else
				_then->prev = tmp_block;
		}
	
		return result;
	}

	Symbol* ElIf::codeGen(CodeGenContext& context)
	{
		Symbol* result = nullptr;
		
		if (stmt_list == nullptr)
		{
			result = exprBlock(context);
			return result;
		}
		else
		{
			result = exprBlock(context);
			if (result == nullptr && context.getError() > 0)
			{
				if (context.getError() == 0)
					return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
				else
					return nullptr;
			}
			else if (result == nullptr && context.getError() == 0)
			{
				for (Statement* stmt : *stmt_list)
				{
					result = stmt->codeGen(context);
					if (result == nullptr && context.getError() > 0)
					{
						if (context.getError() == 0)
							return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
						else
							return nullptr;
					}

					if (result != nullptr) break;
				}
			}
		}

		if (_else != nullptr && result == nullptr)
		{
			_else->type_scope = BlockScope::IF;
			_else->prev = context.getCurrentBlock();
			Block* tmp_block = context.getCurrentBlock();
			context.setCurrentBlock(_else);

			result = _else->codeGen(context);

			_else->locals.clear();
			if (context.getStackFunc() == nullptr || (context.getStackFunc() != nullptr && !context.getStackFunc()->top()->isTmp()))
			{
				context.popCurrentBlock();
				_else->prev = nullptr;
			}
			else
				_else->prev = tmp_block;
		}

		return result;
	}
}