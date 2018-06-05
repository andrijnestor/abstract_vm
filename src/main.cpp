/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:39:07 by anestor           #+#    #+#             */
/*   Updated: 2018/06/05 17:36:41 by anestor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Machine.hpp"

int		main(int argc, char **argv)
{
	if (argc == 2)
		Machine m((std::string(argv[1])));
	else
		Machine m;
//	system("leaks avm");
	return (0);
}
