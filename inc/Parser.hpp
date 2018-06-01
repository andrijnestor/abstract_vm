/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:12:27 by anestor           #+#    #+#             */
/*   Updated: 2018/06/01 00:37:00 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP
# include <regex>
# include <iostream>
# include "Lexer.hpp"
# include "VmExceptions.hpp"

class							Parser
{
	public:
		Parser(void);
		~Parser(void);
		Parser(Parser const & src);
		Parser					&operator=(Parser const & src);
		void					parseTokens(Tokens const & data);

	private:
		void					_lexicalError(void);
		void					_syntacticError(void);
		void					_instrName(void);
		void					_typeName(void);
		void					_validValue(void);
		void					_exit(void);////?????
		
};

#endif
