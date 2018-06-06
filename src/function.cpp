#include "../headers/function.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Function::~Function()
    {
        if (is_tmp && last != nullptr)
        {
            delete last;
            last = nullptr;
        }

        if (!is_tmp && ident != nullptr)
        {
            delete ident;
            ident = nullptr;
        }
        
        if (!is_tmp && block != nullptr)
        {
            delete block;
            block = nullptr;
        }

        if (!is_tmp)
        {
            for (VarDeclaration* arg : *args)
            {
                if (arg != nullptr)
                {
                    delete arg;
                    args = nullptr;
                }
            }
        }        
    }

    Symbol* Function::codeGen(CodeGenContext& context)
    {
        
        if (context.getCurrentBlock()->existFunction(ident->getName()))
        {
			if (context.getError() == 0)
				return Error::call(context, 131, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        
		if (context.getStackFunc() != nullptr && context.getStackFunc()->top()->getName() == ident->getName())
		{
			if (context.getError() == 0)
				return Error::call(context, 131, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
		}

		context.getCurrentBlock()->addFunction(ident->getName(), this);

		Block* aux = context.getCurrentBlock();
		while (aux != nullptr)
		{
			CallFunctionList::iterator itera = aux->getFunctions().begin();

			for (; itera != aux->getFunctions().end(); itera++)
				block->getFunctions()[itera->first] = itera->second;

			aux = aux->prev;
		}

        last = new Symbol{};
        return last;
    }

    Symbol* Function::runCode(CodeGenContext& context)
    {
        Block* tmp_block = context.getCurrentBlock();
        std::vector<Symbol*> tmp_locals = context.getCurrentBlock()->locals;
        block->type_scope = BlockScope::FUNCTION;
        context.push_block(block);
        context.getCurrentBlock()->locals = locals;
        last = block->codeGen(context); //recorre las declaraciones
        
        context.pop_block();
        context.setCurrentBlock(tmp_block);
        context.getCurrentBlock()->locals = tmp_locals;

        locals.clear();

        block->stop = false;
        return last;
    }

    Symbol* Function::existIdenLocals(std::string name)
    {
        for (Symbol*& symbol : locals)
            if (symbol->name == name)
                return symbol;
        
        return nullptr;
    }
}