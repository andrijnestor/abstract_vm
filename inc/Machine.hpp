/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Machine.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:42:37 by anestor           #+#    #+#             */
/*   Updated: 2018/05/29 21:24:00 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHINE_HPP
# define MACHINE_HPP
# include <vector>
# include "Operand.hpp"
//# include "Int8.hpp"

struct									Tokens
{
	int									line;
	std::string							inst;
	eOperandType						type;  //error value?
	std::string							value;
};

class									Machine
{
	public:
		Machine(void);
//		Machine(std::string file);
		Machine(Machine const & src);
		~Machine(void);
		Machine							&operator=(Machine const & src);
		void							parseInput(std::string line);   //del me
		void							dumpStack(void);  //in parser?
//		void							compute(std::string file);

	private:
		std::vector<Tokens>				_data;
		std::vector<const IOperand *>	_stack;   //ioperland

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
