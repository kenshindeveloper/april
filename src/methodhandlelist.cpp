#include "../headers/methodhandlelist.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    MethodHandleList::~MethodHandleList()
    {
        //falta limpieza de punteros... :(
    }

    Symbol* MethodHandleList::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = nullptr;
        if (ident_method->getName() == "size")
        {
            if (args->size() == 0)
                tmp = list::size(sym_expr);
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        }        
        else if (ident_method->getName() == "append")
        {
            if (args->size() == 1)
            {
                Symbol* sym = (*args)[0]->codeGen(context);
                tmp = list::append(sym_expr, sym);
            }
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        } 
        else if (ident_method->getName() == "index")
        {
            if (args->size() == 1)
            {
                Symbol* sym = (*args)[0]->codeGen(context);
                tmp = list::index(sym_expr, sym);
            }
            else
            {
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
            }
        }
        else if (ident_method->getName() == "remove")
        {
            if (args->size() == 1)
            {
                Symbol* sym = (*args)[0]->codeGen(context);
                if (sym->type != Type::INTEGER)
                {
					if (context.getError() == 0)
						return Error::call(context, 7, april_errors->file_name, april_errors->line, ident_method->getName());
					else
						return nullptr;
                }

                Symbol* size = list::size(sym_expr);
                if (sym->value._ival >= size->value._ival || sym->value._ival < 0)
                {
                    delete size;
					if (context.getError() == 0)
						return Error::call(context, 72, april_errors->file_name, april_errors->line, ident_method->getName());
					else
						return nullptr;
                }

                delete size;
                tmp = list::remove(sym_expr, sym);
            }
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