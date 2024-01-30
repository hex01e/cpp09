/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:27 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/30 03:18:16 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	// nothing at all
}

void	BitcoinExchange::processData(void)
{
	std::string	err;
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
			std::cout << "Database file: " << e.what() << std::endl;
		}
	}
}

double	BitcoinExchange::parseValue(std::string line)
{
	char		*tmp;
	double		value;
	std::string	ws("\t\r\f ");

	while (line.size() > 0 && ws.find(line.front()) != std::string::npos)
			line.erase(line.front());
	while (line.size() > 0 && ws.find(line.front()) != std::string::npos)
			line.pop_back();
	if (line.front() == '.' || line.back() == '.')
		throw InvalidInput("Value is invaled");
	value = static_cast<double>(std::strtod(line.c_str(), &tmp));
	if (value == static_cast<double>(std::strtod("nan", 0)))
		throw InvalidInput("Value is invaled, nan number is invaled");// non not working
	if (!std::string(tmp).empty())
		throw InvalidInput("Value is invaled , value should be a number");
	return (value);
}

std::pair<Date, double>	BitcoinExchange::parseLine(std::string &line, const std::string& del)
{
	char	*date_str;
	char	*bitcoin_str;

	int n = std::count(line.begin(), line.end(), del[0]);
	if (n != 1)
		throw InvalidInput("should follow format: date, value");
	date_str = std::strtok((char *)line.c_str(), del.c_str());
	bitcoin_str = std::strtok(NULL, del.c_str());
	if (!date_str)
		throw InvalidInput("date should follow format: Year-month-day");
	if (!bitcoin_str)
		throw InvalidInput("there no value");
	return (std::pair<Date, double>(Date(date_str), parseValue(bitcoin_str)));
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
	msg = "Invalid input";
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
