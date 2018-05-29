/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:51:46 by anestor           #+#    #+#             */
/*   Updated: 2018/05/29 21:23:58 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP
# include "IOperand.hpp"
# include <sstream>
# include <iomanip>
# include "COperand.hpp"
# include <tgmath.h>

template <typename T>
class							Operand : public IOperand
{
	public:
		Operand(std::string const & value, eOperandType type, int precision)
		{
			std::stringstream	temp;
			double				temp_val;
		
			try
			{
				temp_val = std::stod(value);
				this->checkOverflowUnderflow(temp_val);
				this->_value = static_cast<T>(temp_val);
				this->_type = type;
				this->_precision = precision;
				temp << std::fixed << std::setprecision(precision) << temp_val;
				this->_str = temp.str();
				std::cout << "constr " << this->_str << " " << value <<  std::endl; ///
			}
			catch (std::exception &e)
			{
				throw ;
			}
		}
		Operand(Operand const & src)
		{
			*this = src;
		}
		~Operand(void) {}
		Operand					&operator=(Operand const & src)
		{
			if (this != &src)
			{
				this->_type = src._type;
				this->_value = src._value;
				this->_precision = src._precision;
				this->_str = src._str;
				this->_creator = src->_creator;
			}
			return (*this);
		}
		IOperand const			*operator+(IOperand const & rhs) const
		{
			std::string sum =
				std::to_string(this->_value + std::stod(rhs.toString()));
			eOperandType type =
				this->_type > rhs.getType() ? this->_type : rhs.getType();
			return (this->_creator.createOperand(type, sum));
		}
		IOperand const			*operator-(IOperand const & rhs) const
		{
			std::string sum =
				std::to_string(this->_value - std::stod(rhs.toString()));
			eOperandType type =
				this->_type > rhs.getType() ? this->_type : rhs.getType();
			return (this->_creator.createOperand(type, sum));
		}
		IOperand const			*operator*(IOperand const & rhs) const
		{
			std::string sum =
				std::to_string(this->_value * std::stod(rhs.toString()));
			eOperandType type =
				this->_type > rhs.getType() ? this->_type : rhs.getType();
			return (this->_creator.createOperand(type, sum));
		}
		IOperand const			*operator/(IOperand const & rhs) const
		{
			if (std::stod(rhs.toString()) == 0)
				throw std::runtime_error("Div by zero");
			std::string sum =
				std::to_string(this->_value / std::stod(rhs.toString()));
			eOperandType type =
				this->_type > rhs.getType() ? this->_type : rhs.getType();
			return (this->_creator.createOperand(type, sum));
		}
		IOperand const			*operator%(IOperand const & rhs) const
		{
			if (std::stod(rhs.toString()) == 0)
				throw std::runtime_error("Mod by zero");
			std::string sum =
				std::to_string(std::fmod(this->_value, std::stod(rhs.toString())));
			eOperandType type =
				this->_type > rhs.getType() ? this->_type : rhs.getType();
			return (this->_creator.createOperand(type, sum));
		}
		int						getPrecision(void) const
		{
			return (this->_precision);
		}
		eOperandType			getType(void) const
		{
			return (this->_type);
		}
		std::string const		&toString(void) const
		{
			return (this->_str);
		}
		void					checkOverflowUnderflow(double value)
		{
			if (value > std::numeric_limits<T>::max())
				throw std::runtime_error("Overflow");
			if (value < std::numeric_limits<T>::min())
				throw std::runtime_error("Underflow");		
		}

	private:
		Operand(void) {}
		eOperandType			_type;
		T						_value;
		int						_precision;
		std::string				_str;
		COperand const			_creator;
};

#endif
