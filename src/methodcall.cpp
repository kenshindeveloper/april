#include <iostream>
#include "../headers/methodcall.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/methodhandlecast.hpp"
#include "../headers/funclist.hpp"
#include "../headers/methodhandleio.hpp"

extern april::STRUCINFO* april_errors;

namespace april 
{
    MethodCall::~MethodCall()
    {
    }

    Symbol* MethodCall::codeGen(CodeGenContext& context)
    {
        if (ident->getName() == "println" || ident->getName() == "print" || ident->getName() == "input")
        {
            MethodHandleIo* method_handle_io = new MethodHandleIo(ident,args);
            Symbol* tmp = method_handle_io->codeGen(context);
            if (tmp == nullptr)
            {
				if (context.getError() == 0)
					return Error::call(context, 6, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
            }
            delete method_handle_io;
            method_handle_io = nullptr;
            context.getCurrentBlock()->locals.push_back(tmp);

            return tmp;
        }
        else if (ident->getName() == "double" || ident->getName() == "int" || ident->getName() == "str")
        {
            MethodHandleCast* mothod_handle_cast = new MethodHandleCast(ident,args);
            Symbol* tmp = mothod_handle_cast->codeGen(context);
            if (tmp == nullptr)
            {
				if (context.getError() == 0)
					return Error::call(context, 6, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
            }
            delete mothod_handle_cast;
            mothod_handle_cast = nullptr;
            // context.getCurrentBlock()->locals.push_back(tmp);
            
            return tmp;
        }
        else if (ident->getName() == "open")
        {
            if (args->size() == 2)
            {
                Symbol* name = (*args)[0]->codeGen(context);
                Symbol* type = (*args)[1]->codeGen(context);
                if (name->type != Type::STRING || type->type != Type::STRING)
                {
					if (context.getError() == 0)
						return Error::call(context, 133, april_errors->file_name, april_errors->line, ident->getName());
					else
						return nullptr;
                }

                Symbol* tmp = file::open(*name->value._sval, *type->value._sval);
                // context.getCurrentBlock()->locals.push_back(tmp);
                
                return tmp;
            }
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
            }
        }
        else if (ident->getName() == "range")
        {
            if (args->size() == 1)
            {
                Symbol* last = (*args)[0]->codeGen(context);
                if (last->type != Type::INTEGER)
                {
					if (context.getError() == 0)
						return Error::call(context, 133, april_errors->file_name, april_errors->line, ident->getName());
					else
						return nullptr;
                }
                Symbol* tmp = lib::range(last);
                return tmp;
            }
            else if (args->size() == 2)
            {
                Symbol* first = (*args)[0]->codeGen(context);
                Symbol* last = (*args)[1]->codeGen(context);
                if (first->type != Type::INTEGER || last->type != Type::INTEGER)
                {
					if (context.getError() == 0)
						return Error::call(context, 133, april_errors->file_name, april_errors->line, ident->getName());
					else
						return nullptr;
                }
                Symbol* tmp = lib::range(first, last);
                return tmp;
            }
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
            }
        }     
		else if (ident->getName() == "time")
		{
			if (args->size() == 0)
			{
				Symbol* tmp = time::time();
				return tmp;
			}
			else
			{
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
			}
		}
        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------

        if (!context.getCurrentBlock()->existFunction(ident->getName()))
        {
			if (context.getError() == 0)
				return Error::call(context, 134, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }


        if (args->size() != context.getCurrentBlock()->getFunctions(ident->getName())->getArgs()->size())
        {
			if (context.getError() == 0)
				return Error::call(context, 132, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }

        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------

        if (context.getStackFunc() != nullptr && context.getStackFunc()->top()->getName() == ident->getName())
        {
            Identifier* tmp_ident = context.getStackFunc()->top()->getIdent();
            VarList* tmp_var_list = context.getStackFunc()->top()->getArgs();
            Block* tmp_block =  context.getStackFunc()->top()->getBlock()->clone();
            context.getStackFunc()->push(new Function{tmp_ident, tmp_var_list, tmp_block, true});
		}
        else
        {
            if (context.getStackFunc() == nullptr) 
                context.getStackFunc() = new std::stack<Function*>();

            context.getStackFunc()->push(context.getCurrentBlock()->getFunctions(ident->getName()));
        }


		/*if (context.getStackFunc() == nullptr)
			context.getStackFunc() = new std::stack<Function*>();


		Block* tmp_block = nullptr;
		if (context.getStackFunc()->size() > 0 && context.getStackFunc()->top()->getName() == ident->getName())
		{
			tmp_block = context.getStackFunc()->top()->getBlock();
		}
		

		context.getStackFunc()->push(context.getCurrentBlock()->getFunctions(ident->getName()));
		context.getStackFunc()->top()->getLocals().clear();

		std::vector<Symbol*> tmp_vector;
		if (tmp_block != nullptr)
			for (Symbol* sym : tmp_block->locals)
				tmp_vector.push_back(sym);*/

        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        VarList* var_list = context.getCurrentBlock()->getFunctions(ident->getName())->getArgs();
        ExpressionList::iterator ite_args = args->begin();
        VarList::iterator ite_para_fn = var_list->begin();
        Symbol* sym_0 = nullptr;
        Symbol* sym_1 = nullptr;

        while (ite_args != args->end())
        {
            sym_0 = (*ite_args)->codeGen(context);
            
            context.scope_type = Scope::FUNCTION;
            context.setCurrentFunction(context.getStackFunc()->top());
            sym_1 = (*ite_para_fn)->codeGen(context);
            context.scope_type = Scope::BLOCK;
            context.setCurrentFunction(nullptr);
            
            if (sym_0 == nullptr || sym_1 == nullptr)
            {
				if (context.getError() == 0)
					return Error::call(context, 6, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
            }

            if ((sym_0->type != sym_1->type) && !(sym_0->type == Type::INTEGER && sym_1->type == Type::DOUBLE)) //FALTA VALIDAR DOUBLE
            {
				if (context.getError() == 0)
					return Error::call(context, 133, april_errors->file_name, april_errors->line, ident->getName());
				else
					return nullptr;
            }

			if (sym_0->type != Type::LIST)
                sym_1->value = sym_0->value; 
			else
            {
				if (sym_0->prox != nullptr)
					sym_1->prox = list::clone_syms(sym_0->prox);
				else
					sym_1->prox = nullptr;

				if (sym_0->down != nullptr)
					sym_1->down = list::clone_syms(sym_0->down);
				else
					sym_1->down = nullptr;

				sym_1->in_list = true;
            }

            ite_args++;
            ite_para_fn++;
        }
        
        Symbol* sym = context.getStackFunc()->top()->runCode(context);

		/*if (tmp_block != nullptr)
			context.getStackFunc()->top()->getBlock()->locals = tmp_vector;*/

        if (sym == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, ident->getName());
			else
				return nullptr;
        }
        
        if (context.getStackFunc() != nullptr && !context.getStackFunc()->empty())
        {
            if (context.getStackFunc()->top()->getName() == ident->getName() && context.getStackFunc()->size() > 1)
            {
				bool flag = context.getStackFunc()->top()->isTmp();
				context.getStackFunc()->pop();
				if (flag) context.setCurrentBlock(context.getStackFunc()->top()->getBlock());
			}
            else if (context.getStackFunc()->size() == 1)
            {
                context.getStackFunc()->pop();
                delete context.getStackFunc();                
                context.getStackFunc() = nullptr;
            }
        }
        // std::cout << "sym: " << sym->value._ival << std::endl;
        return sym;
    }
	
}