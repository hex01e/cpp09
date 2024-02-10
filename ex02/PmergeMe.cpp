/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:46:36 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/10 15:53:33 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	// nothing
}

PmergeMe::PmergeMe(char **args)
{
	containerA(args);
	containerB(args);
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
	pairwiseA(pairs);
	std::sort(pairs.begin(), pairs.end(), comp);
	// split pairs into two containers
	for (size_t i = 0; i < pairs.size() && pairs[i].first < INT_MAX; i++)
			Ai.push_back(pairs[i].first);
	for (size_t i = 0; i < pairs.size(); i++)
			Bi.push_back(pairs[i].second);
	// insert the 1st element into main chain Ai
	Ai.insert(Ai.begin(), Bi[0]);
	// insert other elements
	size_t i = 1;
	while (i < Bi.size())
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

void	PmergeMe::sortContainerB(void)
{
	std::deque<int> Ai;
	std::deque<int> Bi;
	std::deque<int>::iterator pos;
	std::deque< std::pair<long, long> > pairs;

	// get pairs n/2, pairwising them
	pairwiseB(pairs);
	std::sort(pairs.begin(), pairs.end(), comp);
	// split pairs into two containers
	for (size_t i = 0; i < pairs.size() && pairs[i].first < INT_MAX; i++)
			Ai.push_back(pairs[i].first);
	for (size_t i = 0; i < pairs.size(); i++)
			Bi.push_back(pairs[i].second);
	// insert the 1st element into main chain Ai
	Ai.insert(Ai.begin(), Bi[0]);
	// insert other elements 
	size_t i = 1;
	while (i < Bi.size())
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
	b = Ai;
}

void	PmergeMe::pairwiseA(std::vector< std::pair<long, long> > &pairs)
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

void	PmergeMe::pairwiseB(std::deque< std::pair<long, long> > &pairs)
{
	size_t	i = 0;

	while (i < b.size())
	{
		if (i + 1 < b.size())
		{
			if (b[i] > b[i + 1])
				pairs.push_back(std::pair<long, long>(b[i], b[i + 1]));
			else
				pairs.push_back(std::pair<long, long>(b[i + 1], b[i]));
		}
		else
		{
			pairs.push_back(std::pair<long, long>((long)INT_MAX + 1, b[i]));
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
	a_old = a;
	sortContainerA();
	end = std::clock();
	a_time = (double)(end - start) / CLOCKS_PER_SEC;
	a_time *= 1e6;
}

void PmergeMe::containerB(char **args)
{
	std::clock_t start, end;

	jn_1 = 1;
	jn_2 = 1;
	start = std::clock();
	for (size_t i = 0; args[i]; i++)
		b.push_back(getNumber(args[i]));
	b_old = b;
	sortContainerB();
	end = std::clock();
	b_time = (double)(end - start) / CLOCKS_PER_SEC;
	b_time *= 1e6;
}

void	PmergeMe::analyze(void)
{
	std::cout << "Before:";
	for (size_t i = 0; i < a_old.size(); i++)
		std::cout << " " << a_old[i];
	std::cout << std::endl;
	std::cout << "After:";
	for (size_t i = 0; i < a.size(); i++)
		std::cout << " " << a[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << a.size();
	std::cout << " elements with std::vector : ";
	std::cout << a_time << " us" << std::endl;
	std::cout << "Time to process a range of " << b.size();
	std::cout << " elements with std::deque : ";
	std::cout << b_time << " us" << std::endl;
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
