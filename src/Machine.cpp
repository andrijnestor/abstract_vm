/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:33:18 by anestor           #+#    #+#             */
/*   Updated: 2018/06/06 12:10:57 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Machine.hpp"

Machine::Machine(void)
{
	this->_exit = false;
	try
	{
		this->_makeRunMap();
		this->_stdinLexer();
//		this->dumpTokens();
		this->_tokensParser();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

Machine::Machine(std::string const & file)
{
	this->_exit = false;
	try
	{
		this->_makeRunMap();
		this->_fileLexer(file);
	//	this->dumpTokens();
		this->_tokensParser();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

Machine::~Machine(void)
{
	try
	{
		this->_checkExit();
	}
	catch (std::exception &e)
	{
		std::cout << "Line " << this->_data.size() << ": " << e.what() << std::endl; 
	}
	for (auto it = this->_stack.begin(); it != this->_stack.end(); it++)
	{
		delete (*it);
	}
}

Machine::Machine(Machine const & src)
{
	*this = src;
}

Machine			&Machine::operator=(Machine const & src)
{
	if (this != &src)
	{
		this->_data = src._data;
		this->_stack = src._stack;
		this->_lexer = src._lexer;
		this->_parser = src._parser;
		this->_creator = src._creator;
		this->_exit = src._exit;
	}
	return (*this);
}

void			Machine::_makeRunMap(void)
{
	typedef std::pair<std::string, void (Machine::*)(IOperand const*)> mp;

	_run.insert(mp("pop", &Machine::_iPop));
	_run.insert(mp("push", &Machine::_iPush));
	_run.insert(mp("dump", &Machine::_iDump));
	_run.insert(mp("assert", &Machine::_iAssert));
	_run.insert(mp("add", &Machine::_iAdd));
	_run.insert(mp("sub", &Machine::_iSub));
	_run.insert(mp("mul", &Machine::_iMul));
	_run.insert(mp("div", &Machine::_iDiv));
	_run.insert(mp("mod", &Machine::_iMod));
	_run.insert(mp("print", &Machine::_iPrint));
	_run.insert(mp("exit", &Machine::_iExit));
	_run.insert(mp("max", &Machine::_iMax));
	_run.insert(mp("min", &Machine::_iMin));
	_run.insert(mp("pow", &Machine::_iPow));
	_run.insert(mp("avg", &Machine::_iAvg));
}

void			Machine::dumpTokens(void)
{
	for (auto it = this->_data.begin(); it != this->_data.end(); it++)
	{
		std::cout	<< it->line << " "
					<< it->inst << " "
					<< it->type << " "
					<< it->value << " "
					<< it->lexical
					<< std::endl;
	}
}

void			Machine::dumpStack(void)
{
	for (auto it = this->_stack.end() - 1; it != this->_stack.begin() - 1; it--)
	{
		std::cout << (*it)->toString() << std::endl;
	}
}

void			Machine::_fileLexer(std::string const & file)
{
	std::string		line;
	std::ifstream	fs(file);
	size_t			n = 1;

	if (fs.is_open())
	{
		while (getline(fs, line))
			this->_data.push_back(this->_lexer.lexicalAnalysis(line, n++));
		fs.close();
	}
	else
	{
		this->_exit = true;
		throw (VmExceptions::WrongFile());
	}
}

void			Machine::_stdinLexer(void)
{
	std::string		line;
	size_t			n = 1;

	while (1)
	{
		getline(std::cin, line);
		if (line == ";;")
			break ;
		this->_data.push_back(this->_lexer.lexicalAnalysis(line, n++));
	}
}

void			Machine::_tokensParser(void)
{
	int		line;

	for (auto it = this->_data.begin(); it != this->_data.end(); it++)
	{
		line = (*it).line;
		try
		{
			if (this->_exit == true)
				throw (VmExceptions::ExitFault());
			if (this->_parser.parseErrors(*it))
			{
				auto run = _run.at((*it).inst);
				((*this.*run)(this->_parser.returnOperand(*it)));
			}
		}
		catch (std::exception &e)
		{
			std::cout << "Line " << line << ": " << e.what() << std::endl;
		}
	}
}


void			Machine::_iPop(IOperand const *)
{
	if (this->_stack.size() > 0)
	{
		auto it = this->_stack.end() - 1;
		delete (*it);
		this->_stack.erase(it);
	}
	else
	{
		throw (VmExceptions::EmptyStack());
	}
}

void			Machine::_iPush(IOperand const *value)
{
	this->_stack.push_back(value);
}

void			Machine::_iDump(IOperand const *)
{
	this->dumpStack();
}

void			Machine::_iAssert(IOperand const *value)
{
	if (this->_stack.size() > 0 && value != nullptr
	&& this->_stack.back()->toString() == value->toString()
	&& this->_stack.back()->getType() == value->getType())
	{
		delete value;
	}
	else
	{
		delete value;
		throw (VmExceptions::AssertFault());
	}
}

void			Machine::_iAdd(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			this->_stack.push_back(*two + *one);
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}

void			Machine::_iSub(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			this->_stack.push_back(*two - *one);
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}

void			Machine::_iMul(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			this->_stack.push_back(*two * *one);
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}

void			Machine::_iDiv(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			this->_stack.push_back(*two / *one);
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}

void			Machine::_iMod(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			this->_stack.push_back(*two % *one);
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}


void			Machine::_iMax(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		if (std::stod((*two).toString()) > std::stod(((*one).toString())))
		{
			delete one;
			this->_stack.push_back(two);
		}
		else
		{
			delete two;
			this->_stack.push_back(one);
		}
	}
}

void			Machine::_iMin(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		if (std::stod((*two).toString()) < std::stod(((*one).toString())))
		{
			delete one;
			this->_stack.push_back(two);
		}
		else
		{
			delete two;
			this->_stack.push_back(one);
		}
	}
}


void			Machine::_iPow(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			eOperandType	type =
				(*two).getType() > (*one).getType() ? (*two).getType() : (*one).getType();
			std::string		value =
				std::to_string(std::pow(std::stod((*two).toString()), std::stod((*one).toString())));
			this->_stack.push_back(this->_creator.createOperand(type, value));
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}

void			Machine::_iAvg(IOperand const *)
{
	if (this->_stack.size() < 2)
		throw (VmExceptions::StackLessTwo());
	else
	{
		IOperand const *one = this->_stack.back();
		this->_stack.pop_back();
		IOperand const *two = this->_stack.back();
		this->_stack.pop_back();
		try
		{
			eOperandType	type =
				(*two).getType() > (*one).getType() ? (*two).getType() : (*one).getType();
			std::string		value =
				std::to_string((std::stod((*two).toString()) + std::stod((*one).toString())) / 2);
			this->_stack.push_back(this->_creator.createOperand(type, value));
		}
		catch (std::exception &e)
		{
			this->_stack.push_back(two);
			this->_stack.push_back(one);
			throw ;
		}
		delete one;
		delete two;
	}
}

void			Machine::_iPrint(IOperand const *)
{
	if (this->_stack.size() > 0)
	{
		if ((this->_stack.back()->getType() != Int8))
			throw (VmExceptions::AssertFault());
		auto c = std::stoll(this->_stack.back()->toString());
		std::cout << static_cast<char>(c);
	}
	else
		throw (VmExceptions::PrintEmptyStack());
}

void			Machine::_iExit(IOperand const *)
{
	this->_exit = true;
}

void			Machine::_checkExit(void)
{
	if (this->_exit == false)
		throw (VmExceptions::NoExitFault());
}
