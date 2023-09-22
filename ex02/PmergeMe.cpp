/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/22 15:49:22 by eleotard         ###   ########.fr       */
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

unsigned long long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long long int)(long long int)now.tv_sec * 1000000
		+ (long long int)now.tv_usec);
}

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

void	PmergeMe::printPdeque(p_deque &pairs) const{
	p_d_iterator	it;
	p_d_iterator	ite = pairs.end();

	for (it = pairs.begin(); it != ite; it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << std::endl;
}

void	PmergeMe::printDeque(t_deque &list) const{
	std::deque<int>::iterator	it;
	std::deque<int>::iterator	ite = list.end();

	for (it = list.begin(); it != ite; it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printDdeque(t_ddeque &deque) const{
	for (size_t i = 0; i < deque.size(); i++){
		std::cout << "deque[" << i << "] = ";
		printDeque(deque[i]);
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
	t_vect initial_vect;
	t_vect sorted_list;
	t_deque d_initial_deque;
	t_deque d_sorted_list;
	unsigned long long int startTime = 0;
	unsigned long long int processTime = 0;
	int n = 0;

	setJacobNbs();
	setPowOfTwoLessOneNbs();
	
	/*vect*/
	initial_vect = setVector(argv);
	std::cout << "Before:" << '\t';
	printVect(initial_vect);
	startTime = get_time();
	merge_insert(initial_vect);
	sorted_list = extractMainChainList();
	processTime = get_time() - startTime;
	std::cout << "After:" << GREEN << '\t';
	printVect(sorted_list);
	std::cout << DEFAULT << "Time to process a range of " << initial_vect.size()
		<< " elements with " << YELLOW << "std::vector" << DEFAULT << ": ";
	std::cout << YELLOW << processTime << DEFAULT << " us" << std::endl << std::endl;

	/*deque*/
	d_initial_deque = setDeque(argv);
	std::cout << "Before:" << '\t';
	printDeque(d_initial_deque);
	startTime = get_time();
	dMerge_insert(d_initial_deque);
	d_sorted_list = dExtractMainChainList();
	processTime = get_time() - startTime;
	std::cout << "After:" << GREEN << '\t';
	printDeque(d_sorted_list);
	std::cout << DEFAULT << "Time to process a range of " << d_initial_deque.size()
		<< " elements with " << YELLOW << "std::deque" << DEFAULT << ": ";
	std::cout << YELLOW << processTime << DEFAULT << " us" << std::endl << std::endl;
	
	/*count of comparaisons*/
	std::cout << "nb of comparaisons: " << GREEN << _count << DEFAULT << std::endl;
	n = initial_vect.size();
	std::cout << "worse case: " << RED << n * log2((n)) << DEFAULT << std::endl;
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
	_main_chain.insert(_main_chain.begin() + start, createVect(nb, 1));
}

int PmergeMe::findFirstNbPair(p_vect &pairs, int first, int indexInMain) {
	p_iterator	it;
	p_iterator	ite = pairs.end();
	int			result;

	for (it = pairs.begin(); it->first != first && it != ite; it++) {
	}
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
			save = i;
			while (save > previousPowOfTwoLessOne(i)) {
				if (_main_chain[save][1] == 0) {
					nbToInsert = findFirstNbPair(pairs, _main_chain[save][0], save);
					insertNbInMainChain(nbToInsert, save);
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
				doSort(pairs, list, solo);
			}
		}
	}
}

void PmergeMe::merge_insert(t_vect &list) {
	p_vect	pairs;
	t_vect	new_list;
	int		solo = -1;

	if (list.size() == 1) {
		_main_chain.push_back(createVect(list[0], 1));
		return ;
	}
	pairs = makePairs(list, &solo);
	sortPairs(pairs);
	new_list = createNewList(pairs);
	merge_insert(new_list);
	
	/*******************************Insertion******************************/
	resetInsertionState();
	_main_chain.insert(_main_chain.begin(),
		createVect(findFirstNbPair(pairs, _main_chain[0][0], 0), 1));
	doSort(pairs, list, solo);
	if (_main_chain.size() == list.size() - 1 && solo != -1) {
		insertNbInMainChain(solo, _main_chain.size() - 1);
	}
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////DEQUE VERSION//////////////////////////////
/////////////////////////////////////////////////////////////////////////////


t_deque	PmergeMe::setDeque(char **argv) {
	int		nb;
	t_deque	initial_deque;

	for (int i = 1; argv[i]; i++) {
		std::stringstream ss(argv[i]);
		ss >> nb;
		if (ss.fail() || !ss.eof())
			throw (PmergeMe::OOR());
		initial_deque.push_back(nb);
	}
	return (initial_deque);
}

t_deque	PmergeMe::dExtractMainChainList() {
	t_deque tmp;

	for (size_t i = 0; i < _dmain_chain.size(); i++) {
		tmp.push_back(_dmain_chain[i][0]);
	}
	return (tmp);
}

/*******************************POWEROFTWOLESSONE********************************/
void	PmergeMe::dSetPowOfTwoLessOneNbs() {
	int	n = 0;
	while (n < 32) {
		_dpowOfTwoLessOneNbs.push_back(powOfTwoLessOneNb(n));
		n++;
	}
}

size_t PmergeMe::dPreviousPowOfTwoLessOne(int nb) {
	t_deque::iterator it;
	t_deque::iterator ite = _dpowOfTwoLessOneNbs.end();
	t_deque::iterator save;

	for (it = _dpowOfTwoLessOneNbs.begin(); it != ite && *it < nb ; it++) {
		save = it;
	}
	return ((size_t)*save);
}

/********************FORD-JOHNSON MERGE-INSERT ALGORITHM***********************/
p_deque	PmergeMe::dMakePairs(t_deque &list, int *solo) {
	p_deque	pairs;

	for (size_t i = 0; i < list.size(); i += 2) {
		if ((i + 1) != list.size())
			pairs.push_back(std::make_pair(list[i], list[i + 1]));
		else
			*solo = list[i];
	}
	return (pairs);
}

void	PmergeMe::dSortPairs(p_deque &pairs) {
	p_d_iterator	it;
	p_d_iterator	ite = pairs.end();
	int				tmp;

	for (it = pairs.begin(); it != ite; it++) {
		if (it->first < it->second) {
			_count++;
			tmp = it->first;
			it->first = it->second;
			it->second = tmp;
		}
	}
}

t_deque	PmergeMe::dCreateNewList(p_deque &pairs) {
	p_d_iterator	it;
	p_d_iterator	ite = pairs.end();
	t_deque			new_list;

	for (it = pairs.begin(); it != ite; it++) {
		new_list.push_back(it->first);
	}
	return (new_list);
}

void	PmergeMe::dResetInsertionState() {
	for (size_t i = 0; i < _dmain_chain.size(); i++) {
		_dmain_chain[i][1] = 0;
	}
}

t_deque	PmergeMe::dCreateDeque(int a, int b) {
	t_deque tmp;

	tmp.push_back(a);
	tmp.push_back(b);
	return (tmp);
}

int		PmergeMe::dIsPowOfTwoLessOneNbs(int nb) {
	for (size_t i = 0; i < _dpowOfTwoLessOneNbs.size(); i++) {
		if (nb == _dpowOfTwoLessOneNbs[i])
			return (1);
	}
	return (0);
}
	
void	PmergeMe::dInsertNbInMainChain(int nb, int index) {
	int start = 0;
    int end = index;
    int mid;

    while (start <= end) {
        mid = start + (end - start) / 2;
        if (nb < _dmain_chain[mid][0]) {
            end = mid - 1;
        }
        else if (nb > _dmain_chain[mid][0]) {
            start = mid + 1;
        }
        else {
            start = mid;
            break;
        }
    }
	_dmain_chain.insert(_dmain_chain.begin() + start, dCreateDeque(nb, 1));
}

int PmergeMe::dFindFirstNbPair(p_deque &pairs, int first, int indexInMain) {
	p_d_iterator	it;
	p_d_iterator	ite = pairs.end();
	int				result;

	for (it = pairs.begin(); it->first != first && it != ite; it++) {
	}
	if (it == ite)
		return (-1);
	_dmain_chain[indexInMain][1] = 1;
	result = it->second;
	pairs.erase(it);
	return (result);
}

void	PmergeMe::dDoSort(p_deque &pairs, t_deque list, int solo) {
	if (solo == -1 && _dmain_chain.size() == list.size())
			return ;
	else if (solo != -1 && _dmain_chain.size() == list.size() - 1)
			return ;

	int nbToInsert = 0;
	size_t i = 0;
	size_t save;
	for (; i < _dmain_chain.size(); i++) {
		if (isPowOfTwoLessOneNbs(i) && _dmain_chain[i][1] == 0) {
			nbToInsert = dFindFirstNbPair(pairs, _dmain_chain[i][0], i);
			dInsertNbInMainChain(nbToInsert, i);
			save = i;
			while (save > previousPowOfTwoLessOne(i)) {
				if (_dmain_chain[save][1] == 0) {
					nbToInsert = dFindFirstNbPair(pairs, _dmain_chain[save][0], save);
					dInsertNbInMainChain(nbToInsert, save);
				}
				save--;
			}
			dDoSort(pairs, list, solo);
		}
	}
	if (i == _dmain_chain.size()) {
		for (i = 0; i < _dmain_chain.size(); i++) {
			if (_dmain_chain[i][1] == 0) {
				nbToInsert = dFindFirstNbPair(pairs, _dmain_chain[i][0], i);
				dInsertNbInMainChain(nbToInsert, i);
				dDoSort(pairs, list, solo);
			}
		}
	}
}

void PmergeMe::dMerge_insert(t_deque &list) {
	p_deque	pairs;
	t_deque	new_list;
	int		solo = -1;

	if (list.size() == 1) {
		_dmain_chain.push_back(dCreateDeque(list[0], 1));
		return ;
	}
	pairs = dMakePairs(list, &solo);
	dSortPairs(pairs);
	new_list = dCreateNewList(pairs);
	dMerge_insert(new_list);
	
	/*******************************Insertion******************************/
	dResetInsertionState();
	_dmain_chain.insert(_dmain_chain.begin(),
		dCreateDeque(dFindFirstNbPair(pairs, _dmain_chain[0][0], 0), 1));
	dDoSort(pairs, list, solo);
	if (_dmain_chain.size() == list.size() - 1 && solo != -1) {
		dInsertNbInMainChain(solo, _dmain_chain.size() - 1);
	}
}

