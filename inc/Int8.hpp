/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Int8.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:59:57 by anestor           #+#    #+#             */
/*   Updated: 2018/05/26 21:11:34 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT8_HPP
# define INT8_HPP
# include "IOperand.hpp"

class									Int8 : public IOperand
{
	public:
		Int8(void);
		Int8(Int8 const & src);
		~Int8(void);
		Int8							&operator=(Int8 const & src);
		IOperand const					*operator+(IOperand const & rhs) const;
		int								getPrecision(void) const;   ////???
		eOperandType					getType(void) const;
		std::string const				&toString(void) const;
		void							setType(eOperandType type); ///do i need?
		int8_t							getValue(void) const;
		void							setValue(int8_t value);
//		void							setString(std::string value);
	
	private:
		eOperandType					_type;
		int8_t							_value;
//		std::string						*_string;
};

#endif
