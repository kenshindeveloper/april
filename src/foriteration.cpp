#include "../headers/foriteration.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    ForIteration::~ForIteration()
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

        if (block != nullptr)
        {
            delete block;
            block = nullptr;
        }
    }

    Symbol* ForIteration::codeGen(CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);

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
				return Error::call(context, 124, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        Symbol* result = nullptr;
        
        block->type_scope = BlockScope::FOR;
        block->prev = context.getCurrentBlock();
		Block* tmp_block = context.getCurrentBlock();
        context.setCurrentBlock(block);
       
        ident->codeGen(context);
        Symbol* sym_ident = context.findIdentLocals(ident->getName());
        
		if (sym_ident == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}
        
		Symbol* sym_tmp = sym_expr->prox;
		if (sym_tmp == nullptr) result = new Symbol{};
        while (sym_tmp != nullptr && !block->stop)
        {
            sym_ident->type = sym_tmp->type;
            sym_ident->value = sym_tmp->value;

            result = block->codeGen(context);
            if (result == nullptr)
                return nullptr;
                
            sym_tmp = sym_tmp->prox;
        }

        block->stop = false;
        //context.popCurrentBlock();
		//------------------------
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