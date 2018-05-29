/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:51:08 by anestor           #+#    #+#             */
/*   Updated: 2018/05/29 21:24:01 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP
# include <iostream>

enum									eOperandType
{
										Int8,
										Int16,
										Int32,
										Float,
										Double
};

class									IOperand
{
	public:
		virtual int						getPrecision(void) const = 0;
		virtual	eOperandType			getType(void) const = 0;
		virtual IOperand const	 		*operator+(IOperand const & rhs) const = 0;
		virtual IOperand const			*operator-(IOperand const & rhs) const = 0;
		virtual IOperand const			*operator*(IOperand const & rhs) const = 0;
		virtual IOperand const			*operator/(IOperand const & rhs) const = 0;
		virtual IOperand const			*operator%(IOperand const & rhs) const = 0;
		virtual std::string const		&toString(void) const = 0;
		virtual ~IOperand(void) {}
};

#endif
