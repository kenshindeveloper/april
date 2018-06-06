#include "../headers/break.hpp"
#include "../headers/codegencontext.hpp"
#include "../headers/integer.hpp"

namespace april
{
    Symbol* Break::codeGen(CodeGenContext& context)
    {

        Integer* i = new Integer{1};
        Symbol* result = i->codeGen(context);
        context.stopBreakBlock();
        return result;
    }
}