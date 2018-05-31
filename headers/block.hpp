#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <vector>
#include <stack>

#include "expression.hpp"
#include "statement.hpp"

namespace april
{
    enum class BlockScope
    {
        FOR,
        FUNCTION,
        IF,
        UNDEFINED
    };

    class Block: public Expression
    {
		private:			
			std::stack<Block*> stack_tmp_block;
        
		public:
            std::vector<Statement*> statements;
            std::vector<Symbol*> locals;
            Block* prev;
            bool stop;
            BlockScope type_scope;
            int cont_tmp;

        public:
            Block():prev(nullptr), stop(false), type_scope(BlockScope::UNDEFINED), cont_tmp(0) {}
            ~Block();
            virtual Symbol* codeGen(CodeGenContext&);
			Block* clone();
    };
}

#endif //BLOCK_HPP