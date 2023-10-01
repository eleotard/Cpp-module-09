/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:00 by eleotard          #+#    #+#             */
/*   Updated: 2023/10/01 14:13:25 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <fstream>
#include "BitcoinExchange.hpp"
#include <string>

int main(int argc, char **argv)
{
	if (argc <= 1)
		return (std::cerr << "Error: 1 filename should be used as an argument." << std::endl, 1);
	if (argc != 2)
		return (std::cerr << "Error: only 1 filename should be used as an argument." << std::endl, 2);
	if (!argv[1][0])
		return (std::cerr << "Error: empty argument." << std::endl, 3);
	
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
