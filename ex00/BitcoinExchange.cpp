/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:56:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/21 15:43:04 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	std::cout << "BitcoinExchange constructed" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& src) {
	this = src;
	//std::cout << "BitcoinExchange copy constructed" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {
	std::cout << "BitcoinExchange destructed" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const& src) {
	t
}