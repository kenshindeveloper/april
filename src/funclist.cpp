#pragma warning(disable: 4996)
#include <string.h>
#include <fstream>
#include <ctime>
#include <regex>
#include "../headers/funclist.hpp"

namespace april
{
    namespace list
    {
        Symbol* size(Symbol* root)
        {
            Symbol* aux = root->prox;
            int cont = 0;
            while (aux != nullptr)
            {
                aux = aux->prox;
                cont += 1;
            }

            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->value._ival = cont;
            tmp->is_constant = true;
            tmp->is_variable = false;

            return tmp;
        }

        Symbol* append(Symbol* root, Symbol* sym)
        {
            Symbol* aux = root;

            while (aux->prox != nullptr)
                aux = aux->prox;

            aux->prox = new Symbol{};
            aux = aux->prox;
            if (sym->type != Type::LIST)
            {
                aux->name = "";
                aux->type = sym->type;
                aux->value = sym->value;
                aux->is_constant = true;
                aux->is_variable = false;
                aux->in_list = true;
            }
            else
            {
                aux->type = Type::LIST_DOWN;
                aux->in_list = true;
                Symbol* node = sym;
                aux->down = clone(node);
            }

            return root;
        }

        Symbol* clone (Symbol* node)
        {
            Symbol* result = new Symbol{};
            Symbol* itera = result;
            
            while (node != nullptr)
            {
                itera->name = "%_tmp_%";
                itera->type = node->type;
                itera->value = node->value;
                itera->is_constant = true;
                itera->is_variable = false;
                itera->in_list = true;
               
                if (node->type == Type::LIST_DOWN)
                    itera->down = clone(node->down);
                else
                    itera->value = node->value;
                
                node = node->prox;
                if (node != nullptr)
                {
                    itera->prox = new Symbol{};
                    itera = itera->prox;
                }
            }

            return result;
        }

		Symbol* clone_syms(Symbol* node)
		{
			Symbol* result = new Symbol{};
			Symbol* itera = result;

			while (node != nullptr)
			{
				itera->name = node->name;
				itera->type = node->type;
				itera->value = node->value;
				itera->is_constant = true;
				itera->is_variable = false;
				itera->in_list = true;

				if (node->type == Type::LIST_DOWN)
					itera->down = clone(node->down);
				else
					itera->value = node->value;

				node = node->prox;
				if (node != nullptr)
				{
					itera->prox = new Symbol{};
					itera = itera->prox;
				}
			}

			return result;
		}

        Symbol* index(Symbol* root, Symbol* sym)
        {
            Symbol* aux = root->prox;
            int cont = 0;
            bool exist = false;
            while ( aux != nullptr)
            {
                if ((*aux == *sym) == true)
                {
                    exist = true;
                    break;
                }
                cont += 1;
                aux = aux->prox;
            }
        
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->value._ival = (exist)?(cont):(-1);
            tmp->is_constant = true;
            tmp->is_variable = false;
            return tmp;
        }  

        Symbol* remove(Symbol* root, Symbol* sym)
        {
            Symbol* aux = root;

            for (int cont = 0; cont < sym->value._ival; cont += 1)
                    aux = aux->prox;

            Symbol* tmp = aux->prox;
            aux->prox = aux->prox->prox;
            delete tmp;
            return root;
        } 
    }

    namespace string
    {
        Symbol* size(Symbol* root)
        {
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->value._ival = root->value._sval->length();
            tmp->is_constant = true;
            tmp->is_variable = false;
            return tmp;
        }

        bool isNumber(Symbol* element)
        {
            std::regex re("[0-9]+(\\.[0-9]+)?");

            if (regex_match(*(element->value._sval), re))
                return true;

            return false;
        }  
    } 

    namespace cast 
    {
        Symbol* toDouble(Symbol* element)
        {
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::DOUBLE;
            tmp->is_constant = true;
            tmp->is_variable = false;

            if (element->type == Type::DOUBLE)
                tmp->value._dval = element->value._dval;
             
            else if (element->type == Type::INTEGER)
                tmp->value._dval = double(element->value._ival);    
            
            else if (element->type == Type::STRING)
                tmp->value._dval = double(std::atof(element->value._sval->c_str()));
            
            return tmp;
        }

        Symbol* toInt(Symbol* element)
        {
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::INTEGER;
            tmp->is_constant = true;
            tmp->is_variable = false;
             
            if (element->type == Type::INTEGER)
                tmp->value._ival = element->value._ival;
            
			else if (element->type == Type::DOUBLE)
				tmp->value._ival = int(element->value._dval);

            else if (element->type == Type::STRING)
                tmp->value._ival = int(std::atoi(element->value._sval->c_str()));

            
            return tmp;
        }

        Symbol* toString(Symbol* element)
        {
            Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::STRING;
            tmp->is_constant = true;
            tmp->is_variable = false;

            if (element->type == Type::DOUBLE)
                tmp->value._sval = new std::string(std::to_string(element->value._dval));

            else if (element->type == Type::INTEGER)
                tmp->value._sval = new std::string(std::to_string(element->value._ival));   
            
            else if (element->type == Type::STRING)
                tmp->value._sval = new std::string(element->value._sval->c_str());
            
            return tmp;
        }
    }

    namespace io
    {
        Symbol* println(Symbol* sym)
        {
            std::cout << *sym << std::endl;

            Symbol* tmp = new Symbol{};
			tmp->name = "%_tmp_true";
			tmp->type = Type::BOOLEAN;
            tmp->is_constant = true;
            tmp->is_variable = false;
            tmp->value._bval = true;
            return tmp; //por ahora debe retornar un valor...
        }
        
        Symbol* print(Symbol* sym)
        {
            std::cout << *sym ;

            Symbol* tmp = new Symbol{};
			tmp->name = "%_tmp_true";
            tmp->type = Type::BOOLEAN;
            tmp->is_constant = true;
            tmp->is_variable = false;
            tmp->value._bval = true;
            return tmp; //por ahora debe retornar un valor...
        }

        Symbol* input()
        {
            std::string _input;
            std::cout << "<< ";
            std::getline(std::cin, _input);
            
			Symbol* tmp = new Symbol{};
            tmp->name = "";
            tmp->type = Type::STRING;
            tmp->value._sval =  new std::string(_input);
            tmp->is_constant = true;
            tmp->is_variable = false;

            return tmp;
        }
    }

    namespace file
    {
        Symbol* open(std::string name, std::string type)
        {
            Symbol* root = new Symbol{};
            root->name = "%_open_%";
            root->type = Type::FILE;

            if (type == "r")
                root->value._file = new std::fstream{name.c_str(), std::ios::in };

            else if (type == "w")
                root->value._file = new std::fstream{name.c_str(), std::ios::out };

            return root;
        }

        Symbol* is_open(Symbol* root)
        {
            Symbol* tmp = new Symbol{};
			tmp->name = "%_bool_%";
			tmp->type = Type::BOOLEAN;
            tmp->is_constant = true;
            tmp->is_variable = false;

            if (root->value._file != nullptr)
                tmp->value._bval = root->value._file->is_open();
            else
                tmp->value._bval = false;

            return tmp;
        }

        Symbol* write(Symbol* root, std::string text)
        {
            if (root->value._file != nullptr)
                *root->value._file << text;
            
            return root;
        }

        Symbol* readline(Symbol* root)
        {
			std::string* text = new std::string();
            
            if (root->value._file != nullptr && !root->value._file->eof())
                std::getline(*root->value._file, *text);
            else
                *text = "";

            Symbol* tmp = new Symbol{};
            tmp->name = "%_str_%";
            tmp->type = Type::STRING;
            tmp->value._sval = text;
            tmp->is_constant = true;
            tmp->is_variable = false;
			//std::cout << "(I)text: " << *tmp << std::endl;
            return tmp;
        }

        Symbol* is_eof(Symbol* root)
        {
            Symbol* tmp = new Symbol{};
			tmp->name = "%_bool_%";
			tmp->type = Type::BOOLEAN;
            tmp->is_constant = true;
            tmp->is_variable = false;
            if (root->value._file != nullptr)
                tmp->value._bval = root->value._file->eof();
            else
                tmp->value._bval = true;
                
            return tmp;
        }

        Symbol* close(Symbol* root)
        {
            if (root->value._file != nullptr)
            {
                root->value._file->close();
                root->value._file = nullptr;
            }

            return root;
        }
    }

    namespace lib 
    {
        Symbol* range(Symbol* last)
        {
            Symbol* tmp = new Symbol{};
            tmp->type = Type::LIST;
            tmp->in_list = true;
            Symbol* aux = tmp;
            
            for (int i = 0; i < last->value._ival; i += 1)
            {
                aux->prox = new Symbol{};
                aux = aux->prox;

                aux->type = Type::INTEGER;
                aux->value._ival = i;
                aux->in_list = true;
                aux->is_variable = false;
                aux->is_constant = true;
            }

            return tmp;
        }

        Symbol* range(Symbol* first, Symbol* last)
        {
            Symbol* tmp = new Symbol{};
            tmp->type = Type::LIST;
            tmp->in_list = true;
            Symbol* aux = tmp;

            for (int i = first->value._ival; i < last->value._ival; i += 1)
            {
                aux->prox = new Symbol{};
                aux = aux->prox;

                aux->type = Type::INTEGER;
                aux->value._ival = i;
                aux->in_list = true;
                aux->is_variable = false;
                aux->is_constant = true;
            }

            return tmp;
        }
    }

	namespace time
	{
		Symbol* time()
		{
			Symbol* root = new Symbol{};
			root->name = "%_datatime_%";
			root->type = Type::DATATIME;
			root->value._ival = 1;
			
			return root;
		}

		Symbol* day()
		{
			time_t now = std::time(0);
			tm* t = localtime(&now);

			Symbol* tmp = new Symbol{};
			tmp->name = "%_int_%";
			tmp->type = Type::INTEGER;
			tmp->is_constant = true;
			tmp->is_variable = false;
			tmp->value._ival = t->tm_wday;
			
			return tmp;
		}

		Symbol* month()
		{
			time_t now = std::time(0);
			tm* t = localtime(&now);

			Symbol* tmp = new Symbol{};
			tmp->name = "%_int_%";
			tmp->type = Type::INTEGER;
			tmp->is_constant = true;
			tmp->is_variable = false;
			tmp->value._ival = t->tm_mon;

			return tmp;
		}
		
		Symbol* year()
		{
			time_t now = std::time(0);
			tm* t = localtime(&now);

			Symbol* tmp = new Symbol{};
			tmp->name = "%_int_%";
			tmp->type = Type::INTEGER;
			tmp->is_constant = true;
			tmp->is_variable = false;
			tmp->value._ival = t->tm_year;

			return tmp;
		}
	}
}