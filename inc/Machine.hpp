/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:42:37 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 17:50:02 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHINE_HPP
# define MACHINE_HPP
# include <vector>
# include <fstream>
# include "Operand.hpp"
# include "Lexer.hpp"
# include "VmExceptions.hpp"
/*
struct									Tokens
{
	int									line;
	std::string							inst;
	std::string							type;
	std::string							value;
	bool								lexical;  //if wrong n of tokens or different random cymbols
};
*/
class									Machine
{
	public:
		Machine(void);
		Machine(std::string const & file);
		Machine(Machine const & src);
		~Machine(void);
		Machine							&operator=(Machine const & src);
		void							parseInput(std::string line);   //del me
		void							dumpStack(void);  //in parser?
//		void							compute(std::string file);

	private:
		std::vector<Tokens>				_data;
		std::vector<const IOperand *>	_stack;   //ioperland
		Lexer							_lexer;
	//	void							_stdinLexer(void);
		void							_fileLexer(std::string const & file);

};

#endif

/*
struct								StackStruct
{
    enum
	{
									Int8,
									Int16,
									Int32,
									Float,
									Double
	}								type;
   
	eOperlandType					type;
   	union
    {
        int8_t						e;
        int16_t						s;
		int32_t						t;
		float						f;
        double						d;
    };
};

*/
