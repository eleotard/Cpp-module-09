/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:19 by eleotard          #+#    #+#             */
/*   Updated: 2023/09/13 20:14:06 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// vector: conteneur dynamique qui peut être une bonne option pour stocker les
//  données si on connait à l'avance la taille maximale de la liste
//  On peut utiliser std::vector<int> pour stocker les entiers.
// Les vecteurs offrent un accès rapide aux éléments et sont efficaces pour le tri.

int checkList(std::string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (!isdigit(s[i]))
			return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	if (argc <= 1)
		return (std::cerr << "Error: arguments are required." << std::endl, 1);
	for (int i = 1; argv[i]; i++)
	{
		if (!checkList(argv[i]))
			return (std::cerr << "Error: wrong arguments: positive integers asked only. ex:./PmergeMe 3 5 9 7 4" << std::endl, 1);
	}
	
	PmergeMe p;
	try
	{
		p.setVector(argv);
		//p.printVector();
		p.fordJohnson(p.getVectorSize());
		p.printVector();
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}