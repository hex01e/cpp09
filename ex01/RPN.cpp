/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:07:46 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/02 20:09:28 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
	// nothing
}

RPN::RPN(std::string arg)
{
	trimAll(arg);
	if (arg.empty())
		throw std::invalid_argument("Error");
	std::cout << arg << std::endl;
}

RPN::RPN(const RPN &cpy)
{
	*this = cpy;
}

RPN	&RPN::operator=(const RPN &cpy)
{
	if (this != &cpy)
		stacky = cpy.stacky;
	return (*this);
}

void	RPN::trimAll(std::string &str)
{
	std::string::iterator	it;
	
	it = str.begin();
	while (it != str.end())
	{
		while (it != str.end() && std::isspace(*it))
			str.erase(it);
		if (it != str.end())
			it++;
	}
}

RPN::~RPN(void)
{
	// nothing
}
