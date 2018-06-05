/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:12:27 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 17:14:34 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP
# include <regex>
# include <iostream>
# include "Lexer.hpp"
# include "VmExceptions.hpp"
# include "Operand.hpp"

class							Parser
{
	public:
		Parser(void);
		~Parser(void);
		Parser(Parser const & src);
		Parser					&operator=(Parser const & src);
		bool					parseErrors(Tokens const & data);
		IOperand const			*returnOperand(Tokens const & data);

	private:
		std::map<std::string, eOperandType>	_type;
		COperand				_creator;
		void					_mapType(void);
		void					_lexicalError(bool lexical);
		void					_instName(std::string const & inst);
		void					_typeName(std::string const & type);
		void					_validValue(std::string const & value, std::string const & type);
};

#endif
