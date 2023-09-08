/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:34:23 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/08 20:52:59 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>

# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define GREEN	"\033[32m"
# define RED	"\033[31m"
# define PURPLE	"\033[35m"
# define DEFAULT    "\033[0m"

class RPN {
	public:
		RPN(std::string const& input);
		RPN(RPN const& src);
		~RPN();
		RPN &operator=(RPN const& src);
		
		class WrongFormat: public std::exception {
			public:
                virtual const char *what() const throw() {
                    return ("Error: wrong RPN input format");
                }
		};
			
		void	setStack(std::stack<int> const& st);
		void	setOp(std::string const& op);
		void	setInput(std::string const& input);
		std::stack<int> getStack(void) const;
		std::string		getOp(void) const;
		std::string		getInput(void) const;
		
		void	checkInputFormat();
		
	private:
		RPN();
		std::stack<int>	_st;
		std::string		_op;
		std::string		_input;
};

#endif