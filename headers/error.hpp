#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include "codegencontext.hpp"

namespace april
{
	class Error
	{
		public:
			static Symbol* call(CodeGenContext& context, int errorNumber, std::string file, int line, std::string name);

		private:
			Error() {} //corregir
	};
}


#endif //ERROR_HPP