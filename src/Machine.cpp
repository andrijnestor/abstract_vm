/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:33:18 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 20:46:40 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Machine.hpp"

Machine::Machine(void)
{
//	this->_stdinLexer();
//	this->dumpTokens();
}

Machine::Machine(std::string const & file)
{
	try
	{
		this->_fileLexer(file);
		this->dumpTokens();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl; //// wtf is here?
	}
}

Machine::~Machine(void)
{

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

void			Machine::parseInput(void)  // just test func
{
	try
	{
		IOperand	const *test = this->_creator.createOperand(Int8, "40.9");
		IOperand	const *test1 = this->_creator.createOperand(Int8, "20");
		IOperand	const *test2 = *test + *test1;
		this->_stack.push_back(*test / *test1);
		this->_stack.push_back(*test % *test1);
		this->_stack.push_back(test2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void			Machine::dumpStack(void)
{
	for (auto it = this->_stack.begin(); it != this->_stack.end(); it++)
	{
		IOperand const	*print = *it;
		std::cout << print->toString() << std::endl;
	}
}

void			Machine::_fileLexer(std::string const & file)
{
	std::string		line;
	std::ifstream	fs(file);
	size_t			n = 1;

	if (fs.is_open()) // is it safe?
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
	for (auto it = this->_data.begin(); it != this->_data.end(); it++)
	{
		
	}
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

