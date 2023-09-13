/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/13 20:15:21 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits.h>
#include <exception>

# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define GREEN	"\033[32m"
# define RED	"\033[31m"
# define PURPLE	"\033[35m"
# define DEFAULT    "\033[0m"

class PmergeMe {
	public:
		class OOR : public std::exception {
			virtual const char * what() const throw() {
				return ("Error: input out of range (> INT_MAX)");
			}
		};
		PmergeMe();
		~PmergeMe();
		PmergeMe(PmergeMe const& src);
		PmergeMe &operator=(PmergeMe const& src);
		
		void	printVector();
		void	setVector(char **argv);
		bool	IsPowerOfTwo(int nb);
		void	makeVectSizePowerOfTwo();
		void	fordJohnson(size_t size);
	
		std::vector<int> &getVector();
		size_t	getVectorSize() const;
	private:
		void	setImpair();
		std::vector<int>	_vect;
		bool				_impair;
		int					_saveLast;
		int					_initialSize;
};

#endif