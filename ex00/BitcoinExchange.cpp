/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/21 18:37:33 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _inputs(0) {
	std::cout << "BitcoinExchange constructed" << std::endl;
}

// BitcoinExchange::BitcoinExchange(std::string filename) {
// 	std::cout << "BitcoinExchange file constructed" << std::endl;
// }

BitcoinExchange::BitcoinExchange(BitcoinExchange const& src) {
	*this = src;
	//std::cout << "BitcoinExchange copy constructed" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {
	std::cout << "BitcoinExchange destructed" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const& src) {
	_m = src._m;
	_inputs = src._inputs;
	return (*this);
}

void	BitcoinExchange::recoverInput(std::string const& filename) {
	
	std::string	line;
	std::ifstream file (filename.c_str());
	
	if (!file.is_open()) {
		file.close();
		throw (BitcoinExchange::WrongFile());
	}
	else {
		while (getline(file, line)) {
			_inputs.push_back(line);
			std::cout << line << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	printInputs();
	file.close();
}


void	BitcoinExchange::checkSyntax() {
	std::vector<std::string>::iterator it = _inputs.begin();

	for (; it != _inputs.end(); ++it) {
		//check toute la syntaxe
	}
}

void	BitcoinExchange::printInputs() {
	
	std::vector<std::string>::iterator it = _inputs.begin();
	for (; it != _inputs.end(); ++it) {
		std::cout << *it << std::endl;
	}
}