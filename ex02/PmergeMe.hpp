/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/20 17:37:31 by eleotard         ###   ########.fr       */
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

typedef std::vector<std::vector<int > > t_vvect;
typedef std::vector<int> t_vect;
typedef std::vector<std::pair<int, int> > p_vect;
typedef std::vector<std::pair<int, int> >::iterator p_iterator;


class PmergeMe {
	public:
		class OOR : public std::exception {
			virtual const char * what() const throw() {
				return ("Error: input out of range (> INT_MAX)");
			}
		};
		PmergeMe();
		PmergeMe(char **argv);
		~PmergeMe();
		PmergeMe(PmergeMe const& src);
		PmergeMe &operator=(PmergeMe const& src);
		
		void	printVect(t_vect list);
		void	printPvect(p_vect pairs);
		
		t_vect	setVector(char **argv);
		void	merge_insert(t_vect &list);
		p_vect	makePairs(t_vect &list, int *solo);
		void	sortPairs(p_vect &pairs);
		t_vect	createNewList(p_vect &pairs);

		void	insertionDichotomy(int nbtoInsert);
		void	insertNbInMainChain(int nb, int index);
		
		t_vect	getMainChain() const;
		
	private:
		t_vect	_main_chain;
};

#endif