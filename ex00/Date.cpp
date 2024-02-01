/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:36:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/01 17:57:53 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"

Date::Date(void)
{
	day = 0;
	date = 0;
	year = 0;
	month = 0;
}

Date::Date(const Date &cpy)
{
	*this = cpy;
}

Date::Date(std::string date_str, BitcoinExchange& btc)
{
	char	*t;
	int		ten;
	size_t	tmp;
	char	*token;
	std::stringstream	stream;

	tmp = 0;
	date = 0;
	ten = 10000;
	BitcoinExchange::trim(date_str);
	if (std::count(date_str.begin(), date_str.end(), '-') != 2 || date_str[0] == '-')
		throw BitcoinExchange::InvalidInput("date should follow form Year-Month-Day");
	token = std::strtok((char *)date_str.c_str(), "-");
	if (!token)
		throw BitcoinExchange::InvalidInput("no date specified");
	while (token)
	{
		if (!ten)
			throw BitcoinExchange::InvalidInput("date should be Year-Month-Day");
		stream.clear();
		stream.str(token);
		tmp = std::strtoul(token, &t, 10);
		if (tmp > 1844674407370955U)
			throw BitcoinExchange::InvalidInput("year too high!");
		if (!std::string(t).empty())
			throw BitcoinExchange::InvalidInput("date should be Year-Month-Day (some invalid char)");
		date += tmp * ten;
		ten /= 100;
		token = std::strtok(NULL, "-");
		if (token && std::strlen(token) != 2)
			throw BitcoinExchange::InvalidInput("form Year-Month-Day (MM/DD)");
	}
	day = date % 100;
	year = date / 10000;
	month = (date % 10000) / 100;
	check_date(btc);
}

Date	&Date::operator=(const Date &cpy)
{
	if (this != &cpy)
	{
		day = cpy.day;
		year = cpy.year;
		date = cpy.date;
		month = cpy.month;
	}
	return (*this);
}

bool	Date::operator>(const Date &cpy) const
{
	return (date > cpy.date ? true : false);
}

bool	Date::operator<(const Date &cpy) const
{
	return (date < cpy.date ? true : false);
}

bool	Date::operator==(const Date &cpy) const
{
	return (date == cpy.date ? true : false);
}

bool Date::operator!=(const Date &cpy) const
{
	return (date != cpy.date ? true : false);
}

bool	Date::operator<=(const Date &cpy) const
{
	return (date <= cpy.date ? true : false);
}

bool	Date::operator>=(const Date &cpy) const
{
	return (date >= cpy.date ? true : false);
}

size_t	Date::getDay(void) const
{
	return (day);
}

size_t	Date::getYear(void) const
{
	return (year);
}

size_t	Date::getDate(void) const
{
	return (date);
}

size_t	Date::getMonth(void) const
{
	return (month);
}

void	Date::check_date(BitcoinExchange& btc)
{
	std::map<Date, double>	data(btc.getData());

	if (BitcoinExchange::state && data.begin()->first.date > date)
		throw BitcoinExchange::InvalidInput("no data for this date in database");
	if (month > 12 || month == 0)
		throw BitcoinExchange::InvalidInput("month should be 1-12");
	switch (month)
	{
		case 2:
			if ((year % 4 == 0 && year % 100) || year % 400 == 0)
			{
				if (!day || day > 29)
					throw BitcoinExchange::InvalidInput("day should be 1-29");
			}
			else if (!day || day > 28)
				throw BitcoinExchange::InvalidInput("day should be 1-28");
			break;
		case 4: case 6: case 9: case 11:
			if (!day || day > 30)
				throw BitcoinExchange::InvalidInput("day should be 1-30");
			break;
		default:
			if (!day || day > 31)
				throw BitcoinExchange::InvalidInput("day should be 1-31");
			break;
	}
}

Date::~Date(void)
{
	// nothing
}

std::ostream	&operator<<(std::ostream &out, Date &date)
{
	size_t	year, day, month;

	day = date.getDay();
	year = date.getYear();
	month = date.getMonth();
	out << year << "-";
	out << (month < 10 ? "0" : "") << month << "-";
	out << (day < 10 ? "0" : "") << day;
	return (out);
}
