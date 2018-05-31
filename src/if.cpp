#include <vector>
#include "../headers/if.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    If::~If()
    {
        // std::cout << "destructo IF" << std::endl;
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
    }

    Symbol* If::codeGen (CodeGenContext& context)
    {
        Symbol* sym_expr = expr->codeGen(context);
        Symbol* result = new Symbol{};

        if (sym_expr->type != Type::BOOLEAN)
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: la expresion no es un boolean.\n");
            context.addError();
            return nullptr;
        }

        if (sym_expr->value._bval == true)
        {
            _then->type_scope = BlockScope::IF;
            _then->prev = context.getCurrentBlock();
            Block* tmp_block = context.getCurrentBlock();
			context.setCurrentBlock(_then);
        
            result = _then->codeGen(context); 
            
			if (context.getStackFunc() == nullptr || (context.getStackFunc() != nullptr && !context.getStackFunc()->top()->isTmp()))
			{
				context.popCurrentBlock();
				_then->prev = nullptr;
			}
			/*else
				_then->prev = tmp_block;*/
        }
        else if (_else != nullptr) 
        {
            _else->type_scope = BlockScope::IF;
            _else->prev = context.getCurrentBlock();
			Block* tmp_block = context.getCurrentBlock();
			context.setCurrentBlock(_else);

            result = _else->codeGen(context);
            
			if (context.getStackFunc() == nullptr || (context.getStackFunc() != nullptr && !context.getStackFunc()->top()->isTmp()))
			{
				//std::cout << "chao" << std::endl;
				context.popCurrentBlock();
				_else->prev = nullptr;
			}
			else
			{
				//std::cout << "lolo" << std::endl;
				_else->prev = tmp_block;
			}
        }

        // if (result == nullptr)
        //     std::cout << "result es NULO (IF)" << std::endl;
        // else
        //     std::cout << "result (IF): " << *result << std::endl;
        // std::cout << "fin if" << std::endl;
        
        return result;
    }
}