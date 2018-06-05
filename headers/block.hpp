#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#include "expression.hpp"
#include "statement.hpp"

namespace april
{
	class Function;
	using CallFunctionList = std::map<std::string, Function*>;

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
			CallFunctionList functions;

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
			Function* getFunctions(std::string&);
			CallFunctionList& getFunctions() { return functions; }
			void addFunction(std::string name, Function* function) { functions[name] = function; }
			bool existFunction(std::string);
    };
}

#endif //BLOCK_HPP