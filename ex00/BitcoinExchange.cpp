/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/05/03 21:57:52 by eleotard         ###   ########.fr       */
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
	_m_data = src._m_data;
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
        getline(file, line);
		if (line != "date,exchange_rate")
			throw (BitcoinExchange::WrongDataSyntax());
		while (getline(file, line)) {
			i = line.find(delimiter);
			std::string token1 = line.substr(0, i);
			std::string token2 = line.substr(i + 1, *line.end() - i);
			_m_data[token1] = std::strtod(token2.c_str(), &pEnd);
		}
	}
	file.close();
	_dbState = true;
}

std::map<std::string, double> const&BitcoinExchange::getDatabase() const {
	return (_m_data);
}

bool	BitcoinExchange::getDbState() const {
	return (_dbState);
}

void	BitcoinExchange::printInputs() {
	
	std::map<std::string, double>::iterator it = _m_data.begin();
	std::cout << _m_data.begin()->first << std::endl;
	for (; it != _m_data.end(); ++it) {
		std::cout << BLUE << it->first << " => " << it->second << DEFAULT << '\n';
	}
}

void	BitcoinExchange::checkNbOfArgs(std::string line) {
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
}

void	BitcoinExchange::checkSeparator(std::string line) {
	size_t		i = 0;
	int			j = 0;
	std::string	delimiter = " ";
	std::string	save;

	while (i != std::string::npos && j < 2) {
		i = line.find(delimiter);
		if (i != std::string::npos) {
			save = line.substr(0, i);
			i++;
			line = line.c_str() + i;
		}
		j++;
	}
	if (save != "|")
		throw (BitcoinExchange::WrongGlobalSyntax());
}

void	BitcoinExchange::checkDateSyntax(std::string date) {
	std::string	delimiter = "-";
	std::string input[3];
	size_t		i = 0;
	//size_t		save = 0;
	int			args = 0;
	
	//std::cout << GREEN << "[" << date << "]" <<  DEFAULT << std::endl;
	while (i != std::string::npos)
	{
		// save = i;
		i = date.find("-");
		//std::cout << "date = " << date << std::endl ;
		//std::cout << "i = " << i << std::endl ;
		//std::cout << "save = " << save << std::endl ;
		//std::cout << i - save << std::endl ;
		if (i != std::string::npos && date.c_str()[i + 1] && date.c_str()[i + 1] == '-')
			throw (BitcoinExchange::DateError());
		if (i != std::string::npos && i != 0) {
			if (args > 2)
				throw (BitcoinExchange::DateError());
			input[args] = date.substr(0, i);
			i++;
			date = date.c_str() + i;
		}
		else {
			if (args > 2)
				throw (BitcoinExchange::DateError());
			input[args] = date;
		}
		std::cout << YELLOW << "[" << input[args] << "]" <<  DEFAULT << std::endl;
		args++;
		//std::cout << "args = " << args << std::endl ;
	}
	if (args != 3)
		throw (BitcoinExchange::DateError());
}

void	BitcoinExchange::treatInputFile(std::string const& filename) {
	std::ifstream	file (filename.c_str());
	std::string		line; 
	
	getline(file, line);
	if (line != "date | value")
		throw (BitcoinExchange::WrongGlobalSyntax());
	
	while(getline(file, line)) {
		try {
			checkNbOfArgs(line); //check si ya 3 trucs
			checkSeparator(line);//si la syntaxe globale est respectee
			checkDateSyntax(line.substr(0, line.find(" ")));
			std::cout << line << std::endl;
		}
		catch (std::exception const& e) {
			std::cout << e.what() << std::endl;
		}
		//si la syntaxe de la date est respectee
		//si la date est rationnelle
		//sil ny a pas d'overflow
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
// 			_m_data[token1] = std::strtod(token2.c_str(), &pEnd);
// 			std::cout << _m_data[token1] << std::endl;
// 			std::cout << _m_data.begin()->first << std::endl;
// 			std::cout << std::endl;
// 			std::cout << std::endl;
// 		}
// 	}
// 	std::cout << std::endl;
// 	std::cout << std::endl;
// 	printInputs();
// 	file.close();
// }