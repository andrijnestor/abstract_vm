/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:33:18 by anestor           #+#    #+#             */
/*   Updated: 2018/06/04 20:10:02 by anestor          ###   ########.fr       */
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
//		this->dumpTokens(); // just for me
		this->_tokensParser();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << " Machine(void) " << std::endl; //// wtf is here?
	}
}

Machine::Machine(std::string const & file)
{
	this->_exit = false;
	try
	{
		this->_makeRunMap();
		this->_fileLexer(file);
//		this->dumpTokens(); // just for me
		this->_tokensParser();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << " Machine(Machine const & file) " << std::endl; //// wtf is here?
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
//		this->_stack = src._stack;   /// no assing
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
			std::cout << "line " << line << ": " << e.what() << std::endl;
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
//	std::cout << "pop" << std::endl;
}

void			Machine::_iPush(IOperand const *value)
{
	this->_stack.push_back(value);
//	std::cout << "push" << std::endl;
}

void			Machine::_iDump(IOperand const *)
{
	this->dumpStack();
//	std::cout << "dump" << std::endl;
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
//	std::cout << "assert" << std::endl;
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
			this->_stack.push_back(*one + *two);
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
//	std::cout << "add" << std::endl;
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
			this->_stack.push_back(*one - *two);
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
//	std::cout << "sub" << std::endl;
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
			this->_stack.push_back(*one * *two);
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

//	std::cout << "mul" << std::endl;
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
			this->_stack.push_back(*one / *two);
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

//	std::cout << "div" << std::endl;
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
			this->_stack.push_back(*one % *two);
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

//	std::cout << "mod" << std::endl;
}

void			Machine::_iPrint(IOperand const *)
{
	if ((this->_stack.back()->getType() != Int8))
		throw (VmExceptions::AssertFault());
	auto c = std::stoll(this->_stack.back()->toString());
	std::cout << static_cast<char>(c);
//	std::cout << "print" << std::endl;
}

void			Machine::_iExit(IOperand const *)
{
	this->_exit = true;
//	std::cout << "exit" << std::endl;
}

void			Machine::_checkExit(void)
{
	if (this->_exit == false)
		throw (VmExceptions::NoExitFault());
}

/*

	class Int8	a;
	class Int8	b;
	a.setValue(2);
	b.setValue(3);
	const IOperand	*s = a + b;
	std::cout << s->toString() << std::endl;
	const class Int8	*d = dynamic_cast<const class Int8 *>(a + b);
	const class Int8	*f = dynamic_cast<const class Int8 *>(s);
	class Int8	*l = new class Int8;
	l = const_cast<class Int8 *>(d);
	class Int8	*p = const_cast<class Int8 *>(d);
	(void)f;
	(void)p;
//	s(*this->_stack[0] + *this->_stack[1]);
	this->_stack.push_back(l);

	COperand	creator;

//	IOperand	*test = new Operand<int8_t>("40.0", Int8, 0);

	eOperandType	d = Int8;
	if (d >= 0 && d <= 4)
		std::cout << "Yes!" << std::endl;
	try
	{
		IOperand	const *test = creator.createOperand(d, "40.9");
		IOperand	const *test1 = creator.createOperand(Int8, "20");
//		IOperand	const *test2 = *test + *test1;
		this->_stack.push_back(*test / *test1);
		this->_stack.push_back(*test % *test1);
//		this->_stack.push_back(test2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	for (size_t i = 0; i != this->_stack.size(); i++)
		std::cout << this->_stack[i]->toString() << std::endl; //not type



	Lexer	a;

	Tokens v = a.lexicalAnalysis("assert absasd(   123. 123) ;asdasd", 1);
	Tokens s = a.lexicalAnalysis(";; ;asdasd", 1);
	std::cout << s.line << " " << s.inst << " " << s.type << " " << s.value << " " << s.lexical << std::endl;
	this->_data.push_back(a.lexicalAnalysis("   pop  ;asdasd ", 1));
*/

