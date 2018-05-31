/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:39:07 by anestor           #+#    #+#             */
/*   Updated: 2018/05/31 17:50:01 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Machine.hpp"

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string		file(argv[1]);
		Machine m(file);
	//	m.runVM(file);
	}
	else
	{
		Machine m;
		m.parseInput("23");
		m.parseInput("22");
		m.parseInput("24");
		m.parseInput("26");
		m.dumpStack();
	}
	return (0);
}
