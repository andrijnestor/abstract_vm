/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   COperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:51:14 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 16:51:26 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COPERAND_HPP
# define COPERAND_HPP
# include "IOperand.hpp"
# include <map>

class							COperand
{
	public:
		COperand();
		COperand(COperand const & src);
		virtual ~COperand();
		COperand				&operator=(COperand const & src);
		IOperand const 			*createOperand(eOperandType const & type, std::string value) const;

	private:
		IOperand const			*createInt8(std::string const & value) const;
		IOperand const			*createInt16(std::string const & value) const;
		IOperand const			*createInt32(std::string const & value) const;
		IOperand const			*createFloat(std::string const & value) const;
		IOperand const			*createDouble(std::string const & value) const;
		std::map<eOperandType, IOperand const* (COperand::*)(std::string const & value) const> _mp;
};

#endif
