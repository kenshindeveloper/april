#ifndef METHOD_HANDLE_TIME_HPP
#define METHOD_HANDLE_TIME_HPP

#include "expression.hpp"
#include "identifier.hpp"

namespace april
{
	class MethodHandleTime : public Expression
	{
	private:
		Symbol * sym_expr;
		Identifier* ident_method;
		ExpressionList* args;

	public:
		MethodHandleTime(Symbol* sym_expr, Identifier* ident_method, ExpressionList* args) : sym_expr(sym_expr), ident_method(ident_method), args(args) {}
		virtual ~MethodHandleTime();
		virtual Symbol* codeGen(CodeGenContext&);
	};
}

#endif //METHOD_HANDLE_TIME_HPP