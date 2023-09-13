/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:15 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/13 20:45:32 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _impair(false), _saveLast(0) {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const& src) {*this = src; }

PmergeMe &PmergeMe::operator=(PmergeMe const& src) {
	_vect = src._vect;
	return (*this);
}

void	PmergeMe::printVector() {
	for (size_t i = 0; i < _vect.size(); i++) {
		std::cout << BLUE << _vect[i] << DEFAULT << std::endl;
	}
	std::cout << std::endl;
}

bool	PmergeMe::IsPowerOfTwo(int nb) {
	if ((nb & (nb - 1)) == 0)
		return true;
	return false;
}

void	PmergeMe::makeVectSizePowerOfTwo() {
	while ((_vect.size() & (_vect.size() - 1)) != 0) {
		_vect.push_back(INT_MAX);
	}
}

void	PmergeMe::setVector(char **argv) {
	int	nb;
	for (int i = 1; argv[i]; i++) {
		std::stringstream ss(argv[i]);
		ss >> nb;
		if (ss.fail() || !ss.eof())
			throw (PmergeMe::OOR());
		_vect.push_back(nb);
	}
	_initialSize = _vect.size();
	if (!IsPowerOfTwo(_vect.size())) {
		std::cout << "is not power of two" << std::endl;
		makeVectSizePowerOfTwo();
	}
}

// void	PmergeMe::setImpair() {
// 	if (_vect.size() % 2 == 1) {
// 		_saveLast = _vect.back();
// 		_vect.pop_back();
// 		_impair = true;
// 		std::cout << _saveLast << std::endl;
// 	}
// }

std::vector<int> &PmergeMe::getVector() {
	return (_vect);
}

size_t	PmergeMe::getVectorSize() const{
	return (_vect.size());
}

void	PmergeMe::fordJohnson(size_t size) {
	int	tmp;
	size_t mid = size / 2;
	std::cout << RED << size << DEFAULT << std::endl;
	size_t j = 0;
	for (size_t i = 0; i < mid; i++) {
		std::cout << "Comparaison entre " << _vect[i] << " et " << _vect[mid + j] << std::endl;
		if (_vect[i] > _vect[mid + j]) {
			tmp = _vect[i];
			_vect[i] = _vect[mid + j];
			_vect[mid + j] = tmp;
		}
		j++;
	}
	printVector();
	// size_t halfSize = _vect.size() / 2;
	// _vect.erase(_vect.begin() + halfSize, _vect.end());
	// if (_vect.size() <= 1)
	// 	return ;
	if (size <= 1)
		return ;
	std::cout << "Passe" << std::endl;
	fordJohnson(size / 2);
}

