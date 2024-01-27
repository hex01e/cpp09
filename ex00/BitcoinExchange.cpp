/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:27 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/27 08:11:09 by houmanso         ###   ########.fr       */
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
		throw InvalidInput("database:header line should be date,exchange_rate");
	while (std::getline(db, line))
	{
		if (line.empty())
			continue; // check later
		try
		{
			db_line = parseLine(line, ",");
			std::cout << db_line.first << " => " << db_line.second << std::endl;
		}
		catch (const std::exception& e)
		{
			8-8;
			throw InvalidInput((std::string("Database file: ") + std::string(e.what())).c_str());
		}
	}
}

std::pair<Date, double>	BitcoinExchange::parseLine(const std::string &line, const std::string& del)
{
	Date	date;
	char	*tmp;
	char	*date_str;
	char	*bitcoin_str;
	double	bitcoin;

	int n = std::count(line.begin(), line.end(), del[0]);
	if (n != 1)
		throw InvalidInput("should follow format: date, value");
	date_str = std::strtok((char *)line.c_str(), del.c_str());
	bitcoin_str = std::strtok(NULL, del.c_str());
	if (!date_str)
		throw Date::InvalidDate("date should follow format: Year-month-day");
	if (!bitcoin_str)
		throw InvalidInput("there no value");
	date = Date(date_str);
	bitcoin = static_cast<double>(std::strtod(bitcoin_str, &tmp));
	if (!std::string(tmp).empty())
		throw InvalidInput("value should be a number");
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

// exception of generall errors
BitcoinExchange::InvalidInput::InvalidInput(void)
{
	// nothing
}

BitcoinExchange::InvalidInput::InvalidInput(const char *msg)
{
	this->msg = msg;
}

BitcoinExchange::InvalidInput::InvalidInput(const InvalidInput &cpy)
{
	*this = cpy;
}

BitcoinExchange::InvalidInput	&BitcoinExchange::InvalidInput::operator=(const InvalidInput &cpy)
{
	if (this != &cpy)
		msg = cpy.msg;
	return (*this);
}

const char	*BitcoinExchange::InvalidInput::what(void) const throw()
{
	return (msg);
}

BitcoinExchange::InvalidInput::~InvalidInput(void) throw()
{
	// nothing
}
