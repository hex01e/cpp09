/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:46:36 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/07 22:30:20 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	// nothing
}

PmergeMe::PmergeMe(char **args)
{
	a_time = 0;
	containerA(args);
	// containerA(args);
}

PmergeMe::PmergeMe(const PmergeMe &cpy)
{
	*this = cpy;
}

void	PmergeMe::sortContainerA(void)
{
	
}

int PmergeMe::getNumber(char *str)
{
	char	*end;
	long	num;

	end = NULL;
	num = std::strtol(str, &end, 10);
	if (!end || *end)
		throw (std::invalid_argument("invaled number"));
	if (num > INT_MAX)
		throw (std::invalid_argument("number is too large"));
	if (num < 0)
		throw (std::invalid_argument("number is negative"));
	return (num);
}

void PmergeMe::containerA(char **args)
{
	std::clock_t start, end;

	start = std::clock();
	for (size_t i = 0; args[i]; i++)
		a.push_back(getNumber(args[i]));
	sortContainerA();
	end = std::clock();
	a_time = (double)(end - start) / CLOCKS_PER_SEC;
	a_time *= 1e6;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &cpy)
{
	if (this != &cpy)
		return (*this);
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
	// nothing
}
