#include "../headers/assignmentlist.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    AssignmentList::~AssignmentList()
    {
        
    }

    Symbol* AssignmentList::codeGen(CodeGenContext& context)
    {
		if (expr == nullptr || expr_assig == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 31, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}

        Symbol* sym_expr = expr->codeGen(context);
        Symbol* sym_assig = expr_assig->codeGen(context);

        if (sym_expr->down != nullptr)
        {
            Symbol* aux = sym_expr;
            aux = aux->down;
            Symbol* tmp = nullptr;
            while (aux != nullptr)
            {
                tmp = aux;
                aux = aux->prox;
                delete tmp;
            }
            sym_expr->down = nullptr;
        }
        
        sym_expr->type = sym_assig->type;
        sym_expr->value = sym_assig->value;
        
        if (sym_expr->type == Type::LIST)
            sym_expr->down = sym_assig;

        return sym_expr;
    }
}