#include "../headers/boolean.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* Boolean::codeGen(CodeGenContext& context)
    {
        if (name != "false" && name != "true")
        {
			if (context.getError() == 0)
				return Error::call(context, 61, april_errors->file_name, april_errors->line, "'"+name+"'");
			else
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