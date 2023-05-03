/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:00 by eleotard          #+#    #+#             */
/*   Updated: 2023/05/03 20:27:16 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <fstream>
#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <string>

	// std::cout << "\033[34m"; //bleu
	// std::cout << "\033[32m"; //vert
	// std::cout << "\033[35m"; //violet
	// std::cout << "\033[33m"; //jaune
	
//ptime
//split
//attribuer 1er value
//verifier la syntaxe
//attribuer la 2e valeur
//verifier la syntaxe
//std::cout.precisionset(7)





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
		//b.printInputs();
		b.treatInputFile(argv[1]);	
	}
	catch (std::exception const& e) {
		std::cout << e.what() << std::endl;
	}
	
	// if (b.getDbState()) {
	// 	try {
	// 		b.treatInputFile(argv[1]);	
	// 	}
	// 	catch (std::exception const& e) {
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }

	//while avec un try catch a linterieur
    
    return (0);
}








	// try {
	// 	std::map<std::string, double> m_data = getDataBase();
	// 	std::map<std::string, double>::iterator it = m_data.begin();
	// 	std::cout.precision(7);
	// 	for (; it != m_data.end(); it++) {
	// 		std::cout << YELLOW << it->first << " => " << it->second << DEFAULT <<'\n';
	// 	}
	// 	std::cout << std::endl;
	// 	std::cout << std::endl;
	// }
	// catch (std::exception const& e) {
	// 	std::cout << e.what() << std::endl;
	// }

// std::map<std::string, double> getDataBase() {
    
// 	std::map<std::string, double> inputs;
//     std::string		line("data.csv");
// 	std::ifstream	file (line.c_str());
// 	std::string		delimiter = ",";
// 	size_t i = 0;
// 	char *pEnd;
	
// 	if (!file.is_open()) {
// 		file.close();
// 		throw (BitcoinExchange::WrongFile());
// 	}
// 	else {
//         line = "";
// 		while (getline(file, line)) {
// 			if (line == "date,exchange_rate")
// 				continue ;
// 			i = line.find(delimiter);
// 			std::string token1 = line.substr(0, i);
// 			std::string token2 = line.substr(i + 1, *line.end() - i);
// 			inputs[token1] = std::strtod(token2.c_str(), &pEnd);
// 		}
// 	}
// 	file.close();
// 	return (inputs);
// }