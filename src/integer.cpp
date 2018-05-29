#include "../headers/integer.hpp"
#include "../headers/codegencontext.hpp"

namespace april
{
    Symbol* Integer::codeGen(CodeGenContext& context)
    {
        Symbol* tmp = new Symbol{};
        tmp->name = "";
        tmp->type = Type::INTEGER;
        tmp->value._ival = value;
        tmp->is_constant = true;
        tmp->is_variable = false;
        
        return tmp;
    }
}