/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:47:02 by anestor           #+#    #+#             */
/*   Updated: 2018/05/30 22:51:30 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP
# include <regex>
# include <iostream>

struct									Tokens
{
	int									line;
	std::string							inst;
	std::string							type;
	std::string							value;
	bool								lexical;  //if wrong n of tokens or different random cymbols
};

class							Lexer
{
	public:
		Lexer(void);
		~Lexer(void);
		Lexer(Lexer const & src);
		Lexer					&operator=(Lexer const & src);
		std::vector<Tokens>		lexicalAnalysis(std::string const & file);
	//	void					setLine(void);
	//	void					setInst(void);
	//	void					setValue(void);
	//	void					setError(void);

	private:
		Tokens					_data;
		std::regex				_regex;
};

#endif
