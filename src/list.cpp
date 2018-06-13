#include "../headers/list.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    List::~List()
    {
        for (Expression* expr : *expressions)
        {
            delete expr;
            expr = nullptr;
        }
    }

    Symbol* List::codeGen(CodeGenContext& context)
    {
        Symbol* root = new Symbol{};
		root->name = "%_tmp_%";
        root->in_list = true;
        root->type = Type::LIST;
        Symbol* aux = root;

        for (Expression* expr : *expressions)
        {
            Symbol* tmp = expr->codeGen(context);
            if (tmp->type == Type::LIST)
            {
                aux->prox = new Symbol{};
                aux = aux->prox;
                aux->type = Type::LIST_DOWN;
                aux->down = tmp;
            }
            else if (tmp->type != Type::DOUBLE && tmp->type != Type::INTEGER && tmp->type != Type::STRING)
            {
				if (context.getError() == 0)
					return Error::call(context, 23, april_errors->file_name, april_errors->line, "");
				else
					return nullptr;
            }
			else 
			{
				Symbol* _new = new Symbol{};
				_new->name = "%_tmp_%";
				_new->type = tmp->type;
				_new->value = tmp->value;
				_new->is_constant = true;
				_new->is_variable = false;
				_new->in_list = true;
				aux->prox = _new;
				aux = aux->prox;
			}
        }

        return root;
    }
}