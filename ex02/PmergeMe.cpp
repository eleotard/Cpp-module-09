/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/19 18:30:15 by eleotard         ###   ########.fr       */
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

void PmergeMe::merge_insert(t_vect &list) {
	p_vect	pairs;
	t_vect	new_list;
	int		solo = -1;
	
	printVect(list);
	if (list.size() == 1)
		return ;
		
	pairs = makePairs(list, &solo);

	std::cout << RED << "PAIRS:" << std::endl;
	printPvect(pairs);
	std::cout << DEFAULT <<std::endl;
	
	sortPairs(pairs);
	
	std::cout << BLUE << "SORTED:" << std::endl;
	printPvect(pairs);
	std::cout << DEFAULT <<std::endl;
	
	new_list = createNewList(pairs);
	merge_insert(new_list);
		
	/*******************************Insertion***************/	
	//->>>>>>>>>>>>>>//if (solo != -1)
	
	
	
	return ;
}



// void	PmergeMe::sortPairs(t_vvect &vect) {
// 	for (size_t i = 0; i < vect.size(); i += 2) {
// 		if (i < vect.size() - 1) {
// 			if (vect[i][0] < vect[i + 1][0]) {
// 				std::cout << "passe a i = " << i << std::endl;
// 				// t_vect tmp(vect[i]);
// 				// vect[i].clear();
// 				// vect[i] = vect[i + 1];
// 				// vect[i + 1].clear();
// 				// vect[i + 1] = tmp;
// 				vect[i].swap(vect[i + 1]);
// 				}
// 			}
// 	}
// }

//suite de Jacobsthal
//binary comparaison

// void	PmergeMe::reMakePairs(t_vvect &vect) {
// 	t_vvect t_tmp;
// 	for (size_t i = 0; i < vect[0].size(); i = i + 2) {
// 			t_vect tmp;
// 			tmp.push_back(vect[0][i]);
// 			tmp.push_back(vect[0][i + 1]);
// 			t_tmp.push_back(tmp);
// 		}
// 		vect = t_tmp;
// }

// void	PmergeMe::insertFirstElement(t_vvect &vect) {
// 	t_vect tmp(1, vect[0][0]);
// 	t_vect second(1, vect[0][1]);
// 	vect.insert(vect.begin(), tmp);
// 	vect[1].swap(second);
// }

// int	isStillPairs(t_vvect &vect) {
// 	for (size_t i = 0; i < vect.size(); i++) {
// 		if (vect[i].size() > 1)
// 			return (1);
// 	}
// 	return (0);
// }

// t_vvect createStaddler(t_vect rest) {
// 	t_vvect result;
// 	for (size_t i = 0; i < rest.size(); i++) {
// 		t_vect tmp(rest[i]);
// 		result.push_back(tmp);
// 	}
// 	return (result);
// }

























// std::vector<std::vector<int> > &PmergeMe::splitVect(std::vector<int> &v, std::vector<std::vector<int> > &pairs) {
// 	std::vector<int>				tmp_vect;

// 	for (size_t i = 0; i < v.size(); i++) {
// 		int	tmpSize = tmp_vect.size();
		
// 		if (tmpSize == 1) {
// 			tmp_vect.push_back(v[i]);
// 			pairs.push_back(tmp_vect);
// 			tmp_vect.clear();
// 		}
// 		else if (pairs.size() * 2 == v.size() - 1) {
// 			std::vector<int> singleValue;
//             singleValue.push_back(v[i]);
//             pairs.push_back(singleValue);
// 		}
// 		else if (tmpSize == 0) {
// 			tmp_vect.push_back(v[i]);
// 		}
// 	}
// 	return (pairs);
// }

// std::vector<std::vector<int> > &PmergeMe::sortEachPair(std::vector<std::vector<int> > & pairs) {
// 	for (size_t i = 0; i < pairs.size(); i++) {
// 		if (pairs[i].size() == 2) {
// 			if (pairs[i][0] > pairs[i][1]) {
// 				int tmp = pairs[i][0];
// 				pairs[i][0] = pairs[i][1];
// 				pairs[i][1] = tmp;
// 			}
// 		}
// 	}
// 	return (pairs);
// }

// void	PmergeMe::printPairs(std::vector<std::vector<int> > &pairs) {
// 	for (size_t i = 0; i < pairs.size(); i++) {
// 		std::vector<int> pair = pairs[i];
// 		std::cout << YELLOW << "{";
// 		for (size_t j = 0; j < pair.size(); j++) {
// 			std::cout << pair[j] << " ";
// 		}
// 		std::cout << "}" << std::endl << DEFAULT << std::endl;
// 	}
// }

// void	PmergeMe::setVector(char **argv) {
// 	int	nb;
// 	for (int i = 1; argv[i]; i++) {
// 		std::stringstream ss(argv[i]);
// 		ss >> nb;
// 		if (ss.fail() || !ss.eof())
// 			throw (PmergeMe::OOR());
// 		_vect.push_back(nb);
// 	}
// 	_initialSize = _vect.size();

	
// 	setImpair();
// 	// if (!IsPowerOfTwo(_vect.size())) {
// 	// 	std::cout << "is not power of two" << std::endl;
// 	// 	makeVectSizePowerOfTwo();
// 	// }
// }

// void	PmergeMe::setImpair() {
// 	if (_vect.size() % 2 == 1) {
// 		_saveLast = _vect.back();
// 		_vect.pop_back();
// 		_impair = true;
// 		std::cout << _saveLast << std::endl;
// 	}
// }

// std::vector<int> &PmergeMe::getVector() {
// 	return (_vect);
// }

// size_t	PmergeMe::getVectorSize() const{
// 	return (_vect.size());
// }

// void	PmergeMe::fordJohnson(size_t size) {
// 	int	tmp;
// 	size_t mid = size / 2;
// 	std::cout << RED << size << DEFAULT << std::endl;
// 	size_t j = 0;
// 	for (size_t i = 0; i < mid; i++) {
// 		std::cout << "Comparaison entre " << _vect[i] << " et " << _vect[mid + j] << std::endl;
// 		if (_vect[i] > _vect[mid + j]) {
// 			tmp = _vect[i];
// 			_vect[i] = _vect[mid + j];
// 			_vect[mid + j] = tmp;
// 		}
// 		j++;
// 	}
// 	printVector();
// 	// size_t halfSize = _vect.size() / 2;
// 	// _vect.erase(_vect.begin() + halfSize, _vect.end());
// 	// if (_vect.size() <= 1)
// 	// 	return ;
// 	if (size <= 1)
// 		return ;
// 	std::cout << "Passe" << std::endl;
// 	fordJohnson(size / 2);
// }

// void	PmergeMe::fordJohnson(size_t size) {
	
// }
// void	PmergeMe::printVector() {
// 	for (size_t i = 0; i < _vect.size(); i++) {
// 		std::cout << BLUE << _vect[i] << DEFAULT << std::endl;
// 	}
// 	std::cout << std::endl;
// }

// bool	PmergeMe::IsPowerOfTwo(int nb) {
// 	if ((nb & (nb - 1)) == 0)
// 		return true;
// 	return false;
// }

// void	PmergeMe::makeVectSizePowerOfTwo() {
// 	while ((_vect.size() & (_vect.size() - 1)) != 0) {
// 		_vect.push_back(INT_MAX);
// 	}
// }