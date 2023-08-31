/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/08/31 15:50:49 by eleotard         ###   ########.fr       */
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
	std::stringstream ss(year);
	std::stringstream ss1(month);
	std::stringstream ss2(day);
	int y = 0;
	int m = 0;
	int d = 0;

	ss >> y;
	ss1 >> m;
	ss2 >> d;
	if (y > 2022 || y < 2009)
		throw DateError();
	if (m > 12)
		throw DateError();
	if (d > 31)
		throw DateError();
	if ((m == 2 || m == 4 || m == 6 || m == 9 || m == 11)
		&& d == 31)
		throw DateError();
	if ((y == 2012 || y == 2016 || y == 2020) && m == 2) {
		if (d > 29)
			throw DateError();
	}
	else if ((y != 2012 && y != 2016 && y != 2020) && m == 2) {
		if (d > 28)
			throw DateError();
	}
	// std::cout << YELLOW << "[" << year << "]" << std::endl;
	// std::cout << "[" << month << "]" << std::endl;
	// std::cout << "[" << day << "]" << DEFAULT << std::endl;
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
			std::string date(line, 0, 10);
			std::cout << "[" << date << "]" << std::endl;
			dateCheck(date);
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
