/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:41:25 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/10 19:15:38 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

#include "RPN.hpp"

//peut-etre utiliser le container stack pour cet exo
//pck juste besoin de lacces aux deux element du dessus en permanence
//2*(5+6) => 2 5 6 + *

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

	RPN rpn;
	std::string input(argv[1]);
	std::string result;
	
	result = rpn.calcul(input);
	if (result == "Error")
		std::cerr << result << std::endl;
	else
		std::cout << result << std::endl;
	
	return (0);
}