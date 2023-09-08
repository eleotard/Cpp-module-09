/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:41:25 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/08 20:54:38 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

#include "RPN.hpp"

//peut-etre utiliser le container stack pour cet exo
//pourquoi: éléments en acces contigu dans la memoire
//pratique pour acceder souvent par indices aux elements

//2*(5+6) => 2 5 6 + *
int	recupNb(std::string const& s) {
	std::stringstream	ss;
	int					nb = 0;
	ss << s;
	ss >> nb;
	if (ss.fail() || !ss.eof())
		throw (std::exception());
	return (nb);
}

void	printStack(std::stack<int> st) {
	while (!st.empty()) {
		std::cout << st.top() << std::endl;
		st.pop();
	}
}

std::stack<int> recupData(std::string s){
	std::string::iterator it = s.begin();
	std::string::iterator ite = s.end();
	std::string::iterator tmp = s.begin();
	std::stack<int> st;
	int nb = 0;
	
	while (it != ite) {
		while (*it == ' ' && it != ite)
			it++;
		tmp = it;
		while (*it != ' ' && it != ite)
			it++;
		std::string buff(tmp, it);
		std::cout << "string = " << "[" << buff << "]" << std::endl;
		tmp = it;
		std::stringstream ss;
		ss << buff;
		ss >> nb;
		std::cout << "nb = " << nb << std::endl;
		if (ss.fail() || !ss.eof())
			throw (std::exception());
		st.push(nb);
	}
	return (st);
}





int	CheckCharacters(std::string &s) {
	size_t i;
	
	for (i = 0; i < s.size(); i++) {
		if (!(std::isdigit(s[i])) && s[i] != '+' && s[i] != '-'
			&& s[i] != '*' && s[i] != '/' && s[i] != ' ')
			return (0);
	}
	return (1);
}

int parsGlobalCheck(int argc, char** argv) {
	if (argc == 1) {
		std::cerr << "Error: arguments are required." << std::endl;
		return (1);
	}
	if (argc != 2) {
		std::cerr << "Error: too many arguments." << std::endl;
		return (2);
	}
	std::string data(argv[1]);
	if (data.empty()) {
		std::cerr << "Error: empty argument." << std::endl;
		return (3);
	}
	if (!CheckCharacters(data)) {
		std::cerr << "Error: some caracters are not expected inside the buffer." << std::endl;
		return (4);	
	}
	return (0);
}

int	main(int argc, char **argv) {
	int err = parsGlobalCheck(argc, argv);
	if (err)
		return (err);

	std::string data(argv[1]);
	
	RPN obj(data);
	try
	{
		obj.checkInputFormat();
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	





	
	// RPN obj;
	// try
	// {
	// 	std::stack<int> st;
	// 	st = recupData(data);
	// 	printStack(st);
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	
	return (0);
}