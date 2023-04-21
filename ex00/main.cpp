/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:00 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/21 18:42:25 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <fstream>
#include "BitcoinExchange.hpp"
#include "Date.hpp"

std::vector<std::string> getDataBase() {
    
    std::string	line("data.scv");
	std::vector<std::string> inputs;
	std::ifstream file (line.c_str());
	
	if (!file.is_open()) {
		file.close();
		throw (BitcoinExchange::WrongFile());
	}
	else {
        line = "";
		while (getline(file, line)) {
			inputs.push_back(line);
			std::cout << line << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	file.close();
}


int main(int argc, char **argv)
{
    std::vector<std::string> v_data = getDataBase();
    if (argc <= 1)
        return (std::cerr << "Error: could not open file." << std::endl, 1);
    if (!argv[1][0])
        return (std::cerr << "Error: empty argument." << std::endl, 2);
    
    
    
    try {
        BitcoinExchange b = BitcoinExchange();
        b.recoverInput(std::string(argv[1]));
        b.checkSyntax();
        
    }
    catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }
    
    return (0);
}