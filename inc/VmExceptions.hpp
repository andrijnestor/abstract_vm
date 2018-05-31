/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VmExceptions.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:18:58 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 20:44:54 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMEXCEPTIONS_HPP
# define VMEXCEPTIONS_HPP
# include <exception>
# include <cstring>
# include <cerrno>

class						VmExceptions : public std::exception
{
	public:
		virtual ~VmExceptions(void) throw();
		virtual const char	*what() const throw();
		class				Owerflow : public std::exception
		{
			public:
				virtual ~Owerflow(void) throw();
				virtual const char	*what() const throw();
		};
		class				Underflow : public std::exception
		{
			public:
				virtual ~Underflow(void) throw();
				virtual const char	*what() const throw();
		};
		class				DivZero : public std::exception
		{
			public:
				virtual ~DivZero(void) throw();
				virtual const char	*what() const throw();
		};
		class				ModZero : public std::exception
		{
			public:
				virtual ~ModZero(void) throw();
				virtual const char	*what() const throw();
		};
		class				UnknownInstruction : public std::exception
		{
			public:
				virtual ~UnknownInstruction(void) throw();
				virtual const char	*what() const throw();
		};
		class				LexicalError : public std::exception
		{
			public:
				virtual ~LexicalError(void) throw();
				virtual const char	*what() const throw();
		};
		class				SyntacticError : public std::exception
		{
			public:
				virtual ~SyntacticError(void) throw();
				virtual const char	*what() const throw();
		};
		class				EmptyStack : public std::exception
		{
			public:
				virtual ~EmptyStack(void) throw();
				virtual const char	*what() const throw();
		};
		class				ExitFault : public std::exception
		{
			public:
				virtual ~ExitFault(void) throw();
				virtual const char	*what() const throw();
		};
		class				AssertFault : public std::exception
		{
			public:
				virtual ~AssertFault(void) throw();
				virtual const char	*what() const throw();
		};
		class				StackLessTwo : public std::exception
		{
			public:
				virtual ~StackLessTwo(void) throw();
				virtual const char	*what() const throw();
		};
		class				WrongValueType : public std::exception
		{
			public:
				virtual ~WrongValueType(void) throw();
				virtual const char	*what() const throw();
		};
		class				WrongFile : public std::exception
		{
			public:
				virtual ~WrongFile(void) throw();
				virtual const char	*what() const throw();
		};
};

#endif
