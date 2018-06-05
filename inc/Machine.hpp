/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:42:37 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 17:33:35 by anestor          ###   ########.fr       */
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
		void							dumpStack(void);
		void							dumpTokens(void);

	private:
		bool							_exit;
		std::vector<Tokens>				_data;
		std::vector<const IOperand *>	_stack;
		Lexer							_lexer;
		Parser							_parser;
		COperand						_creator;
		std::map<std::string, void (Machine::*)(IOperand const *)>	_run;
		void							_makeRunMap(void);
		void							_stdinLexer(void);
		void							_fileLexer(std::string const & file);
		void							_tokensParser(void);
		void							_iPop(IOperand const *);
		void							_iPush(IOperand const *);
		void							_iDump(IOperand const *);
		void							_iAssert(IOperand const *);
		void							_iAdd(IOperand const *);
		void							_iSub(IOperand const *);
		void							_iMul(IOperand const *);
		void							_iDiv(IOperand const *);
		void							_iMod(IOperand const *);
		void							_iPrint(IOperand const *);
		void							_iExit(IOperand const *);
		void							_checkExit(void);

};

#endif
