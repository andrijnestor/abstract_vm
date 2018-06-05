/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   COperand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:51:05 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 16:51:25 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "COperand.hpp"
#include "Operand.hpp"

COperand::COperand()
{
	typedef std::pair<eOperandType, IOperand const* (COperand::*)(std::string const &v) const> mp;

	_mp.insert(mp(Int8, &COperand::createInt8));
	_mp.insert(mp(Int16, &COperand::createInt16));
	_mp.insert(mp(Int32, &COperand::createInt32));
	_mp.insert(mp(Float, &COperand::createFloat));
	_mp.insert(mp(Double, &COperand::createDouble));
}

COperand::COperand(COperand const & src)
{
	*this = src;
}

COperand &COperand::operator=(COperand const &src)
{
	if (this != &src)
	{
		this->_mp = src._mp;
	}
	return (*this);
}

COperand::~COperand() {}

IOperand const *COperand::createOperand(eOperandType const & type, std::string value) const
{
	auto func = _mp.at(type);
	return ((*this.*func)(value));
}

IOperand const *COperand::createInt8(std::string const & value) const
{
	return (new Operand<int8_t>(value, Int8, 0));
}

IOperand const *COperand::createInt16(std::string const & value) const
{
	return (new Operand<int16_t>(value, Int16, 0));
}

IOperand const *COperand::createInt32(std::string const & value) const
{
	return (new Operand<int32_t>(value, Int32, 0));
}

IOperand const *COperand::createFloat(std::string const & value) const
{
	return (new Operand<float>(value, Float, 7));
}

IOperand const *COperand::createDouble(std::string const & value) const
{
	return (new Operand<double>(value, Double, 15));
}
