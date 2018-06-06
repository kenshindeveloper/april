#include "../headers/booleancmp.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/symbol.hpp"
#include "../headers/identifier.hpp"
#include "../parser.h"

extern april::STRUCINFO* april_errors;

namespace april
{

    Symbol* BooleanCmp::codeGen(CodeGenContext& context)
    {
        Symbol* sym_left = left->codeGen(context);
        Symbol* sym_right = right->codeGen(context);

        Symbol* tmp = new Symbol{};
        tmp->type = Type::BOOLEAN;

        if (sym_left->type == Type::UNDEFINED || sym_right->type == Type::UNDEFINED)
        {
			if (context.getError() == 0)
				return Error::call(context, 32, april_errors->file_name, april_errors->line, "");
			else
	            return nullptr;
        }

        switch (ope)
        {
            // !=
            case TCOMNE:
                tmp->value._bval = *sym_left != *sym_right;
                break;
        
            // ==
            case TCOMEQ:
                tmp->value._bval = *sym_left == *sym_right;
                break;
            
            // <=
            case TCOMLE:
                tmp->value._bval = *sym_left <= *sym_right;
                break;
            
             // >=
            case TCOMGE:
                tmp->value._bval = *sym_left >= *sym_right;
                break;
            
            // <
            case TCOMLT:
                tmp->value._bval = *sym_left < *sym_right;
                break;
            
            // >
            case TCOMGT:
                tmp->value._bval = *sym_left > *sym_right;
                break;
        }

        return tmp;
    }
}