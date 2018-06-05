/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:23:32 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 22:29:51 by anestor          ###   ########.fr       */
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
			std::cout	<< "Line " << data.line << ": Syntax error: " <<  e.what()
						<< _instPredictor(data.inst) << std::endl;
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

std::string			Parser::_instPredictor(std::string const & inst)
{
	if (std::regex_match(inst, std::regex(R"(^p.*p$)")))
		return ("; did you mean 'pop'?");
	else if (std::regex_match(inst, std::regex(R"(^d.*p$)")))
		return ("; did you mean 'dump'?");
	else if (std::regex_match(inst, std::regex(R"(^a.*d$)")))
		return ("; did you mean 'add'?");
	else if (std::regex_match(inst, std::regex(R"(^s.*b$)")))
		return ("; did you mean 'sub'?");
	else if (std::regex_match(inst, std::regex(R"(^m.*l$)")))
		return ("; did you mean 'mul'?");
	else if (std::regex_match(inst, std::regex(R"(^d.*v$)")))
		return ("; did you mean 'div'?");
	else if (std::regex_match(inst, std::regex(R"(^m.*d$)")))
		return ("; did you mean 'mod'?");
	else if (std::regex_match(inst, std::regex(R"(^p.*t$)")))
		return ("; did you mean 'print'?");
	else if (std::regex_match(inst, std::regex(R"(^e.*t$)")))
		return ("; did you mean 'exit'?");
	else if (std::regex_match(inst, std::regex(R"(^m.*x$)")))
		return ("; did you mean 'max'?");
	else if (std::regex_match(inst, std::regex(R"(^m.*n$)")))
		return ("; did you mean 'min'?");
	else if (std::regex_match(inst, std::regex(R"(^a.*g$)")))
		return ("; did you mean 'avg'?");
	else if (std::regex_match(inst, std::regex(R"(^p.*w$)")))
		return ("; did you mean 'pow'?");
	else if (std::regex_match(inst, std::regex(R"(^p.*h$)")))
		return ("; did you mean 'push'?");
	else if (std::regex_match(inst, std::regex(R"(^a.*t$)")))
		return ("; did you mean 'assert'?");
	else
		return ("");
}

std::string			Parser::_typePredictor(std::string const & type)
{
	if (std::regex_match(type, std::regex(R"(^.*8$)")))
		return ("; did you mean 'int8'?");
	else if (std::regex_match(type, std::regex(R"(^.*6$)")))
		return ("; did you mean 'int16'?");
	else if (std::regex_match(type, std::regex(R"(^.*2$)")))
		return ("; did you mean 'int32'?");
	else if (std::regex_match(type, std::regex(R"(^f.*$)")))
		return ("; did you mean 'float'?");
	else if (std::regex_match(type, std::regex(R"(^d.*$)")))
		return ("; did you mean 'double'?");
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
