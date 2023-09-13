/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/11 18:32:03 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "BitcoinExchange.hpp"
#include <unistd.h>
#include <limits.h>
#include <sstream>
#include <iomanip>

BitcoinExchange::BitcoinExchange() : _dbState(0) {
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& src) {
	*this = src;
}

BitcoinExchange::~BitcoinExchange() {
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
		throw (BitcoinExchange::WrongFile());
	}
	else {
        getline(file, line);
		if (line != "date,exchange_rate" || line.empty() || file.eof()) {
			file.close();
			throw (BitcoinExchange::WrongDataSyntax());}
		while (getline(file, line)) {
			i = line.find(delimiter);
			if (i == std::string::npos) {
				file.close();
				throw (BitcoinExchange::WrongDataSyntax());
			}
			std::string token1 = line.substr(0, i);
			std::string token2 = line.substr(i + 1, *line.end() - i);
			std::stringstream ss(token2);
			ss >> nb;
			_m_data[token1] = nb;
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
	if (nb > 1000)
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
	if (y == 2009 && m == 1 && d == 1)
		throw DateError();
}

double	BitcoinExchange::findResult(std::string const& line) {
	std::string	date(line, 0, 10);
	std::string	amount(line, 13, line.length() - 13);
	std::stringstream	ss(amount);
	double				amountNb = 0;
	double				res = 0;
	std::map<std::string, double>::iterator it;
	std::map<std::string, double>::iterator ite;
	
	ss >> amountNb;
	it = _m_data.begin();
	ite = _m_data.end();
	--ite;
	if (date == it->first)
		return (it->second * amountNb);
	else if (date >= ite->first) {
		return (ite->second * amountNb);
	}
	else {
		while (date >= it->first && it != _m_data.end()) {
			it++;
		}
		--it;
		res = it->second * amountNb;
	}
	return (res);
}

void	BitcoinExchange::treatInputFile(std::string const& filename) {
	std::ifstream	file (filename.c_str());
	std::string		line;
	double			result = 0;

	if (!file.is_open()) {
		throw (BitcoinExchange::WrongFile());
	}
	getline(file, line);
	if (line != "date | value" || line.empty() || file.eof()) {
		file.close();
		throw (BitcoinExchange::WrongGlobalSyntax());}
	
	while(getline(file, line)) {
		try {
			globalCheck(line, "|");
			std::string date(line, 0, 10);
			dateCheck(date);
			result = findResult(line);
			std::string	amount(line, 13, line.length() - 13);
			std::cout << date << " => " << std::setprecision(2)
				<< std::fixed << amount << " = "<< result <<  std::endl;
		}
		catch (std::exception const& e) {
			std::cerr << RED << e.what();
			if ((std::string)e.what() == "Error: bad input"
				|| (std::string)e.what() == "Error: date bad input")
				std::cerr << " => " << line;
			std::cerr << DEFAULT << std::endl;
		}
	}
	file.close();
}
