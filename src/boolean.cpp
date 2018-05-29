#include "../headers/boolean.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* Boolean::codeGen(CodeGenContext& context)
    {
        if (name != "false" && name != "true")
        {
            printError(april_errors->file_name + ":" + std::to_string(april_errors->line) + " error: el tipo de dato '"+name+"' no esta definido dentro de boolean.\n");
            context.addError();
            return nullptr;
        }

        Symbol* tmp = new Symbol{};
        tmp->name = "%_tmp_"+name;
        tmp->type = Type::BOOLEAN;
		tmp->value._bval = (name == "true") ? (true) : (false);
        tmp->is_constant = true;
        tmp->is_variable = false;

		context.getCurrentBlock()->locals.push_back(tmp);
        return tmp;       
    }
}