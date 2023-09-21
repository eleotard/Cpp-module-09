/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/21 20:09:23 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const& src) {*this = src; }

PmergeMe &PmergeMe::operator=(PmergeMe const& src) {
	_main_chain = src._main_chain;
	_final_chain = src._final_chain;
	_jacobNbs = src._jacobNbs;
	return (*this);
}
/*************************************LOGS***********************************/
// double log2Factorial(int n) {
//     double result = 0.0;
//     for (int i = 1; i <= n; ++i) {
//         result += std::log(static_cast<double>(i));
//     }
//     result /= std::log(2.0); // Conversion en logarithme base 2
//     return result;
// }

/*************************************PRINTS***********************************/
void	PmergeMe::printPvect(p_vect &pairs) const{
	p_iterator	it;
	p_iterator	ite = pairs.end();

	for (it = pairs.begin(); it != ite; it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << std::endl;
}

void	PmergeMe::printVect(t_vect &list) const{
	std::vector<int>::iterator	it;
	std::vector<int>::iterator	ite = list.end();

	for (it = list.begin(); it != ite; it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printVvect(t_vvect &vect) const{
	for (size_t i = 0; i < vect.size(); i++){
		std::cout << "vect[" << i << "] = ";
		printVect(vect[i]);
		std::cout << std::endl;
	}
}

void	PmergeMe::printJacobNbs() const{
	for (size_t i = 0; i < _jacobNbs.size(); i++) {
		std::cout << GREEN << _jacobNbs[i] << " ";
	}
	std::cout << DEFAULT << std::endl;
}

/*******************************CONSTRUCTOR_FTS********************************/
PmergeMe::PmergeMe(char **argv) : _count(0) {
	t_vect sorted_list;
	t_vect initial_vect;

	setJacobNbs();
	setPowOfTwoLessOneNbs();

	initial_vect = setVector(argv);
	std::cout << "Before:" << '\t';
	printVect(initial_vect);
	// std::cout << GREEN << std::endl;
	// printVect(initial_vect);
	// std::cout << DEFAULT <<std::endl;
	merge_insert(initial_vect);

	sorted_list = extractMainChainList();
	std::cout << "After:" << '\t';
	printVect(sorted_list);
	// std::cout << GREEN << std::endl;
	// printVect(sorted_list);
	// std::cout << DEFAULT <<std::endl;
	std::cout << "nb of comparaisons: " << _count << std::endl;
	int n = initial_vect.size(); // Remplacez par la valeur de n pour laquelle vous souhaitez calculer log2(n!).
	std::cout << "worse case: " << n * log2((n)) << std::endl;
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

t_vect	PmergeMe::extractMainChainList() {
	t_vect tmp;

	for (size_t i = 0; i < _main_chain.size(); i++) {
		tmp.push_back(_main_chain[i][0]);
	}
	return (tmp);
}

/*******************************JACOBSTHAL********************************/
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

/*******************************POWEROFTWOLESSONE********************************/
//permet de faire des comparaisons optimales
int	powOfTwoLessOneNb(int pIndex) {
	return (std::pow(2, pIndex) - 1);
}

void	PmergeMe::setPowOfTwoLessOneNbs() {
	int	n = 0;
	while (n < 32) {
		_powOfTwoLessOneNbs.push_back(powOfTwoLessOneNb(n));
		n++;
	}
}

size_t PmergeMe::previousPowOfTwoLessOne(int nb) {
	t_vect::iterator it;
	t_vect::iterator ite = _powOfTwoLessOneNbs.end();
	t_vect::iterator save;

	for (it = _powOfTwoLessOneNbs.begin(); it != ite && *it < nb ; it++) {
		save = it;
	}
	return ((size_t)*save);
}

/********************FORD-JOHNSON MERGE-INSERT ALGORITHM***********************/
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
			_count++;
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

void	PmergeMe::resetInsertionState() {
	for (size_t i = 0; i < _main_chain.size(); i++) {
		_main_chain[i][1] = 0;
	}
}

t_vect	PmergeMe::createVect(int a, int b) {
	t_vect tmp;

	tmp.push_back(a);
	tmp.push_back(b);
	return (tmp);
}

int		PmergeMe::isPowOfTwoLessOneNbs(int nb) {
	for (size_t i = 0; i < _powOfTwoLessOneNbs.size(); i++) {
		if (nb == _powOfTwoLessOneNbs[i])
			return (1);
	}
	return (0);
}

int		PmergeMe::isJacob(int nb) {
	for (size_t i = 0; i < _jacobNbs.size(); i++) {
		if (nb == _jacobNbs[i])
			return (1);
	}
	return (0);
}
	
void	PmergeMe::insertNbInMainChain(int nb, int index) {
	int start = 0;
    int end = index;
    int mid;

    while (start <= end) {
        mid = start + (end - start) / 2;
        if (nb < _main_chain[mid][0]) {
            end = mid - 1;
			_count++;
        }
        else if (nb > _main_chain[mid][0]) {
            start = mid + 1;
			_count++;
        }
        else {
			_count++;
            start = mid;
            break;
        }
    }
	//std::cout << YELLOW << "start: " << start << "end: "<< end << DEFAULT << std::endl; 
	_main_chain.insert(_main_chain.begin() + start, createVect(nb, 1));
}

int PmergeMe::findFirstNbPair(p_vect &pairs, int first, int indexInMain) {
	p_iterator	it;
	p_iterator	ite = pairs.end();
	int			result;

	for (it = pairs.begin(); it->first != first && it != ite; it++) {
	}
	//std::cout << "FT FIND SND: "<< GREEN << it->second << DEFAULT << " PAIRE ASSOCIEE: " << GREEN << it->first << std::endl;
	if (it == ite)
		return (-1);
	_main_chain[indexInMain][1] = 1;
	result = it->second;
	pairs.erase(it);
	return (result);
}

void	PmergeMe::doSort(p_vect &pairs, t_vect list, int solo) {
	if (solo == -1 && _main_chain.size() == list.size())
			return ;
	else if (solo != -1 && _main_chain.size() == list.size() - 1)
			return ;

	int nbToInsert = 0;
	size_t i = 0;
	size_t save;
	for (; i < _main_chain.size(); i++) {
		if (isPowOfTwoLessOneNbs(i) && _main_chain[i][1] == 0) {
			nbToInsert = findFirstNbPair(pairs, _main_chain[i][0], i);
			insertNbInMainChain(nbToInsert, i);
			// std::cout << RED;
			// printVvect(_main_chain);
			// std::cout << DEFAULT << std::endl;
			// printPvect(pairs);
			save = i;
			while (save > previousPowOfTwoLessOne(i)) {
				if (_main_chain[save][1] == 0) {
					nbToInsert = findFirstNbPair(pairs, _main_chain[save][0], save);
					insertNbInMainChain(nbToInsert, save);
					// std::cout << RED;
					// printVvect(_main_chain);
					// std::cout << DEFAULT << std::endl;
					// printPvect(pairs);
				}
				save--;
			}
			doSort(pairs, list, solo);
		}
	}
	if (i == _main_chain.size()) {
		for (i = 0; i < _main_chain.size(); i++) {
			if (_main_chain[i][1] == 0) {
				nbToInsert = findFirstNbPair(pairs, _main_chain[i][0], i);
				insertNbInMainChain(nbToInsert, i);
				// std::cout << RED;
				// printVvect(_main_chain);
				// std::cout << DEFAULT << std::endl;
				// printPvect(pairs);
				doSort(pairs, list, solo);
			}
		}
	}
}

void PmergeMe::merge_insert(t_vect &list) {
	p_vect	pairs;
	t_vect	new_list;
	int		solo = -1;

	//printVect(list);
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
	
	/*******************************Insertion******************************/
	resetInsertionState();
	// std::cout << DEFAULT << std::endl;
	// printPvect(pairs);
	// std::cout << RED;
	// printVvect(_main_chain);
	// std::cout << DEFAULT;
	// std::cout << GREEN << "liste: ";
	// printVect(list);
	// std::cout << DEFAULT;

	_main_chain.insert(_main_chain.begin(), createVect(findFirstNbPair(pairs, _main_chain[0][0], 0), 1));
	// std::cout << RED;
	// printVvect(_main_chain);
	// std::cout << DEFAULT << std::endl;
	// printPvect(pairs);
	
	doSort(pairs, list, solo);
	
	if (_main_chain.size() == list.size() - 1 && solo != -1) {
		insertNbInMainChain(solo, _main_chain.size() - 1);
		// std::cout << BLUE << "DERNIER SOLO " << solo << DEFAULT << std::endl;
		// std::cout << RED;
		// printVvect(_main_chain);
		// std::cout << DEFAULT << std::endl;
	}
}
