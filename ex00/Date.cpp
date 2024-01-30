/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:36:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/30 03:33:04 by houmanso         ###   ########.fr       */
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

Date::Date(std::string date_str)
{
	int		ten;
	size_t	tmp;
	char	*token;
	std::string	ws("\t\r\f ");
	std::stringstream	stream;

	tmp = 0;
	date = 0;
	ten = 10000;

	while (date_str.size() > 0 && ws.find(date_str.front()) != std::string::npos)
			date_str.erase(date_str.front());
	while (date_str.size() > 0 && ws.find(date_str.front()) != std::string::npos)
			date_str.pop_back();
	int n = std::count(date_str.begin(), date_str.end(), '-');
	if (n != 2)
		throw BitcoinExchange::InvalidInput("date should follow form Year-Month-Day");
	token = std::strtok((char *)date_str.c_str(), "-");
	if (!token)
		throw  BitcoinExchange::InvalidInput("no date specified");;
	while (token)
	{
		if (!ten)
			throw BitcoinExchange::InvalidInput("date should be Year-Month-Day");
		stream.clear();
		stream << token;
		stream >> tmp;
		date += tmp * ten;
		ten /= 100;
		token = std::strtok(NULL, "-");
	}
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

std::ostream	&operator<<(std::ostream &out, Date &date)
{
	out << date.getDate();
	return (out);
}
