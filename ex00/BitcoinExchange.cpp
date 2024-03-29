/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:27 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/02 20:09:49 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	BitcoinExchange::state = false;

BitcoinExchange::BitcoinExchange(void)
{
	// nothing at all
}

void	BitcoinExchange::processData(void)
{
	std::string	line;
	std::pair<Date, double>	db_line;

	size_t nl = 1;
	std::getline(db, line);
	trimAll(line);
	if (line != "date,exchange_rate") // check later
		throw InvalidInput("Database file line 1\t:header line should be date,exchange_rate");
	while (std::getline(db, line))
	{
		try
		{
			nl++;
			if (line.empty())
				throw InvalidInput("empty line");
			db_line = parseLine(line, ",");
			data[db_line.first] = db_line.second;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: Database file line "<< nl << "\t: "<< e.what() << std::endl;
		}
	}
	state = true;
}

double	BitcoinExchange::parseValue(std::string line)
{
	char		*tmp;
	size_t		index;
	double		value;

	trim(line);
	if (line.front() == '.' || line.back() == '.')
		throw InvalidInput("Value is invaled");
	value = std::strtod(line.c_str(), &tmp);
	index = line.find_first_not_of("0123456789.+-");
	if (index != std::string::npos || !std::string(tmp).empty())
		throw InvalidInput("Value is invaled , value should be a number");
	if (value < 0)
		throw InvalidInput("Value is invaled , not a positive value");
	if (value > 1000.0 && state)
		throw InvalidInput("Value is invaled , value should be 0-1000");
	return (value);
}

std::pair<Date, double>	BitcoinExchange::parseLine(std::string &line, const std::string& del)
{
	std::string	err;
	char		*date_str;
	char		*bitcoin_str;

	trim(line);
	if (std::count(line.begin(), line.end(), del[0]) != 1 || line[0] == del[0])
	{
		err = "should follow format: Date ";
		err += del + std::string(" value");
		throw InvalidInput(err.c_str());
	}
	date_str = std::strtok((char *)line.c_str(), del.c_str());
	bitcoin_str = std::strtok(NULL, del.c_str());
	if (!date_str)
		throw InvalidInput("date should follow format: Year-month-day");
	if (!bitcoin_str || line.empty())
		throw InvalidInput("there no value");
	return (std::pair<Date, double>(Date(date_str, *this), parseValue(bitcoin_str)));
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

void	BitcoinExchange::exchange(void)
{
	std::string	line;
	std::pair<Date, double>	db_line;

	size_t	nl = 1;
	std::getline(in, line);
	if (data.size() == 0)
		throw InvalidInput("DataBase is empty");
	trimAll(line);
	if (line != "date|value")
		throw InvalidInput("Input file line 1\t: header line should be date | value");
	while (std::getline(in, line))
	{
		try
		{
			nl++;
			if (line.empty())
				throw InvalidInput("empty line");
			db_line = parseLine(line, "|");
			std::cout << db_line.first << " => " << db_line.second << " = " << db_line.second * getBtc(db_line.first) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: Input file line " << nl << "\t: " << e.what() << std::endl;
		}
	}
}

double	BitcoinExchange::getBtc(Date &date)
{
	std::map<Date, double>::iterator	y;

	y = data.lower_bound(date);
	return (y->first != date && y != data.end() && y != data.begin() ? (--y)->second : y->second);
}

void	BitcoinExchange::trim(std::string &str)
{
	while (str.size() > 0 && std::isspace(str.front()))
		str.erase(str.begin());
	while (str.size() > 0 && std::isspace(str.back()))
		str.pop_back();
}

void	BitcoinExchange::trimAll(std::string &str)
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

std::map<Date, double> &BitcoinExchange::getData(void)
{
	return (data);
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
