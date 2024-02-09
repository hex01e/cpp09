/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:54 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/08 21:08:01 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <vector>
#include <climits>
#include <iomanip>
#include <iostream>
#include <algorithm>

class PmergeMe
{
	private:
		size_t	jn_1;
		size_t	jn_2;
		double	a_time;
		std::vector<int>	a;


		PmergeMe(void);

		size_t	jacobsthal(void);
		int		getNumber(char *str);
		void	sortContainerA(void);
		void	containerA(char **args);
		void	pairwise(std::vector< std::pair<long, long> > &pairs);
		// void	containerB(const char *args[]);

	public:
		PmergeMe(char **args);
		PmergeMe(const PmergeMe& cpy);

		PmergeMe&	operator=(const PmergeMe& cpy);

		~PmergeMe(void);
};

#endif
