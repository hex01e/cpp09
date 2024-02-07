/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:54 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/07 22:30:32 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <ctime>
#include <vector>
#include <climits>
#include <iomanip>
#include <iostream>

class PmergeMe
{
	private:
		double	a_time;
		std::vector<int>	a;

		PmergeMe(void);

		int		getNumber(char *str);
		void	sortContainerA(void);
		void	containerA(char **args);
		// void	containerB(const char *args[]);

	public:
		PmergeMe(char **args);
		PmergeMe(const PmergeMe& cpy);

		PmergeMe&	operator=(const PmergeMe& cpy);

		~PmergeMe(void);
};

#endif
