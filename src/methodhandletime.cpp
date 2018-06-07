#include "../headers/methodhandletime.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

extern april::STRUCINFO* april_errors;

namespace april
{
	MethodHandleTime::~MethodHandleTime()
	{
	
	}

	Symbol* MethodHandleTime::codeGen(CodeGenContext& context)
	{
		Symbol* tmp = nullptr;

		if (ident_method->getName() == "day")
		{
			if (args->size() == 0)
				tmp = time::day();
			else
			{
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
			}
		}
		else if (ident_method->getName() == "month")
		{
			if (args->size() == 0)
				tmp = time::month();
			else
			{
				if (context.getError() == 0)
					return Error::call(context, 132, april_errors->file_name, april_errors->line, ident_method->getName());
				else
					return nullptr;
			}
		}
		else if (ident_method->getName() == "year")
		{
			if (args->size() == 0)
				tmp = time::year();
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