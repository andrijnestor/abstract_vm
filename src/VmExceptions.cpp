/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VmExceptions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:24:20 by anestor           #+#    #+#             */
/*   Updated: 2018/05/30 18:31:39 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VmExceptions.hpp"

VmExceptions::~VmExceptions(void) throw() {}

const char*		VmExceptions::what(void) const throw()
{
	return ("AVM error");
}

VmExceptions::Owerflow::~Owerflow(void) throw() {}

const char*		VmExceptions::Owerflow::what(void) const throw()
{
	return ("Owerflow on a value");
}

VmExceptions::Underflow::~Underflow(void) throw() {}

const char*		VmExceptions::Underflow::what(void) const throw()
{
	return ("Underflow on a value");
}

VmExceptions::DivZero::~DivZero(void) throw() {}

const char*		VmExceptions::DivZero::what(void) const throw()
{
	return ("Division by zero");
}

VmExceptions::ModZero::~ModZero(void) throw() {}

const char*		VmExceptions::ModZero::what(void) const throw()
{
	return ("Modulo by zero");
}

VmExceptions::UnknownInstruction::~UnknownInstruction(void) throw() {}

const char*		VmExceptions::UnknownInstruction::what(void) const throw()
{
	return ("Unknown instruction");
}

VmExceptions::LexicalError::~LexicalError(void) throw() {}

const char*		VmExceptions::LexicalError::what(void) const throw()
{
	return ("Lexical error");
}

VmExceptions::SyntacticError::~SyntacticError(void) throw() {}

const char*		VmExceptions::SyntacticError::what(void) const throw()
{
	return ("Syntactic error");
}

VmExceptions::EmptyStack::~EmptyStack(void) throw() {}

const char*		VmExceptions::EmptyStack::what(void) const throw()
{
	return ("Pop on an empty stack");
}

VmExceptions::ExitFault::~ExitFault(void) throw() {}

const char*		VmExceptions::ExitFault::what(void) const throw()
{
	return ("The program doesn’t have an exit instruction");
}

VmExceptions::AssertFault::~AssertFault(void) throw() {}

const char*		VmExceptions::AssertFault::what(void) const throw()
{
	return ("An assert instruction is not true");
}

VmExceptions::StackLessTwo::~StackLessTwo(void) throw() {}

const char*		VmExceptions::StackLessTwo::what(void) const throw()
{
	return ("The stack is composed of strictly less that \
			two values when an arithmetic instruction is executed");
}

VmExceptions::WrongValueType::~WrongValueType(void) throw() {}

const char*		VmExceptions::WrongValueType::what(void) const throw()
{
	return ("Wrong value type");
}
