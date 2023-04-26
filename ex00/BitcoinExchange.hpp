/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:18 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/26 19:08:37 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include "Date.hpp"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define GREEN	"\033[32m"
# define PURPLE	"\033[35m"
# define DEFAULT	"\033[0m"

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
        class WrongBcValue: public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("Wrong bitcoin value");
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
        
		void	setDatabase(std::string const& filename);
		std::map<std::string, double> &getDatabase() const;
    private:
        std::map<std::string, double> _m;
};

#endif