#include "../headers/error.hpp"
#include "../headers/msg.hpp"

namespace april
{

	Symbol* Error::call(CodeGenContext& context, int errorNumber, std::string file, int line, std::string name)
	{
		Node::printError(" ");
		Node::printError(Msg::Mtitle);
		Node::printError(Msg::Mcode + std::to_string(errorNumber));
		Node::printError(Msg::Mfile + file);
		Node::printError(Msg::Mline + std::to_string(line));

		if (name != "")
		{
			name = " '" + name + "' ";
		}

		std::string msg = Msg::Mmessage;

		switch (errorNumber)
		{
			// [1-10] node -> statemente -> vardeclaration
		case(1): msg += Msg::M001 + name; break;
		case(2): msg += Msg::M002 + name; break;
		case(3): msg += Msg::M003 + name; break;
		case(4): msg += Msg::M004; break;
		case(5): msg += Msg::M005; break;
		case(6): msg += Msg::M006; break;
		case(7): msg += Msg::M007; break;
		case(8): msg += Msg::M008; break;
		case(9): msg += Msg::M009; break;

			// [11-20] node -> statemente -> vardeclarationdeduce
		case(11): msg += Msg::M011 + name; break;
		case(12): msg += Msg::M012 + name; break;
		case(13): msg += Msg::M013 + name; break;

			// [21-30] node -> expression -> Assignment
		case(21): msg += Msg::M021 + name; break;
		case(22): msg += Msg::M022; break;
		case(23): msg += Msg::M023; break;

			// [31-40] node -> expression -> AssigBioperator
		case(31): msg += Msg::M031; break;
		case(32): msg += Msg::M032 + name; break;
		case(33): msg += Msg::M033; break;
		case(34): msg += Msg::M034; break;

			// [41-50] node -> expression -> BinaryOperator
		case(41): msg += Msg::M041; break;
		case(42): msg += Msg::M042 + name; break;
		case(43): msg += Msg::M043 + name; break;

			// [51-60] node -> expression -> Block

			// [61-70] node -> expression -> Boolean
		case(61): msg += Msg::M061; break;
		case(62): msg += Msg::M062; break;
		case(63): msg += Msg::M063; break;
		case(64): msg += Msg::M064; break;
			// [71-80] node -> expression -> ListAccess
		case(71): msg += Msg::M071; break;
		case(72): msg += Msg::M072; break;

			// [81-90] node -> expression -> ComparasionOpe
		case(81): msg += Msg::M081; break;
		case(82): msg += Msg::M082; break;

			// [91-100] node -> expression -> Conditional
		case(91): msg += Msg::M091; break;

			// [101-110] node -> expression -> Double

			// [111-120] node -> expression -> ExpressionStatement

			// [121-130] node -> expression -> ForLoop
		case(121): msg += Msg::M121; break;
		case(122): msg += Msg::M122; break;
		case(123): msg += Msg::M123; break;
		case(124): msg += Msg::M124; break;

			// [131-140] node -> expression -> Function
		case(131): msg += Msg::M131 + name; break;
		case(132): msg += Msg::M132 + name; break;
		case(133): msg += Msg::M133; break;
		case(134): msg += Msg::M134 + name; break;

			// [141-150] node -> expression -> Identifier
		case(141): msg += Msg::M141 + name; break;

			// [151-160] node -> expression -> Integer

			// [161-170] node -> expression -> LogicOpe
		case(161): msg += Msg::M161; break;
		case(162): msg += Msg::M162; break;

			// [171-180] node -> expression -> MethodCall
		case(171): msg += Msg::M171 + name; break;
		case(172): msg += Msg::M172 + name; break;
		case(173): msg += Msg::M173 + name; break;
		case(174): msg += Msg::M174 + name; break;

			// [181-190] node -> expression -> nativefn

			// [191-200] node -> expression -> Return
		case(191): msg += Msg::M191; break;

			// [201-210] node -> expression -> Scope

			// [211-220] node -> expression -> String

			// [221-230] node -> expression -> UnaryOpe
		case(221): msg += Msg::M221; break;

			//  default - errors
		default: msg += Msg::M000; break;
		}
		Node::printError(msg);
		Node::printError(" ");
		context.addError();
		return nullptr;
	}
}