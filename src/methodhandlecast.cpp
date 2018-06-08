#include "../headers/methodhandlecast.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    MethodHandleCast::~MethodHandleCast()
    {

    }

    Symbol* MethodHandleCast::codeGen(CodeGenContext& context)
    {
        Expression* expr_arg = nullptr;
        if (args->size() == 1)
            expr_arg = args->back();
        else
        {
			if (context.getError() == 0)
				return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
			else
				return nullptr;
        }

        Symbol* sym_arg = expr_arg->codeGen(context);
        
        if (sym_arg == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, ident_method->getName());
			else
				return nullptr;
        }
        
        if (sym_arg->type == Type::BOOLEAN || sym_arg->type == Type::LIST || sym_arg->type == Type::LIST_DOWN || sym_arg->type == Type::UNDEFINED)
        {
			if (context.getError() == 0)
				return Error::call(context, 133, april_errors->file_name, april_errors->line, ident_method->getName());
			else
				return nullptr;
        }

        if (ident_method->getName() != "str" && (sym_arg->type == Type::STRING  &&  !(string::isNumber(sym_arg))))
        {
			if (context.getError() == 0)
				return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        Symbol* tmp = nullptr;
        if (ident_method->getName() == "double")
        {
			if (sym_arg->type == Type::DOUBLE || sym_arg->type == Type::INTEGER)
				tmp = cast::toDouble(sym_arg);
			else
			{
				if (context.getError() == 0)
					return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
				else
					return nullptr;
			}
        } 
        else if (ident_method->getName() == "str")
        {
			if (sym_arg->type == Type::DOUBLE || sym_arg->type == Type::INTEGER || sym_arg->type == Type::STRING)
				tmp = cast::toString(sym_arg);
			else
			{
				if (context.getError() == 0)
					return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
				else
					return nullptr;
			}
        }
        else if (ident_method->getName() == "int")
        {
            if (sym_arg->type == Type::DOUBLE || sym_arg->type == Type::INTEGER)
                tmp = cast::toInt(sym_arg);
            else    
            {
				if (context.getError() == 0)
					return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
				else
					return nullptr;
            }
        } 
        else
        {
			if (context.getError() == 0)
				return Error::call(context, 134, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        return tmp;
    }
}