/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:23:32 by anestor           #+#    #+#             */
/*   Updated: 2018/06/01 00:42:49 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void)
{
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

void				Parser::parseTokens(Tokens const & data)
{
	(void)data;
	try
	{
		this->_lexicalError();
		this->_syntacticError();		
	}
	catch (VmExceptions::LexicalError &e)
	{
		std::cout << e.what() << std::endl;
	}
///	catch (VmExceptions::SyntacticError &e)
//	{
//		std::cout << e.what() << std::endl;
//	}
}

void				Parser::_lexicalError(void)
{
	throw VmExceptions::LexicalError();
}

void				Parser::_syntacticError(void)
{
	throw VmExceptions::SyntacticError();
}
