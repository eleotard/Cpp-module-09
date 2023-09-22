/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:12 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/22 15:36:07 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits.h>
#include <exception>
#include <cmath>
#include <sys/time.h>

#include <bits/stdc++.h>

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

typedef std::deque<std::deque<int > > t_ddeque;
typedef std::deque<int> t_deque;
typedef std::deque<std::pair<int, int> > p_deque;
typedef std::deque<std::pair<int, int> >::iterator p_d_iterator;

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

		/******************************VECTOR***********************************/
		/*prints*/
		void	printVect(t_vect &list) const;
		void	printVvect(t_vvect &vect)const;
		void	printPvect(p_vect &pairs) const;
		void	printJacobNbs() const;

		/*constructor*/
		t_vect	setVector(char **argv);
		t_vect	extractMainChainList();
		void	setJacobNbs();
		void	setPowOfTwoLessOneNbs();

		/*ford johnson merge-insert algorithm*/
		void	merge_insert(t_vect &list);
		p_vect	makePairs(t_vect &list, int *solo);
		void	sortPairs(p_vect &pairs);
		t_vect	createNewList(p_vect &pairs);
		t_vect	createVect(int a, int b);

		void	resetInsertionState();
		void	doSort(p_vect &pairs, t_vect list, int solo);
		int		isJacob(int nb);
		
		int		isPowOfTwoLessOneNbs(int nb);
		size_t	previousPowOfTwoLessOne(int nb);
		
		int		findFirstNbPair(p_vect &pairs, int first, int indexInMain);
		void	insertNbInMainChain(int nb, int index);

		/*get*/
		t_vvect	getMainChain() const;
		
		/*******************************DEQUE**********************************/
		/*prints*/
		void	printDeque(t_deque &list) const;
		void	printDdeque(t_ddeque &deque)const;
		void	printPdeque(p_deque &pairs) const;

		/*constructor*/
		t_deque	setDeque(char **argv);
		t_deque	dExtractMainChainList();

		/*ford johnson merge-insert algorithm*/
		void	dMerge_insert(t_deque &list);
		p_deque	dMakePairs(t_deque &list, int *solo);
		void	dSortPairs(p_deque &pairs);
		t_deque	dCreateNewList(p_deque &pairs);
		t_deque	dCreateDeque(int a, int b);

		void	dResetInsertionState();
		void	dDoSort(p_deque &pairs, t_deque list, int solo);
		
		int		dFindFirstNbPair(p_deque &pairs, int first, int indexInMain);
		void	dInsertNbInMainChain(int nb, int index);

		int		dIsPowOfTwoLessOneNbs(int nb);
		size_t 	dPreviousPowOfTwoLessOne(int nb);
		void	dSetPowOfTwoLessOneNbs();

		/*get*/
		//t_ddeque	getMainChain() const;

		
	private:
		/******************************VECTOR***********************************/
		t_vvect	_main_chain;
		t_vect	_final_chain;
		t_vect	_jacobNbs;
		t_vect	_powOfTwoLessOneNbs;
		int		_count;
		
		/******************************DEQUE************************************/
		t_ddeque	_dmain_chain;
		t_deque	_dfinal_chain;
		t_deque	_djacobNbs;
		t_deque	_dpowOfTwoLessOneNbs;
};		

#endif