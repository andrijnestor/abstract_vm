/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VmExceptions.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:24:20 by anestor           #+#    #+#             */
/*   Updated: 2018/06/06 00:15:00 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VmExceptions.hpp"
#include <iostream>

VmExceptions::~VmExceptions(void) throw() {}

const char*		VmExceptions::what(void) const throw()
{
	return ("\033[91mAVM error\033[0m");
}

VmExceptions::Owerflow::~Owerflow(void) throw() {}

const char*		VmExceptions::Owerflow::what(void) const throw()
{
	return ("\033[91mOwerflow on a value\033[0m");
}

VmExceptions::Underflow::~Underflow(void) throw() {}

const char*		VmExceptions::Underflow::what(void) const throw()
{
	return ("\033[91mUnderflow on a value\033[0m");
}

VmExceptions::DivZero::~DivZero(void) throw() {}

const char*		VmExceptions::DivZero::what(void) const throw()
{
	return ("\033[91mDivision by zero\033[0m");
}

VmExceptions::ModZero::~ModZero(void) throw() {}

const char*		VmExceptions::ModZero::what(void) const throw()
{
	return ("\033[91mModulo by zero\033[0m");
}

VmExceptions::UnknownInstruction::~UnknownInstruction(void) throw() {}

const char*		VmExceptions::UnknownInstruction::what(void) const throw()
{
	return ("\033[91mUnknown instruction\033[0m");
}

VmExceptions::LexicalError::~LexicalError(void) throw() {}

const char*		VmExceptions::LexicalError::what(void) const throw()
{
	return ("\033[91mLexical error\033[0m");
}

VmExceptions::SyntacticError::~SyntacticError(void) throw() {}

const char*		VmExceptions::SyntacticError::what(void) const throw()
{
	return ("\033[91mSyntactic error\033[0m");
}

VmExceptions::EmptyStack::~EmptyStack(void) throw() {}

const char*		VmExceptions::EmptyStack::what(void) const throw()
{
	return ("\033[91mPop on an empty stack\033[0m");
}

VmExceptions::PrintEmptyStack::~PrintEmptyStack(void) throw() {}

const char*		VmExceptions::PrintEmptyStack::what(void) const throw()
{
	return ("\033[91mPrint on an empty stack\033[0m");
}

VmExceptions::NoExitFault::~NoExitFault(void) throw() {}

const char*		VmExceptions::NoExitFault::what(void) const throw()
{
	return ("\033[91mThe program doesn’t have an exit instruction\033[0m");
}

VmExceptions::ExitFault::~ExitFault(void) throw() {}

const char*		VmExceptions::ExitFault::what(void) const throw()
{
	return ("\033[91mInstruction after exit\033[0m");
}

VmExceptions::AssertFault::~AssertFault(void) throw() {}

const char*		VmExceptions::AssertFault::what(void) const throw()
{
	return ("\033[91mAn assert instruction is not true\033[0m");
}

VmExceptions::StackLessTwo::~StackLessTwo(void) throw() {}

const char*		VmExceptions::StackLessTwo::what(void) const throw()
{
	return ("\033[91mThe stack is composed of strictly less that two values when an arithmetic instruction is executed\033[0m");
}

VmExceptions::WrongTypeName::~WrongTypeName(void) throw() {}

const char*		VmExceptions::WrongTypeName::what(void) const throw()
{
	return ("\033[91mWrong type name\033[0m");
}

VmExceptions::WrongValueType::~WrongValueType(void) throw() {}

const char*		VmExceptions::WrongValueType::what(void) const throw()
{
	return ("\033[91mWrong value type\033[0m");
}

VmExceptions::WrongFile::~WrongFile(void) throw() {}

const char*		VmExceptions::WrongFile::what(void) const throw()
{
	std::string ret("\033[91m");
	ret += std::strerror(errno);
	ret += "\033[0";
	return (ret.c_str());
}
