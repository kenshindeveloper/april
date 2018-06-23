#ifndef ELIF_HPP
#define ELIF_HPP

#include "statement.hpp"
#include "block.hpp"

namespace april 
{
	class ElIf : public Statement
	{
	private:
		Expression * expr;
		Block* _then;
		StatementList* stmt_list;
		Block* _else;

	public:
		ElIf(Expression* expr, Block* _then) : expr(expr), _then(_then), stmt_list(nullptr), _else(nullptr) {}
		ElIf(Expression* expr, Block* _then, StatementList* stmt_list) : expr(expr), _then(_then), stmt_list(stmt_list), _else(nullptr) {}
		ElIf(Expression* expr, Block* _then, StatementList* stmt_list, Block* _else): expr(expr), _then(_then), stmt_list(stmt_list), _else(_else) {}
		~ElIf();
		Symbol* codeGen(CodeGenContext&);

	private:
		Symbol* exprBlock(CodeGenContext&);

	};
}

#endif //ELIF_HPP
