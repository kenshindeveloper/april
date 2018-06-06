#include "../headers/methodstruct.hpp"
#include "../headers/methodhandlelist.hpp"
#include "../headers/methodhandlestring.hpp"
#include "../headers/methodhandlefile.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* MethodStruct::codeGen(CodeGenContext& context)
    {   
        if (ident_var == nullptr && expr_var == nullptr)
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, ident_method->getName());
			else
				return nullptr;
        }

        if (ident_var != nullptr && !context.existIdenLocals(ident_var->getName()))
        {
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, ident_method->getName());
			else
				return nullptr;
        }

        Symbol* sym_expr = nullptr;
        if (ident_var != nullptr)
            sym_expr = context.findIdentLocals(ident_var->getName());
        else
            sym_expr = expr_var->codeGen(context);

        Symbol* tmp = nullptr;
        if (sym_expr->type == Type::LIST)
        {
            MethodHandleList* methodhandlelist = new MethodHandleList(sym_expr, ident_method, args);
            tmp = methodhandlelist->codeGen(context);
            // context.getCurrentBlock()->cont_tmp += 1;
            // context.getCurrentBlock()->locals.push_back(tmp);
            delete methodhandlelist;
            methodhandlelist = nullptr;
        }
        else if (sym_expr->type == Type::STRING)
        {
            MethodHandleString* methodhandlestring = new MethodHandleString(sym_expr, ident_method, args);
            tmp = methodhandlestring->codeGen(context);
            // context.getCurrentBlock()->cont_tmp += 1;
            // context.getCurrentBlock()->locals.push_back(tmp);
            delete methodhandlestring;
            methodhandlestring = nullptr;
        }
        else if (sym_expr->type == Type::FILE)
        {
            MethodHandleFile* methodhandlefile = new MethodHandleFile(sym_expr, ident_method, args);
            tmp = methodhandlefile->codeGen(context);
            // context.getCurrentBlock()->cont_tmp += 1;
            // context.getCurrentBlock()->locals.push_back(tmp);
            delete methodhandlefile;
            methodhandlefile = nullptr;
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