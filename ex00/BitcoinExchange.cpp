/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:27 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/26 04:41:14 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	// nothing at all
}

void	BitcoinExchange::processData(void)
{
	std::string	line;
	std::pair<Date, double>	db_line;

	std::getline(db, line);
	if (line != "date,exchange_rate")
		throw (0);
	while (std::getline(db, line))
	{
		db_line = parseLine(line);
		std::cout << db_line.first << " <++> " << db_line.second << std::endl;
	}
}

std::pair<Date, double>	BitcoinExchange::parseLine(const std::string &line)
{
	Date	date;
	char	*date_str;
	char	*bitcoin_str;
	double	bitcoin;

	date_str = std::strtok((char *)line.c_str(), ",");
	bitcoin_str = std::strtok(NULL, ",");
	if (!date_str || !bitcoin_str)
		throw Date::InvalidDate();
	date = Date(date_str);
	bitcoin = static_cast<double>(std::strtod(bitcoin_str, 0));
	return std::pair<Date, double>(date, bitcoin);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy)
{
	*this = cpy;
}

BitcoinExchange::BitcoinExchange(const std::string &inputFile)
{
	in.open(inputFile, std::ios::in);
	if (!in.good())
		throw OpenFileFailed("Failed to open input file");
	db.open(DB_FILENAME, std::ios::in);
	if (!db.good())
		throw OpenFileFailed("Failed to open database file");
	processData();
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &cpy)
{
	if (this != &cpy)
		return (*this);
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	in.close();
	db.close();
}

// BitcoinExchange: nested OpenFileFailed exception class

BitcoinExchange::OpenFileFailed::OpenFileFailed(void)
{
	msg = "Failed to open a file";
}

BitcoinExchange::OpenFileFailed::OpenFileFailed(const char *msg)
{
	this->msg = msg;
}

BitcoinExchange::OpenFileFailed::OpenFileFailed(const OpenFileFailed &cpy)
{
	*this = cpy;
}

BitcoinExchange::OpenFileFailed	&BitcoinExchange::OpenFileFailed::operator=(const OpenFileFailed &cpy)
{
	if (this != &cpy)
		msg = cpy.msg;
	return (*this);
}

const char	*BitcoinExchange::OpenFileFailed::what(void) const throw()
{
	return (msg);
}

BitcoinExchange::OpenFileFailed::~OpenFileFailed(void) throw()
{
	// nothing
}
