#include "../headers/methodhandlefile.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    MethodHandleFile::~MethodHandleFile()
    {
        //falta limpieza de punteros... :(
    }

    Symbol* MethodHandleFile::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = nullptr;

        if (ident_method->getName() == "close")
        {
            if (args->size() == 0)
                tmp = file::close(sym_expr);
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        }
        else if (ident_method->getName() == "is_open")
        {
            if (args->size() == 0)
                tmp = file::is_open(sym_expr);
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        }
        else if (ident_method->getName() == "write")
        {
            if (args->size() == 1)
            {
                Symbol* str = (*args)[0]->codeGen(context);
                if (str->type != Type::STRING)
                {
					if (context.getError() == 0)
						return Error::call(context, 133, april_errors->file_name, april_errors->line, ident_method->getName());
					else
						return nullptr;
                }
                tmp = file::write(sym_expr, *str->value._sval);
            }
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        }
        else if (ident_method->getName() == "readline")
        {
            if (args->size() == 0)
                tmp = file::readline(sym_expr);
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }

			
        }
        else if (ident_method->getName() == "is_eof")
        {
            if (args->size() == 0)
                tmp = file::is_eof(sym_expr);
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        }
        else
        {
			if (context.getError() == 0)
				return Error::call(context, 134, april_errors->file_name, april_errors->line, ident_method->getName());
			else
				return nullptr;
        }

        return tmp;
    }
}