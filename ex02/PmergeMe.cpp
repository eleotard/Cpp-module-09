/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/16 20:32:30 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const& src) {*this = src; }

PmergeMe &PmergeMe::operator=(PmergeMe const& src) {
	_vect = src._vect;
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

// PmergeMe::PmergeMe(char **argv) : _impair(false), _saveLast(0) {
// 	std::vector<std::vector<int> > pairs;
// 	setVector(argv); //set cont
// 	pairs = splitVect(_vect, pairs);
// 	pairs = sortEachPair(pairs);
// 	printPairs(pairs);
// }

PmergeMe::PmergeMe(char **argv) : _impair(false), _saveLast(0) {
	t_vect sorted_list; 
	setVector(argv);
	
	std::cout << GREEN << std::endl;
	printVvect(getVect());
	std::cout << std::endl;
	
	sortPairs(getVect());
	
	std::cout << RED << std::endl;
	printVvect(getVect());
	std::cout << std::endl;
	
	sorted_list = merge_insert(getVect());

}

void	PmergeMe::setVector(char **argv) {
	int	nb;
	for (int i = 1; argv[i]; i++) {
		std::stringstream ss(argv[i]);
		ss >> nb;
		if (ss.fail() || !ss.eof())
			throw (PmergeMe::OOR());
		_vect.push_back(std::vector<int>(1, nb));
	}
}


t_vvect &PmergeMe::getVect() {
	return (_vect);
}



int PmergeMe::makePairs(t_vvect &vect) {
	for (size_t i = 0; i < vect.size(); i++) {
		t_vect &cur(vect[i]);
		if ((i + 1) < vect.size()) {
			t_vect next(vect[i + 1]);
			cur.insert(cur.end(), next.begin(), next.end());
			vect.erase(vect.begin() + i + 1);
			//printVect(cur);
		}
		else {
			//printVvect(vect);
			return (1);
		}
	}
		//printVvect(vect);
		return (0);
}

void	PmergeMe::sortPairs(t_vvect &vect) {
	for (size_t i = 0; i < vect.size(); i += 2) {
		if (i < vect.size() - 1) {
			if (vect[i][0] > vect[i + 1][0]) {
				std::cout << "passe a i = " << i << std::endl;
				// t_vect tmp(vect[i]);
				// vect[i].clear();
				// vect[i] = vect[i + 1];
				// vect[i + 1].clear();
				// vect[i + 1] = tmp;
				vect[i].swap(vect[i + 1]);
				}
			}
	}
}


std::vector<int> PmergeMe::merge_insert(t_vvect &vect) {
	std::vector<int> v(2, 100);
	std::vector<int> staddler;
	
	if (makePairs(vect) == 1) {
		staddler = vect.back();
		vect.pop_back();
	}
	
	std::cout << YELLOW << std::endl;
	printVvect(vect);
	std::cout << std::endl;
	
	sortPairs(vect);
	
	std::cout << BLUE << std::endl;
	printVvect(vect);
	std::cout << std::endl;
	
	if (vect.size() <= 1)
		return (v);
	merge_insert(vect);
	return (v);
}























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