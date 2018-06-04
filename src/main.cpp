/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:39:07 by anestor           #+#    #+#             */
/*   Updated: 2018/06/04 18:04:05 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Machine.hpp"

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::string		file(argv[1]);
		Machine m(file);
	}
	else
	{
		Machine m;
	}
	std::cout << std::endl;
	system("leaks avm");
	return (0);
}
