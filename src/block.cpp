#include "../headers/block.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/funclist.hpp"

namespace april
{
    Block::~Block()
    {
        for (Statement* stmt: statements)
        {
            if (stmt != nullptr)
            {
                delete stmt;
                stmt = nullptr;
            }
        }
        statements.clear();

		for (Symbol* sym : locals)
        {
			Symbol* aux = sym;
			while (aux != nullptr)
			{
				Symbol* tmp = aux;
				aux = aux->prox;
				delete tmp;
				tmp = nullptr;
			}
        }
        locals.clear();

		while (stack_tmp_block.size() > 0)
		{
			Block* b = stack_tmp_block.top();
			b->statements.clear();

			delete b;
			stack_tmp_block.pop();
		}
    }

    Symbol* Block::codeGen(CodeGenContext& context)
    {
        // std::cout << ">> ini block <<" << std::endl;
        Symbol* last = new Symbol{};
        
        for (Statement*& stmt: statements)
        {
            if (!stop)
            {
                last = stmt->codeGen(context);
                if (last == nullptr) return nullptr;
            }
            else
                break;
        }

        
        if (type_scope != BlockScope::FOR)
            stop = false;
            
        return last;
    }

	Block* Block::clone()
	{
		Block* new_block = new Block{};
		new_block->statements = statements;
		new_block->type_scope = type_scope;
		new_block->functions = functions;

		for (Symbol* sym : locals)
			new_block->locals.push_back(list::clone(sym));

		stack_tmp_block.push(new_block);
		return new_block;
	}

	bool Block::existFunction(std::string name)
	{
		Block* aux = this;

		while (aux != nullptr)
		{
			if (aux->functions.find(name) != aux->functions.end())
				return true;
			aux = aux->prev;
		}

		return false;
	}

	Function* Block::getFunctions(std::string& name)
	{
		Block* aux = this;

		while (aux != nullptr)
		{
			if (aux->functions.find(name) != aux->functions.end())
				return aux->functions[name];
			
			aux = aux->prev;
		}

		return nullptr;
	}
}