/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/20 19:28:28 by eleotard         ###   ########.fr       */
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

// void	printVvect(t_vvect &vect) {
// 	for (size_t i = 0; i < vect.size(); i++){
// 		std::cout << "vect[" << i << "] = ";
// 		printVect(vect[i]);
// 		std::cout << std::endl;
// 	}
// }

PmergeMe::PmergeMe(char **argv) {
	t_vect sorted_list;
	t_vect initial_vect;
	
	initial_vect = setVector(argv);
	
	// std::cout << GREEN << std::endl;
	// printVect(initial_vect);
	// std::cout << DEFAULT <<std::endl;
	
	merge_insert(initial_vect);
	sorted_list = getMainChain();
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

t_vect PmergeMe::getMainChain() const {
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

//sort le nombre de la suite jacobsthal associé à l'index envoyé
size_t	jacobsthalNb(int jIndex) {
	if (jIndex == 0)
		return (0);
	if (jIndex == 1)
		return (1);
	
	size_t a = 0;
	size_t b = 1;
	size_t result;
	int i = 2;

	while (i <= jIndex) {
		result = (2 * a) + b;
		a = b;
		b = result;
		i++;
	}
	return (result);
}



// void	PmergeMe::insertionDichotomy(int nbtoInsert) {
// 	int size = _main_chain.size();

	
void	PmergeMe::insertNbInMainChain(int nb, int index) {
	
	int	start = 0;
	int end = index;
	int mid;

	while (start <= end) {
		mid = start + (end - start) / 2;
		if (nb < _main_chain[mid]) {
			end = mid - 1;
		}
		else if (nb > _main_chain[mid]) {
			start = mid + 1;
		}
		else
			break ;
	}
	// if (nb < _main_chain[start])
	// 	_main_chain.insert(_main_chain.begin() + (start - 1), nb);
	// else if (nb >= _main_chain[start])
		_main_chain.insert(_main_chain.begin() + start, nb);
}

int	findFirstNbPair(p_vect pairs, int first) {
	p_iterator	it;
	p_iterator	ite = pairs.end();

	for (it = pairs.begin(); it->first != first && it != ite; it++) {
	}
	std::cout << "FT FIND SND: "<< GREEN << it->second << std::endl;
	if (it == ite)
		return (-1);
	return (it->second);
}

void PmergeMe::merge_insert(t_vect &list) {
	p_vect	pairs;
	t_vect	new_list;
	int		solo = -1;
	
	printVect(list);
	if (list.size() == 1) {
		_main_chain.push_back(list[0]);
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
	//->>>>>>>>>>>>>>//if (solo != -1)
	
	//en gros faut que je déploie le resultat dans la main chain
	//et apres je garde acces aux paires dans larecursivite pour
	//pouvoir continuer a la deployer pour le tour d'apres
	
	//t_vvect vect;

	//LE PREMIER A METTRE DS LA MAIN CHAIN
	std::cout << RED;
	printVect(_main_chain);
	std::cout << DEFAULT << std::endl;
	printPvect(pairs);
	_main_chain.insert(_main_chain.begin(), findFirstNbPair(pairs, _main_chain[0]));
	//std::cout << BLUE << "1srt Nbtoinsert: " << findFirstNbPair(pairs, _main_chain[0]) << DEFAULT << std::endl;
	std::cout << RED;
	printVect(_main_chain);
	std::cout << DEFAULT << std::endl;
	// if (findFirstNbPair(pairs, _main_chain[0]) == -1 && solo != -1) {
	// 	insertNbInMainChain(solo, _main_chain.size() - 1);
	// 	return ;
	// }
	// else if (findFirstNbPair(pairs, _main_chain[0]) == -1 && solo == -1)
	// 	return ;
		
	int js_index = 2;
	size_t i = 0;
	size_t j = 0;
	size_t	save = 0;
	size_t	stop = 0;
	int	nbToInsert = 0;
	if (solo == -1) {
		while (_main_chain.size() != list.size() && i < _main_chain.size() && stop < _main_chain.size()) {
			js_index++;
			if (jacobsthalNb(js_index) >= _main_chain.size()) {
				std::cout << BLUE << "passe jn > s " << jacobsthalNb(js_index) << DEFAULT << std::endl;
				std::cout << BLUE << "stop  = " << stop << DEFAULT << std::endl;
				nbToInsert = findFirstNbPair(pairs, _main_chain[stop]);
				if (nbToInsert != -1)
					insertNbInMainChain(nbToInsert, stop);
				// else 
				// 	break ;
				std::cout << RED;
				printVect(_main_chain);
				std::cout << DEFAULT << std::endl;
				stop++;
			}
			else {
				std::cout << BLUE << "passe jn < s " << jacobsthalNb(js_index) << DEFAULT << std::endl;
				save = i;
				while (i < jacobsthalNb(js_index))
					i++;
				stop = i;
				nbToInsert = findFirstNbPair(pairs, _main_chain[i]); // <=> _main_chain[jacobsthalNb(js_index)]
				//std::cout << BLUE << "Nbtoinsert: " << nbToInsert << DEFAULT << std::endl;
				if (nbToInsert != -1)
					insertNbInMainChain(nbToInsert, i);
				// else 
				// 	break ;
				std::cout << RED;
				printVect(_main_chain);
				std::cout << DEFAULT << std::endl;
				j = i;
				while (j < save) {
					nbToInsert = findFirstNbPair(pairs, _main_chain[j]);
					//std::cout << BLUE << "Nbtoinsert: " << nbToInsert << DEFAULT << std::endl;
					if (nbToInsert != -1)
						insertNbInMainChain(nbToInsert, j);
					else 
						break ;
					std::cout << RED;
					printVect(_main_chain);
					std::cout << DEFAULT << std::endl;
					j--;
				}
			}
		}
	}
	else {
		if (_main_chain.size() == list.size() - 1) {
			insertNbInMainChain(solo, _main_chain.size() - 1);
			std::cout << BLUE << "Nbtoinsert: " << solo << DEFAULT << std::endl;
			std::cout << RED;
			printVect(_main_chain);
			std::cout << DEFAULT << std::endl;
			return ;
		}
		while (_main_chain.size() < list.size() && i < _main_chain.size()) {
			js_index++;
			if (jacobsthalNb(js_index) >= _main_chain.size()) {
				std::cout << BLUE << "passe SOLO jn > s " << jacobsthalNb(js_index) << DEFAULT << std::endl;
				nbToInsert = findFirstNbPair(pairs, _main_chain[i]);
				//std::cout << BLUE << "Nbtoinsert: " << nbToInsert << DEFAULT << std::endl;
				if (nbToInsert != -1)
					insertNbInMainChain(nbToInsert, i);
				// else 
				// 	break ;
				std::cout << RED;
				printVect(_main_chain);
				std::cout << DEFAULT << std::endl;
				i++;
			}
			else {
				std::cout << BLUE << "passe SOLO jn < s " << jacobsthalNb(js_index) << DEFAULT << std::endl;
				save = i;
				while (i < jacobsthalNb(js_index))
					i++;
				nbToInsert = findFirstNbPair(pairs, _main_chain[i]); // <=> _main_chain[jacobsthalNb(js_index)]
				//std::cout << BLUE << "Nbtoinsert: " << nbToInsert << DEFAULT << std::endl;
				if (nbToInsert != -1)
					insertNbInMainChain(nbToInsert, i);
				// else 
				// 	break ;
				std::cout << RED;
				printVect(_main_chain);
				std::cout << DEFAULT << std::endl;
				j = i;
				while (j < save) {
					nbToInsert = findFirstNbPair(pairs, _main_chain[j]);
					//std::cout << BLUE << "Nbtoinsert: " << nbToInsert << DEFAULT << std::endl;
					if (nbToInsert != -1)
						insertNbInMainChain(nbToInsert, j);
					else 
						break ;
					std::cout << RED;
					printVect(_main_chain);
					std::cout << DEFAULT << std::endl;
					j--;
				}
			}
		}
		insertNbInMainChain(solo, _main_chain.size() - 1);
		std::cout << BLUE << "Nbtoinsert: " << solo << DEFAULT << std::endl;
		std::cout << RED;
		printVect(_main_chain);
		std::cout << DEFAULT << std::endl;
	}

	std::cout << YELLOW << std::endl;
	printVect(_main_chain);
	std::cout << DEFAULT <<std::endl;
	
	return ;
}
