/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 21:21:58 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 23:43:25 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer(void)
{
	this->_instr.assign(R"(^\s*(pop|dump|add|sub|mul|div|mod|print|exit|max|min|avg|pow)(\s*|\s+;.*)$)");
	this->_instrNvalue.assign(R"(^\s*(push|assert)\s+\w+\(.+\)(\s*|\s+;.*)$)");
	this->_empty.assign(R"(^(\s*|\s*;.*)$)");
}

Lexer::~Lexer(void) {}

Lexer::Lexer(Lexer const & src)
{
	*this = src;
}

Lexer				&Lexer::operator=(Lexer const & src)
{
	if (this != &src)
	{
		this->_line = src._line;
		this->_tokens = src._tokens;
		this->_instr = src._instr;
		this->_instrNvalue = src._instrNvalue;
		this->_empty = src._empty;
	}
	return (*this);
}

Tokens				Lexer::lexicalAnalysis(std::string const & line, int lineN)
{
	this->_line = line;
	this->_tokens.line = lineN;
	if (std::regex_match(line, this->_instr))
		return (this->_singleInstruction());
	else if (std::regex_match(line, this->_instrNvalue))
		return (this->_instructionWithValue());
	else if (std::regex_match(line, this->_empty))
		return (this->_emptyLine());
	else
		return (this->_lexicalError());
}

Tokens				Lexer::_singleInstruction(void)
{
	std::smatch	m;
	std::regex_search(this->_line, m, std::regex(R"(\w+)"));
	this->_tokens.inst = m.str();
	this->_tokens.type = "Null";
	this->_tokens.value = "Null";
	this->_tokens.lexical = false;
	return (this->_tokens);
}

Tokens				Lexer::_instructionWithValue(void)
{
	std::smatch	m;
	std::regex_search(this->_line, m, std::regex(R"(\w+)"));
	this->_tokens.inst = m.str();
	std::regex_search(this->_line, m, std::regex(R"(\w+\()"));
	this->_tokens.type = m.str().substr(0, m.str().size() - 1);
	std::regex_search(this->_line, m, std::regex(R"(\(.*\))"));
	this->_tokens.value = m.str().substr(1, m.str().size() - 2);
	this->_tokens.lexical = false;
	return (this->_tokens);
}

Tokens				Lexer::_emptyLine(void)
{
	this->_tokens.inst = "Null";
	this->_tokens.type = "Null";
	this->_tokens.value = "Null";
	this->_tokens.lexical = false;
	return (this->_tokens);
}

Tokens				Lexer::_lexicalError(void)
{
	std::smatch	m;
	std::regex_search(this->_line, m, std::regex(R"(\w+)"));
	this->_tokens.inst = m.str();
	this->_tokens.type = "Null";
	this->_tokens.value = "Null";
	this->_tokens.lexical = true;
	return (this->_tokens);
}

