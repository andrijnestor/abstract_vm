/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:23:32 by anestor           #+#    #+#             */
/*   Updated: 2018/06/04 20:08:48 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void)
{
	this->_mapType();
}

Parser::~Parser(void) {}

Parser::Parser(Parser const & src)
{
	*this = src;
}

Parser				&Parser::operator=(Parser const & src)
{
	if (this != &src)
	{
		///
	}
	return (*this);
}

void				Parser::_mapType(void)
{
	typedef std::pair<std::string, eOperandType> mp;

	_type.insert(mp("int8", Int8));
	_type.insert(mp("int16", Int16));
	_type.insert(mp("int32", Int32));
	_type.insert(mp("float", Float));
	_type.insert(mp("double", Double));
}

bool				Parser::parseErrors(Tokens const & data)
{
	bool	clean = true;

	try
	{
		this->_lexicalError(data.lexical);
	}
	catch (VmExceptions::LexicalError &e)
	{
		clean = false;
		std::cout << "Line " << data.line << ": " <<  e.what() << std::endl;
	}
	try
	{
		this->_typeName(data.type);
	}
	catch (VmExceptions::WrongTypeName &e)
	{
		clean = false;
		std::cout << "Line " << data.line << ": Syntax error: " <<  e.what() << std::endl;
	}
	try
	{
		this->_instName(data.inst);
	}
	catch (VmExceptions::UnknownInstruction &e)
	{
		clean = false;
		if (data.inst != "Null")
			std::cout << "Line " << data.line << ": Syntax error: " <<  e.what() << std::endl;
	}
	try
	{
		this->_validValue(data.value, data.type);
	}
	catch (VmExceptions::WrongValueType &e)
	{
		clean = false;
		std::cout << "Line " << data.line << ": Syntax error: " <<  e.what() << std::endl;
	}

	return (clean);
}

IOperand const *	Parser::returnOperand(Tokens const & data)
{
	try
	{
		if (data.inst == "push" || data.inst == "assert")
			return (this->_creator.createOperand(this->_type.at(data.type), data.value));
		else
			return (nullptr);
	}
	catch (VmExceptions::Owerflow &e)
	{
		throw VmExceptions::Owerflow();
	}
	catch (VmExceptions::Underflow &e)
	{
		throw VmExceptions::Underflow();
	}
	catch (std::exception &e)
	{
		throw VmExceptions();
	}
}

void				Parser::_lexicalError(bool lexical)
{
	if (lexical == true)
		throw (VmExceptions::LexicalError());
}

void				Parser::_syntacticError(void)
{
	throw VmExceptions::SyntacticError();
}

void				Parser::_typeName(std::string const & type)
{
	try
	{
		if (type != "Null")
			this->_type.at(type);
	}
	catch (std::exception &e)
	{
		throw (VmExceptions::WrongTypeName());
	}
}

void				Parser::_instName(std::string const & inst)
{
	std::regex	basic(R"(^(pop|dump|add|sub|mul|div|mod|print|exit|push|assert)$)");
	if (!std::regex_match(inst, basic))
		throw (VmExceptions::UnknownInstruction());
}

void				Parser::_validValue(std::string const & value, std::string const & type)
{
	if (std::regex_match(type, std::regex(R"(^(int8|int16|int32)$)")))
		if (!std::regex_match(value, std::regex(R"(^-*\d+$)")))
			throw (VmExceptions::WrongValueType());
	if (std::regex_match(type, std::regex(R"(^(float|double)$)")))
		if (!std::regex_match(value, std::regex(R"(^-*\d+.\d+$)")))
			throw (VmExceptions::WrongValueType());
}
