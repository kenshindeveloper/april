#include "../headers/stringarray.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    Symbol* StringArray::codeGen(CodeGenContext& context)
    {

        Symbol* sym_ident = context.existIdenLocals(ident_var->getName());
        if (sym_ident == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }
        if (sym_ident->type != Type::STRING)
        {
			if (context.getError() == 0)
				return Error::call(context, 63, april_errors->file_name, april_errors->line, sym_ident->name);
			else
				return nullptr;
        }

        Symbol* sym_indice =  expr_indice->codeGen(context);
        if (sym_indice->type != Type::INTEGER)
        {
			if (context.getError() == 0)
				return Error::call(context, 64, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        if (sym_indice->value._ival > (sym_ident->value._sval)->length())
        {
			if (context.getError() == 0)
				return Error::call(context, 72, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }

        std::string arr = *(sym_ident->value._sval);
        arr = arr[sym_indice->value._ival];

        Symbol* tmp = new Symbol();
        tmp->name = "";
        tmp->type = Type::STRING;
        tmp->value._sval = new std::string(arr);
        tmp->is_constant = true;
        tmp->is_variable = false;

        return tmp;
    };
}