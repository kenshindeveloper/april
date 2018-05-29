#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <vector>
#include <fstream>

namespace april
{
    enum class Type
    {
        UNDEFINED,
        INTEGER,
        DOUBLE,
        BOOLEAN,
        STRING,
        LIST,
        LIST_DOWN,
        FILE
    };

    union Value
    { 
        std::string* _sval;  
        long long _ival;
        double _dval;
        bool _bval;
        std::fstream* _file;
    };

    class Symbol
    {
        public: //why public? XD
            std::string name;
            Type type;
            Value value;
            bool is_constant;
            bool is_variable;
            bool in_list;
            Symbol* prox;
            Symbol* down;

        public:
            Symbol();
            bool operator!= (const Symbol&) const;
            bool operator== (const Symbol&) const;
            bool operator<= (const Symbol&) const;
            bool operator>= (const Symbol&) const;
            bool operator< (const Symbol&) const;
            bool operator> (const Symbol&) const;
            Symbol* operator+ (Symbol&);
            Symbol* operator- (const Symbol&);
            Symbol* operator* (const Symbol&);
            Symbol* operator/ (const Symbol&);
            Symbol* operator% (const Symbol&);
            void operator= (const Symbol&);
            bool operator&& (const Symbol&);
            bool operator|| (const Symbol&);

            std::string getType();
            friend std::ostream& operator<< (std::ostream& out, const Symbol& sym);
    };
}

#endif //SYMBOL_HPP