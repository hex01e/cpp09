/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:46:36 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/09 15:33:42 by houmanso         ###   ########.fr       */
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

static bool	comp(std::pair<long, long> p1, std::pair<long, long> p2)
{
	return (p1.first < p2.first);
}

size_t	PmergeMe::jacobsthal(void)
{
	size_t jn = jn_1 + 2 * jn_2;
	jn_2 = jn_1;
	jn_1 = jn;
	return (jn);
}

void	PmergeMe::sortContainerA(void)
{
	std::vector<int> Ai;
	std::vector<int> Bi;
	std::vector<int>::iterator pos;
	std::vector< std::pair<long, long> > pairs;

	// get pairs n/2, pairwising them
	pairwise(pairs);
	std::sort(pairs.begin(), pairs.end(), comp);
	// split pairs into two containers
	for (size_t i = 0; i < pairs.size() && pairs[i].first < INT_MAX; i++)
			Ai.push_back(pairs[i].first);
	for (size_t i = 0; i < pairs.size(); i++)
			Bi.push_back(pairs[i].second);
	// insert the 1st element into main chain Ai
	Ai.insert(Ai.begin(), Bi[0]);
	// insert other elements 
	for (size_t i = 0; i < Bi.size(); i++)
	{
		size_t	old_jn_1 = jn_1;
		size_t	jn = jacobsthal();
		if (jn > Bi.size())
			jn = Bi.size();
		size_t	range_size = jn + old_jn_1 - 1;
		for (size_t j = jn - 1; j >= old_jn_1; j--)
		{
			pos = std::lower_bound(Ai.begin(), Ai.begin() + range_size++, Bi[j]);
			Ai.insert(pos, Bi[j]);
			i++;
		}
	}
	a = Ai;
}


void	PmergeMe::pairwise(std::vector< std::pair<long, long> > &pairs)
{
	size_t	i = 0;

	while (i < a.size())
	{
		if (i + 1 < a.size())
		{
			if (a[i] > a[i + 1])
				pairs.push_back(std::pair<long, long>(a[i], a[i + 1]));
			else
				pairs.push_back(std::pair<long, long>(a[i + 1], a[i]));
		}
		else
		{
			pairs.push_back(std::pair<long, long>((long)INT_MAX + 1, a[i]));
			break ;
		}
		i += 2;
	}
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

	jn_1 = 1;
	jn_2 = 1;
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
