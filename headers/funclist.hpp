#ifndef FUNC_LIST_HPP
#define FUNC_LIST_HPP

#include <map>
#include "symbol.hpp"
#include "node.hpp"

namespace april
{
    class Symbol;

    namespace list
    {
        Symbol* size(Symbol*);
        Symbol* append(Symbol*, Symbol*);
		Symbol* clone(Symbol*);
		Symbol* clone_syms(Symbol*);
        Symbol* index(Symbol*, Symbol*);
        Symbol* remove(Symbol*, Symbol*);
    }

    namespace string
    {
        Symbol* length(Symbol*);
        bool isNumber(Symbol*);
    }

    namespace cast
    {
        Symbol* toDouble(Symbol*);
        Symbol* toInt(Symbol*);
        Symbol* toString(Symbol*);
    }

    namespace io
    {
        Symbol* println(Symbol*);
        Symbol* print(Symbol*);
        Symbol* input();
    }

    namespace file
    {
        Symbol* open(std::string, std::string);
        Symbol* is_open(Symbol*);
        Symbol* write(Symbol*, std::string);
        Symbol* readline(Symbol*);
        Symbol* is_eof(Symbol*);
        Symbol* close(Symbol*);
    }

    namespace lib 
    {
        Symbol* range(Symbol*);
        Symbol* range(Symbol*, Symbol*);
    }

	namespace time
	{
		Symbol* time();
		Symbol* day();
		Symbol* month();
		Symbol* year();
	}
}

#endif //FUNC_LIST_HPP