/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:07:46 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/02 22:46:42 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
	// nothing
}

RPN::RPN(std::string arg)
{
	std::string::iterator	it;
	trimAll(arg);
	if (arg.empty())
		throw std::invalid_argument("Error");
	else if (arg.find_first_not_of("0123456789+-*/") != std::string::npos)
		throw std::invalid_argument("Error");
	it = arg.begin();
	while (it != arg.end())
	{
		if (std::isdigit(*it))
			stacky.push(*it - '0');
		else
			calc(*it);
		it++;
	}
	if (stacky.size() != 1)
		throw std::invalid_argument("Error");
	std::cout << stacky.top() << std::endl;
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

void	RPN::calc(char op)
{
	long		result;
	int		a, b;

	result = 0;
	if (stacky.size() < 2)
		throw (std::invalid_argument("Error"));
	b = stacky.top();
	stacky.pop();
	a = stacky.top();
	stacky.pop();
	switch (op)
	{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			if (!b)
				throw std::invalid_argument("cant devide by 0");
			result = a / b;
			break;
		default:
			throw std::invalid_argument("error"); // fake protection 
	}
	stacky.push(result);
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
