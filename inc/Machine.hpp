/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:42:37 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 20:26:57 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHINE_HPP
# define MACHINE_HPP
# include <vector>
# include <fstream>
# include "Operand.hpp"
# include "Lexer.hpp"
# include "Parser.hpp"
# include "VmExceptions.hpp"

class									Machine
{
	public:
		Machine(void);
		Machine(std::string const & file);
		Machine(Machine const & src);
		~Machine(void);
		Machine							&operator=(Machine const & src);
		void							parseInput(void);   //del me
		void							dumpStack(void);
		void							dumpTokens(void);

	private:
		std::vector<Tokens>				_data;
		std::vector<const IOperand *>	_stack;
		Lexer							_lexer;
		Parser							_parser;
		COperand						_creator;
		void							_stdinLexer(void);
		void							_fileLexer(std::string const & file);
		void							_tokensParser(void);

};

#endif
