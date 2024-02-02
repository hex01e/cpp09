/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:05:46 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/02 17:52:55 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>

class RPN
{
	private:
		std::stack<char>	stacky;
		RPN(void);

	public:
		RPN(const RPN& cpy);
		RPN(std::string arg);

		RPN&	operator=(const RPN& cpy);

		void	trimAll(std::string& str);

		~RPN(void);
};

#endif
