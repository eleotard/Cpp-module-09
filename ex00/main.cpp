/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:00 by eleotard          #+#    #+#             */
/*   Updated: 2023/08/31 19:32:49 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <fstream>
#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <string>

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc <= 1)
		return (std::cerr << "Error: could not open file." << std::endl, 1);
	if (!argv[1][0])
		return (std::cerr << "Error: empty argument." << std::endl, 2);
	
	BitcoinExchange b;
	try {
		b.setDatabase("data.csv");
		b.treatInputFile(argv[1]);	
	}
	catch (std::exception const& e) {
		std::cerr << RED << e.what() << DEFAULT << std::endl;
	}
    return (0);
}
