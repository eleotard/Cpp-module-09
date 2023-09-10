/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:34:23 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/10 18:51:57 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <limits.h>

# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define GREEN	"\033[32m"
# define RED	"\033[31m"
# define PURPLE	"\033[35m"
# define DEFAULT    "\033[0m"

class RPN {
	public:
		RPN();
		RPN(RPN const& src);
		~RPN();
		RPN &operator=(RPN const& src);
		
		void	printStack();
		class WrongFormat: public std::exception {
			public:
                virtual const char *what() const throw() {
                    return ("Error: wrong RPN input format");
                }
		};
		
		void	addition();
		void	substraction();
		void	multiplication();
		void	division();
		
		std::string calcul(std::string input);
		
		//void	checkInputFormat();
		
	private:
		std::stack<int>	_st;
};

#endif