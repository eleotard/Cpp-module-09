/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/28 19:51:27 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "BitcoinExchange.hpp"
#include <unistd.h>

BitcoinExchange::BitcoinExchange() : _dbState(0) {
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
	_dbState = src._dbState;
	return (*this);
}

void BitcoinExchange::setDatabase(std::string const& filename) {
    std::string		line;
	std::ifstream	file (filename.c_str());
	std::string		delimiter = ",";
	size_t i = 0;
	char *pEnd;
	
	if (!file.is_open()) {
		file.close();
		throw (BitcoinExchange::WrongFile());
	}
	else {
        line = "";
		while (getline(file, line)) {
			if (line == "date,exchange_rate")
				continue ;
			i = line.find(delimiter);
			std::string token1 = line.substr(0, i);
			std::string token2 = line.substr(i + 1, *line.end() - i);
			_m[token1] = std::strtod(token2.c_str(), &pEnd);
		}
	}
	file.close();
	_dbState = true;
}

std::map<std::string, double> const&BitcoinExchange::getDatabase() const {
	return (_m);
}

bool	BitcoinExchange::getDbState() const {
	return (_dbState);
}

void	BitcoinExchange::printInputs() {
	
	std::map<std::string, double>::iterator it = _m.begin();
	std::cout << _m.begin()->first << std::endl;
	for (; it != _m.end(); ++it) {
		std::cout << BLUE << it->first << " => " << it->second << DEFAULT << '\n';
	}
}

void	BitcoinExchange::checkGlobalSyntax(std::string & line) {
	size_t		i = 0;
	int			args = 0;
	std::string delimiter = " ";
	std::string save(line);
	
	while (i != std::string::npos)
	{
		//std::cout << YELLOW << "[" << line << "]" << DEFAULT << std::endl;
		i = line.find(delimiter);
		//std::cout << i << std::endl;
		if (i != std::string::npos) {
			i++;
			line = line.c_str() + i;
		}
		args++;
	}
	//std::cout << GREEN << args << DEFAULT << std::endl;
	if (args != 3)
		throw (BitcoinExchange::WrongGlobalSyntax());
	else 
		std::cout << save << std::endl;
}


void	BitcoinExchange::treatInputFile(std::string const& filename) {
	std::ifstream	file (filename.c_str());
	std::string		line;
	
	while(getline(file, line)) {
		if (line == "date | value")
			continue ;
		try {
			checkGlobalSyntax(line);
			//si la syntaxe globale est respectee
			//si la syntaxe de la date est respectee
			//si la date est rationnelle
			//sil ny a pas d'overflow
		}
		catch (std::exception const& e) {
			std::cout << e.what() << std::endl;
		}
	}
}



// void	BitcoinExchange::recoverInput(std::string const& filename) {
	
// 	std::string		line;
// 	std::ifstream	file (filename.c_str());
// 	std::string		delimiter = "|";
// 	size_t i = 0;
// 	char *pEnd;
	
// 	if (!file.is_open()) {
// 		file.close();
// 		throw (BitcoinExchange::WrongFile());
// 	}
// 	else {
// 		while (getline(file, line)) {
// 			if (line == "date | value")
// 				continue ;
// 			if (line.find(delimiter) == line.npos)
// 				throw (BitcoinExchange::WrongSyntax());
// 			std::cout << line << std::endl;
// 			i = line.find(delimiter);
// 			std::string token1 = line.substr(0, i);
// 			std::cout << "[" << token1 << "]" << std::endl;
// 			std::string token2 = line.substr(i + 1, *line.end() - i);
// 			std::cout << "[" << token2 << "]" << std::endl;
// 			_m[token1] = std::strtod(token2.c_str(), &pEnd);
// 			std::cout << _m[token1] << std::endl;
// 			std::cout << _m.begin()->first << std::endl;
// 			std::cout << std::endl;
// 			std::cout << std::endl;
// 		}
// 	}
// 	std::cout << std::endl;
// 	std::cout << std::endl;
// 	printInputs();
// 	file.close();
// }