/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/13 17:46:11 by eleotard         ###   ########.fr       */
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
	private:
		std::vector<int> _vect;
};

#endif