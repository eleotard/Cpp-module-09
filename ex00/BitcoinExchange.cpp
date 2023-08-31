/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/08/31 15:23:03 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "BitcoinExchange.hpp"
#include <unistd.h>
#include <limits.h>
#include <sstream>
#include <iomanip>

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
	size_t			i = 0;
	float			nb = 0;
	
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
			//std::cout << BLUE << token2 << DEFAULT << '\n';
			std::stringstream ss(token2);
			ss >> nb;
			//std::cout << std::setprecision(2) << std::fixed << YELLOW << nb << DEFAULT << '\n';
			_m_data[token1] = nb;
		}
	}
	file.close();
	//printInputs();
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
		std::cout << BLUE << it->first << " => "
			<< std::setprecision(2) << std::fixed << it->second << DEFAULT << '\n';
	}
}

// void	BitcoinExchange::checkNbOfArgs(std::string line) {
// 	size_t		i = 0;
// 	int			args = 0;
// 	std::string delimiter = " ";
// 	std::string save(line);
	
// 	while (i != std::string::npos)
// 	{
// 		//std::cout << YELLOW << "[" << line << "]" << DEFAULT << std::endl;
// 		i = line.find(delimiter);
// 		//std::cout << i << std::endl;
// 		if (i != std::string::npos) {
// 			i++;
// 			line = line.c_str() + i;
// 		}
// 		args++;
// 	}
// 	//std::cout << GREEN << args << DEFAULT << std::endl;
// 	if (args != 3)
// 		throw (BitcoinExchange::WrongGlobalSyntax());
// }

// void	BitcoinExchange::checkSeparator(std::string line) {
// 	size_t		i = 0;
// 	int			j = 0;
// 	std::string	delimiter = " ";
// 	std::string	save;

// 	while (i != std::string::npos && j < 2) {
// 		i = line.find(delimiter);
// 		if (i != std::string::npos) {
// 			save = line.substr(0, i);
// 			i++;
// 			line = line.c_str() + i;
// 		}
// 		j++;
// 	}
// 	if (save != "|")
// 		throw (BitcoinExchange::WrongGlobalSyntax());
// }

// void	BitcoinExchange::checkDateSyntax(std::string date) {
// 	std::string	delimiter = "-";
// 	std::string input[3];
// 	size_t		i = 0;
// 	//size_t		save = 0;
// 	int			args = 0;
	
// 	//std::cout << GREEN << "[" << date << "]" <<  DEFAULT << std::endl;
// 	while (i != std::string::npos)
// 	{
// 		// save = i;
// 		i = date.find("-");
// 		//std::cout << "date = " << date << std::endl ;
// 		//std::cout << "i = " << i << std::endl ;
// 		//std::cout << "save = " << save << std::endl ;
// 		//std::cout << i - save << std::endl ;
// 		if (i != std::string::npos && date.c_str()[i + 1] && date.c_str()[i + 1] == '-')
// 			throw (BitcoinExchange::DateError());
// 		if (i != std::string::npos && i != 0) {
// 			if (args > 2)
// 				throw (BitcoinExchange::DateError());
// 			input[args] = date.substr(0, i);
// 			i++;
// 			date = date.c_str() + i;
// 		}
// 		else {
// 			if (args > 2)
// 				throw (BitcoinExchange::DateError());
// 			input[args] = date;
// 		}
// 		std::cout << YELLOW << "[" << input[args] << "]" <<  DEFAULT << std::endl;
// 		args++;
// 		//std::cout << "args = " << args << std::endl ;
// 	}
// 	if (args != 3)
// 		throw (BitcoinExchange::DateError());
// }

bool isInt(std::string const& part, int start, int end) {
	size_t		 i = 0;
	std::string	str = part.substr(start, end);
	
	while (i < str.length()) {
		if (!std::isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

bool isDouble(std::string const& part) {
	std::stringstream ss(part);
	double nb = 0;
	
	ss >> nb;
	if (ss.fail() || !ss.eof())
		return false;
	if (nb > INT_MAX)
		throw (BitcoinExchange::LargeNb());
	else if (nb < 0)
		throw (BitcoinExchange::NegativeNb());
	return true;
}

void	BitcoinExchange::globalCheck(std::string line, std::string const& delimiter) {
	size_t		delimiterPos = line.find(delimiter);
	
	if (delimiterPos != 11)
		throw (BitcoinExchange::WrongGlobalSyntax());

	std::string	fstPart(line, 0, delimiterPos + 2);
	if (fstPart[4] != '-' || fstPart[7] != '-')
		throw (BitcoinExchange::WrongGlobalSyntax());
	if (fstPart[10] != ' ' || fstPart[12] != ' ')
		throw (BitcoinExchange::WrongGlobalSyntax());
	if (!isInt(fstPart, 0, 4) || !isInt(fstPart, 5, 2)
		|| !isInt(fstPart, 8, 2))
		throw (BitcoinExchange::WrongGlobalSyntax());
		
	std::string	lstPart(line, delimiterPos + 2, line.length() - delimiterPos + 2);
	if (!isDouble(lstPart))
		throw (BitcoinExchange::WrongGlobalSyntax());
	
	//std::cout << "[" << lstPart << "]" << std::endl;
}

void	BitcoinExchange::dateCheck(std::string date) {
	std::string year(date, 0, 4);
	std::string month(date, 5, 2);
	std::string day(date, 8, 2);
	// std::cout << "[" << year << "]" << std::endl;
	// std::cout << "[" << month << "]" << std::endl;
	// std::cout << "[" << day << "]" << std::endl;
}	

void	BitcoinExchange::treatInputFile(std::string const& filename) {
	std::ifstream	file (filename.c_str());
	std::string		line; 

	getline(file, line);
	if (line != "date | value")
		throw (BitcoinExchange::WrongGlobalSyntax());
	
	while(getline(file, line)) {
		try {
			// checkNbOfArgs(line); //check si ya 3 trucs
			// checkSeparator(line);//si la syntaxe globale est respectee
			// checkDateSyntax(line.substr(0, line.find(" ")));
			globalCheck(line, "|");
			// std::string date(line, 0, 10);
			// std::cout << "[" << date << "]" << std::endl;
			// dateCheck(date);
			std::cout << line << std::endl;
		}
		catch (std::exception const& e) {
			std::cout << e.what() << std::endl;
		}
		//si la syntaxe de la date est respectee
		//si la date est rationnelle
		//sil ny a pas d'overflow
		//chercher le truc attribue et le ressortir
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