/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/21 14:26:53 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const& src) {*this = src; }

PmergeMe &PmergeMe::operator=(PmergeMe const& src) {
	_main_chain = src._main_chain;
	return (*this);
}

void	printVect(t_vect v) {
	std::vector<int>::iterator it;
	std::vector<int>::iterator ite = v.end();
	for (it = v.begin(); it != ite; it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	printVvect(t_vvect &vect) {
	for (size_t i = 0; i < vect.size(); i++){
		std::cout << "vect[" << i << "] = ";
		printVect(vect[i]);
		std::cout << std::endl;
	}
}

t_vect	PmergeMe::extractMainChainList() {
	t_vect tmp;

	for (size_t i = 0; i < _main_chain.size(); i++) {
		tmp.push_back(_main_chain[i][0]);
	}
	return (tmp);
}

PmergeMe::PmergeMe(char **argv) {
	t_vect sorted_list;
	t_vect initial_vect;
	
	setJacobNbs();
	printJacobNbs();

	initial_vect = setVector(argv);
	// std::cout << GREEN << std::endl;
	// printVect(initial_vect);
	// std::cout << DEFAULT <<std::endl;
	merge_insert(initial_vect);

	sorted_list = extractMainChainList();
	std::cout << GREEN << std::endl;
	printVect(sorted_list);
	std::cout << DEFAULT <<std::endl;
}

t_vect	PmergeMe::setVector(char **argv) {
	int		nb;
	t_vect	initial_vect;
	
	for (int i = 1; argv[i]; i++) {
		std::stringstream ss(argv[i]);
		ss >> nb;
		if (ss.fail() || !ss.eof())
			throw (PmergeMe::OOR());
		initial_vect.push_back(nb);
	}
	return (initial_vect);
}

t_vvect PmergeMe::getMainChain() const {
	return (_main_chain);
}


void	PmergeMe::printPvect(p_vect pairs) {
	p_iterator	it;
	p_iterator	ite = pairs.end();

	for (it = pairs.begin(); it != ite; it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << std::endl;
}

void	PmergeMe::printVect(t_vect list) {
	std::vector<int>::iterator	it;
	std::vector<int>::iterator	ite = list.end();

	for (it = list.begin(); it != ite; it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

p_vect	PmergeMe::makePairs(t_vect &list, int *solo) {
	p_vect	pairs;
	
	for (size_t i = 0; i < list.size(); i += 2) {
		if ((i + 1) != list.size())
			pairs.push_back(std::make_pair(list[i], list[i + 1]));
		else
			*solo = list[i];
	}
	return (pairs);
}

void	PmergeMe::sortPairs(p_vect &pairs) {
	p_iterator	it;
	p_iterator	ite = pairs.end();
	int			tmp;

	for (it = pairs.begin(); it != ite; it++) {
		if (it->first < it->second) {
			tmp = it->first;
			it->first = it->second;
			it->second = tmp;
		}
	}
}

t_vect	PmergeMe::createNewList(p_vect &pairs) {
	p_iterator	it;
	p_iterator	ite = pairs.end();
	t_vect		new_list;
	
	for (it = pairs.begin(); it != ite; it++) {
		new_list.push_back(it->first);
	}
	return (new_list);
}

t_vvect	pairsToDoubleVect(p_vect pairs) {
	t_vvect vect;
	t_vect	tmp;
	p_iterator	it;
	p_iterator	ite = pairs.end();
	
	for(it = pairs.begin(); it != ite; it++) {
		tmp.push_back(it->first);
		tmp.push_back(it->second);
		vect.push_back(tmp);
	}

	return (vect);
}

//donne le nombre de la suite jacobsthal associé à l'index envoyé
int	jacobsthalNb(int jIndex) {
	if (jIndex == 0)
		return (0);
	if (jIndex == 1)
		return (1);
	
	int a = 0;
	int b = 1;
	int result;
	int i = 2;

	while (i <= jIndex) {
		result = (2 * a) + b;
		a = b;
		b = result;
		i++;
	}
	return (result);
}

void	PmergeMe::setJacobNbs() {
	int	index = 2;
	while (index < 30) {
		_jacobNbs.push_back(jacobsthalNb(index));
		index++;
	}
}

void	PmergeMe::printJacobNbs() {
	for (size_t i = 0; i < _jacobNbs.size(); i++) {
		std::cout << GREEN << _jacobNbs[i] << " ";
	}
	std::cout << DEFAULT << std::endl;
}

int		PmergeMe::isJacob(int nb) {
	for (size_t i = 0; i < _jacobNbs.size(); i++) {
		if (nb == _jacobNbs[i])
			return (1);
	}
	return (0);
}
	
void	PmergeMe::insertNbInMainChain(int nb, int index) {
	
	int	start = 0;
	int end = index;
	int mid;

	while (start <= end) {
		mid = start + (end - start) / 2;
		if (nb < _main_chain[mid][0]) {
			end = mid - 1;
		}
		else if (nb > _main_chain[mid][0]) {
			start = mid + 1;
		}
		else
			break ;
	}
	_main_chain.insert(_main_chain.begin() + start, createVect(nb, 1));
}

int PmergeMe::findFirstNbPair(p_vect pairs, int first, int indexInMain) {
	p_iterator	it;
	p_iterator	ite = pairs.end();

	for (it = pairs.begin(); it->first != first && it != ite; it++) {
	}
	std::cout << "FT FIND SND: "<< GREEN << it->second << DEFAULT << " PAIRE ASSOCIEE: " << GREEN << it->first << std::endl;
	if (it == ite)
		return (-1);
	_main_chain[indexInMain][1] = 1;
	return (it->second);
}

t_vect	PmergeMe::createVect(int a, int b) {
	t_vect tmp;
	
	tmp.push_back(a);
	tmp.push_back(b);
	return (tmp);
}

void	PmergeMe::resetInsertionState() {
	for (size_t i = 0; i < _main_chain.size(); i++) {
		_main_chain[i][1] = 0;
	}
}

void	PmergeMe::doSort(p_vect pairs, t_vect list, int solo) {
	if (solo == -1 && _main_chain.size() == list.size())
			return ;
	else if (solo != -1 && _main_chain.size() == list.size() - 1)
			return ;
	
	int nbToInsert = 0;
	size_t i = 0;
	for (; i < _main_chain.size(); i++) {
		if (isJacob(i) && _main_chain[i][1] == 0) {
			nbToInsert = findFirstNbPair(pairs, _main_chain[i][0], i);
			insertNbInMainChain(nbToInsert, i);
			std::cout << RED;
			printVvect(_main_chain);
			std::cout << DEFAULT << std::endl;
			doSort(pairs, list, solo);
		}
	}
	if (i == _main_chain.size()) {
		for (i = 0; i < _main_chain.size(); i++) {
			if (_main_chain[i][1] == 0) {
				nbToInsert = findFirstNbPair(pairs, _main_chain[i][0], i);
				insertNbInMainChain(nbToInsert, i);
				std::cout << RED;
				printVvect(_main_chain);
				std::cout << DEFAULT << std::endl;
				doSort(pairs, list, solo);
			}
		}
	}
}

void PmergeMe::merge_insert(t_vect &list) {
	p_vect	pairs;
	t_vect	new_list;
	int		solo = -1;
	
	printVect(list);
	if (list.size() == 1) {
		_main_chain.push_back(createVect(list[0], 1));
		return ;
	}
		
	pairs = makePairs(list, &solo);

	// std::cout << RED << "PAIRS:" << std::endl;
	// printPvect(pairs);
	// std::cout << DEFAULT <<std::endl;
	
	sortPairs(pairs);
	
	// std::cout << BLUE << "SORTED:" << std::endl;
	// printPvect(pairs);
	// std::cout << DEFAULT <<std::endl;
	
	new_list = createNewList(pairs);
	merge_insert(new_list);
		
	/*******************************Insertion***************/	


	resetInsertionState();

	std::cout << DEFAULT << std::endl;
	printPvect(pairs);
	std::cout << RED;
	printVvect(_main_chain);
	std::cout << DEFAULT;
	std::cout << GREEN << "liste: ";
	printVect(list);
	std::cout << DEFAULT;
	

	_main_chain.insert(_main_chain.begin(), createVect(findFirstNbPair(pairs, _main_chain[0][0], 0), 1));
	doSort(pairs, list, solo);
	if (_main_chain.size() == list.size() - 1 && solo != -1) {
		insertNbInMainChain(solo, _main_chain.size() - 1);
		// std::cout << BLUE << "NbTO INSERTTTT: " << solo << DEFAULT << std::endl;
		std::cout << RED;
		printVvect(_main_chain);
		std::cout << DEFAULT << std::endl;
	}
	
	return ;
}


//fonction
	//boucle qui regarde si ya pas un truc JC en revenant a 0 a chaque fois avec un curseur
		//si un index correspond a un nombre jacobsthal et quil est a 0, appairer
		//rechecker
		//si le curseur arrive a la fin sans trouver, quitter la boucle
//renvoie un truc quand elle trouve plus de JC avec un 0 disponible
	
//quand tu trouves pas de JC tu prends le premier qui est a 0 en repartant du debut
//tu recheck la boucle JC
//si tas pas pu retrouver de JC tu remets le premier truc a 0
//tu recheck JC
//etc..
