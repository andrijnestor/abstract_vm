/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:23:32 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 20:24:42 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void)
{
}

Parser::~Parser(void) {}

Parser::Parser(Parser const & src)
{
	*this = src;
}

Parser				&Parser::operator=(Parser const & src)
{
	if (this != &src)
	{
		///
	}
	return (*this);
}
