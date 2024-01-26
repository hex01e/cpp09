/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:36:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/26 04:03:08 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"

Date::Date(void)
{
	date = 0;
}

Date::Date(const Date &cpy)
{
	*this = cpy;
}

Date::Date(const std::string &date_str)
{
	int		i;
	char	*token;
	std::stringstream	stream;

	i = 0;
	token = std::strtok((char *)date_str.c_str(), "-");
	if (!token)
		throw (InvalidDate("no date specified"));
	while (token)
	{
		std::cout << token << std::endl;
		token = std::strtok(NULL, "-");
		i++;
	}
	std::cout << i << std::endl;
}

Date	&Date::operator=(const Date &cpy)
{
	if (this != &cpy)
		date = cpy.date;
	return (*this);
}

bool	Date::operator>(const Date &cpy)
{
	return (date > cpy.date ? true : false);
}

bool	Date::operator<(const Date &cpy)
{
	return (date < cpy.date ? true : false);
}

bool	Date::operator==(const Date &cpy)
{
	return (date == cpy.date ? true : false);
}

bool	Date::operator<=(const Date &cpy)
{
	return (date <= cpy.date ? true : false);
}

bool	Date::operator>=(const Date &cpy)
{
	return (date >= cpy.date ? true : false);
}

size_t	Date::getDate(void) const
{
	return (date);
}

Date::~Date(void)
{
	// nothing
}

// Date: Invalid exception

Date::InvalidDate::InvalidDate(void)
{
	msg = "Invalide date";
}

Date::InvalidDate::InvalidDate(const char *msg)
{
	this->msg = msg;
}

Date::InvalidDate::InvalidDate(const InvalidDate &cpy)
{
	*this = cpy;
}

Date::InvalidDate	&Date::InvalidDate::operator=(const InvalidDate &cpy)
{
	if (this != &cpy)
		msg = cpy.msg;
	return (*this);
}

const char	*Date::InvalidDate::what() const throw()
{
	return (msg);
}

Date::InvalidDate::~InvalidDate(void) throw()
{
	// nothing
}

std::ostream	&operator<<(std::ostream &out, Date &date)
{
	out << date.getDate();
	return (out);
}
