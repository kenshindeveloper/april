#include "../headers/methodhandlestring.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;


namespace april
{
    MethodHandleString::~MethodHandleString()
    {

    }

    Symbol* MethodHandleString::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = nullptr;
        if (ident_method->getName() == "size")
        {
            if (args->size() == 0)
                tmp = string::size(sym_expr);
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