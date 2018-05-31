/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:47:02 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 17:50:05 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP
# include <regex>
# include <iostream>

struct							Tokens
{
	int							line;
	std::string					inst;
	std::string					type;
	std::string					value;
	bool						lexical;
};

class							Lexer
{
	public:
		Lexer(void);
		~Lexer(void);
		Lexer(Lexer const & src);
		Lexer					&operator=(Lexer const & src);
		Tokens					lexicalAnalysis(std::string const & line, int lineN);

	private:
		Tokens					_singleInstruction(void);
		Tokens					_instructionWithValue(void);
		Tokens					_emptyLine(void);
		Tokens					_lexicalError(void);
		Tokens					_tokens;
		std::string				_line;
		std::regex				_instr;
		std::regex				_instrNvalue;
		std::regex				_empty;
};

#endif
