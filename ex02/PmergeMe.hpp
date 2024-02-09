/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:54 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/09 16:04:10 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <deque>
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
		double	b_time;
		std::deque<int>	b;
		std::deque<int>	b_old;
		std::vector<int>	a;
		std::vector<int>	a_old;


		PmergeMe(void);

		size_t	jacobsthal(void);
		int		getNumber(char *str);

		void	sortContainerA(void);
		void	containerA(char **args);
		void	pairwiseA(std::vector< std::pair<long, long> > &pairs);

		void	containerB(char **args);
		void	sortContainerB(void);
		void	pairwiseB(std::deque< std::pair<long, long> > &pairs);

	public:
		PmergeMe(char **args);
		PmergeMe(const PmergeMe& cpy);

		void	analyze(void);

		PmergeMe&	operator=(const PmergeMe& cpy);

		~PmergeMe(void);
};

#endif
