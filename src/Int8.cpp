/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 17:06:34 by anestor           #+#    #+#             */
/*   Updated: 2018/05/26 21:11:37 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Int8.hpp"

Int8::Int8(void)
{
	this->_type = ::Int8;
	this->_value = 0;
//	this->_string = new std::string;
}

Int8::~Int8(void)
{
//	delete this->_string;
}

Int8::Int8(Int8 const & src)
{
	*this = src;
}

class Int8			&Int8::operator=(Int8 const & src)
{
	if (this != &src)
	{
		this->_type = src._type;
		this->_value = src._value;
	}
	return (*this);
}

int					Int8::getPrecision(void) const
{
	return (0);
}

eOperandType		Int8::getType(void) const
{
	return (this->_type);
}

void				Int8::setType(eOperandType type)
{
	this->_type = type;
}
/*
void				Int8::setString(std::string value)
{
	this->_string = &value;
}
*/
std::string const	&Int8::toString(void) const   //// rly???
{
	std::string	*ret = new std::string;
	*ret = std::to_string(this->_value);
	return (*ret);
}

int8_t				Int8::getValue(void) const
{
	return (this->_value);
}

void				Int8::setValue(int8_t value)
{
	this->_value = value;
}

IOperand const		*Int8::operator+(IOperand const & rhs) const
{
	Int8	*result = new class Int8;
	result->setValue(this->_value + std::stod(rhs.toString()));
	return (result); /// must return Creator ??
}
