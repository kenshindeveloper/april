#include "../headers/integer.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* Integer::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = new Symbol{};

        tmp->name = "%_tmp_"+std::to_string(value);
        tmp->type = Type::INTEGER;
        tmp->value._ival = value;
        tmp->is_constant = true;
        tmp->is_variable = false;

		context.getCurrentBlock()->locals.push_back(tmp);
        return tmp;
    }
}