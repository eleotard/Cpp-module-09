/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:18 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/28 19:49:07 by eleotard         ###   ########.fr       */
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
                    return ("Error: File problem");
                }
        };
        class LargerBcNumber: public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("Error: too large number");
                }
        };
        class LowerBcNumber: public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("Error: not a positive number");
                }
        };
        class DateError: public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("Error: bad input");
                }
        };
        class WrongGlobalSyntax: public std::exception {
            public:
                virtual const char *what() const throw() {
                    return ("Error: wrong global syntax");
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
		std::map<std::string, double> const&getDatabase() const;
        bool    getDbState() const;
        
        void	treatInputFile(std::string const& filename);
        
        void    checkGlobalSyntax(std::string &input);
        void    checkDateSyntax(std::string & date);
        
    private:
        std::map<std::string, double> _m;
        bool _dbState;
};

#endif