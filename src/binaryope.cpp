#include "../headers/binaryope.hpp"
#include "../headers/codegencontext.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
    Symbol* BinaryOpe::codeGen(CodeGenContext& context)
    {
        Symbol* value_left = left->codeGen(context);
		if (value_left == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}
        
        Symbol* tmp = new Symbol{};
		
		if (ope == OPE::AND && value_left->type == Type::BOOLEAN && !value_left->value._bval)
		{
			tmp->type = Type::BOOLEAN;
			tmp->value._bval = false;
			tmp->is_constant = true;
			tmp->is_variable = false;
			tmp->name = "%_" + std::to_string(context.getCurrentBlock()->cont_tmp);
			context.getCurrentBlock()->cont_tmp += 1;
			context.getCurrentBlock()->locals.push_back(tmp);

			return tmp;
		}

		Symbol* value_right = right->codeGen(context);
		if (value_right == nullptr)
		{
			if (context.getError() == 0)
				return Error::call(context, 6, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
		}


        if ((Type::STRING == value_left->type) && (Type::STRING == value_right->type) && (ope != OPE::PLUS))
        {
			if (context.getError() == 0)
				return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }
        else if((Type::STRING != value_left->type && Type::STRING == value_right->type) || (Type::STRING == value_left->type && Type::STRING != value_right->type) )
        {
			if (context.getError() == 0)
				return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
			else
				return nullptr;
        }
       
        switch (ope)
        {
            case OPE::PLUS:
                tmp = *value_left + *value_right;
                break;
            
            case OPE::MIN:
                tmp = *value_left - *value_right;
                break;
            
            case OPE::MUL:
                tmp = *value_left * *value_right;
                break;
            
            case OPE::DIV:
                if ((value_right->type == Type::INTEGER && value_right->value._ival == 0) || (value_right->type == Type::DOUBLE && value_right->value._dval == 0))
                {
					if (context.getError() == 0)
						return Error::call(context, 43, april_errors->file_name, april_errors->line, "");
					else
						return nullptr;
                }
                tmp = *value_left / *value_right;
                break;
            
            case OPE::MOD:
                if (value_left->type != Type::INTEGER || value_right->type != Type::INTEGER || value_right->value._ival == 0)
                {
                    if (context.getError() == 0)
						return Error::call(context, 42, april_errors->file_name, april_errors->line, "");
					else
	                    return nullptr;
                }
                tmp = *value_left % *value_right;
                break;
            
            case OPE::AND:
				if (value_left->type != Type::BOOLEAN || value_right->type != Type::BOOLEAN)
				{
					if (context.getError() == 0)
						return Error::call(context, 62, april_errors->file_name, april_errors->line, "");
					else
						return nullptr;
				}
				
                tmp->value._bval = *value_left && *value_right;
                tmp->type = Type::BOOLEAN;
                break;
            
            case OPE::OR:
				if (value_left->type != Type::BOOLEAN || value_right->type != Type::BOOLEAN)
				{
					if (context.getError() == 0)
						return Error::call(context, 62, april_errors->file_name, april_errors->line, "");
					else
						return nullptr;
				}
                tmp->value._bval = *value_left || *value_right;
                tmp->type = Type::BOOLEAN;
                break;
        }
        
        tmp->name = "%_"+std::to_string(context.getCurrentBlock()->cont_tmp);
        context.getCurrentBlock()->cont_tmp += 1;
        context.getCurrentBlock()->locals.push_back(tmp);

        return tmp;
    }
}