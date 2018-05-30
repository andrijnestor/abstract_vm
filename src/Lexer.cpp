/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 21:21:58 by anestor           #+#    #+#             */
/*   Updated: 2018/05/30 22:51:26 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer(void)
{
	this->_regex.assign(R"(^\s*\S+((\s*|\s+;.*)$|\s+\S+\(\s*\S*\s*\)(\s*|\s+;.*)$)|^;.*$)");
}

Lexer::~Lexer(void) {}

Lexer::Lexer(Lexer const & src)
{
	*this = src;
}

Lexer				&Lexer::operator=(Lexer const & src)
{
	if (this != &src)
	{
		this->_data = src._data;
		this->_regex = src._regex;
	}
	return (*this);
}

std::vector<Tokens>	Lexer::lexicalAnalysis(std::string const & file)
{
	std::vector<Tokens>	vector;
//	Tokens				tokens;

	if (std::regex_match(file, this->_regex))
		std::cout << "hello there!" << std::endl;
	else
		std::cout << "I am here!" << std::endl;




    std::regex words_regex("[^\\s()]+");
    auto words_begin =
        std::sregex_iterator(file.begin(), file.end(), words_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " words:\n";

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        std::cout << match_str << '\n';
    }
	return (vector);
}
