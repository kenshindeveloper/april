#ifndef FOR_DECL_HPP
#define FOR_DECL_HPP

#include "statement.hpp"
#include "block.hpp"

namespace april
{
	class ForDecl: public Statement 
	{
		private:
			Statement * declaration;
			Expression* condition;
			Expression* increment;
			Block*	block;

		public:
			ForDecl(Statement* declaration, Expression* condition, Expression* increment, Block* block)
			: declaration(declaration), condition(condition), increment(increment), block(block) { }
			~ForDecl();
			virtual Symbol* codeGen(CodeGenContext&);
	};
}

#endif //FOR_DECL_HPP