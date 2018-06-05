/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:23:32 by anestor           #+#    #+#             */
/*   Updated: 2018/06/06 00:06:39 by anestor          ###   ########.fr       */
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
		this->_type = src._type;
		this->_creator = src._creator;
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
		std::cout	<< "Line " << data.line << ": Syntax error: " << e.what()
					<< _typePredictor(data.type) << std::endl;
	}
	try
	{
		this->_instName(data.inst);
	}
	catch (VmExceptions::UnknownInstruction &e)
	{
		clean = false;
		if (data.inst != "Null")
			std::cout	<< "Line " << data.line << ": Syntax error: " << e.what()
						<< std::endl;
	}
	try
	{
		this->_validValue(data.value, data.type);
	}
	catch (VmExceptions::WrongValueType &e)
	{
		clean = false;
		std::cout	<< "Line " << data.line << ": Syntax error: " << e.what()
					<< _valueExceptor(data.value, data.type) << std::endl;
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
	std::regex	basic(R"(^(pop|dump|add|sub|mul|div|mod|print|exit|push|assert|max|min|pow|avg)$)");
	if (!std::regex_match(inst, basic))
		throw (VmExceptions::UnknownInstruction());
}

std::string			Parser::_typePredictor(std::string const & type)
{
	if (std::regex_match(type, std::regex(R"(^.*8.*$)")))
		return ("; did you mean '\033[96mint8\033[0m'?");
	else if (std::regex_match(type, std::regex(R"(^.*(1|6).*$)")))
		return ("; did you mean '\033[96mint16\033[0m'?");
	else if (std::regex_match(type, std::regex(R"(^.*(3|2).*$)")))
		return ("; did you mean '\033[96mint32\033[0m'?");
	else if (std::regex_match(type, std::regex(R"(^.*(f|l|a).*$)")))
		return ("; did you mean '\033[96mfloat\033[0m'?");
	else if (std::regex_match(type, std::regex(R"(^.*(d|u|b|e).*$)")))
		return ("; did you mean '\033[96mdouble\033[0m'?");
	else
		return ("");
}

std::string			Parser::_valueExceptor(std::string const & value, std::string const & type)
{
	std::string		ret("; undesirable symbols: \033[96m");
	bool			gotIt = false;

	if (std::regex_match(type, std::regex(R"(^(.*8|.*6|.*2)$)")))
	{
		for (size_t i = 0; i != value.size(); i++)
			if (!std::regex_match(value.substr(i, 1), std::regex(R"((-|\d))")))
			{
				gotIt = true;
				ret += value[i];
				ret += " ";
			}
		ret += "\033[0m";
		if (gotIt == true)
			return (ret);
	}
	else if (std::regex_match(type, std::regex(R"(^(f.*|d.*)$)")))
	{
		for (size_t i = 0; i != value.size(); i++)
			if (!std::regex_match(value.substr(i, 1), std::regex(R"((-|\d|\.))")))
			{
				gotIt = true;
				ret += value.substr(i, 1);
				ret += " ";
			}
		ret += "\033[0m";
		if (gotIt == true)
			return (ret);
	}
	return ("");
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
