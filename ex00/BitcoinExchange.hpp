/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:18 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/21 18:31:23 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include "Date.hpp"

class Date;

class BitcoinExchange {
    public:
        class WrongFile : public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("File problem");
                }
        };
        class WrongSyntax : public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("Wrong syntax in input file");
                }
        };
        BitcoinExchange();
        BitcoinExchange(std::string filename);
        BitcoinExchange(BitcoinExchange const& src);
        ~BitcoinExchange();
        BitcoinExchange &operator=(BitcoinExchange const& src);
        void	recoverInput(std::string const& filename);
        void    checkSyntax();
        void    printInputs();
        
    private:
        std::vector<std::string> _inputs;
        std::map<std::string, float> _m;
};

#endif