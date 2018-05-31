/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 20:12:27 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 20:24:43 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP
# include <regex>
# include <iostream>

class							Parser
{
	public:
		Parser(void);
		~Parser(void);
		Parser(Parser const & src);
		Parser					&operator=(Parser const & src);

	private:
		
};

#endif
