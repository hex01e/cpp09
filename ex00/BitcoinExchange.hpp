/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/02/01 17:13:36 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include "Date.hpp"
#include <fstream>
#include <iostream>

#define DB_FILENAME "data.csv"

class Date;

class BitcoinExchange
{
	private:
		std::fstream	in;
		std::fstream	db;
		std::map<Date, double>	data;

		BitcoinExchange(void);

		void	processData(void);
		double	parseValue(std::string line);
		std::pair<Date, double>	parseLine(std::string& line, const std::string& del);

	public:
		static bool		state;
		BitcoinExchange(const BitcoinExchange& cpy);
		BitcoinExchange(const std::string& inputFile);

		BitcoinExchange&	operator=(const BitcoinExchange& cpy);

		void		exchange(void);
		double		getBtc(Date& date);
		static void	trim(std::string& str);

		std::map<Date, double>&	getData(void);

		class OpenFileFailed: public std::exception
		{
			private:
				const char	*msg;
			public:
				OpenFileFailed(void);
				OpenFileFailed(const char *msg);
				OpenFileFailed(const OpenFileFailed& cpy);

				OpenFileFailed&	operator=(const OpenFileFailed& cpy);

				const char	*what(void) const throw();

				~OpenFileFailed(void) throw();
		};

		class InvalidInput: public std::exception
		{
			private:
				const char	*msg;
			public:
				InvalidInput(void);
				InvalidInput(const char *msg);
				InvalidInput(const InvalidInput& cpy);
		
				InvalidInput&	operator=(const InvalidInput& cpy);
		
				const char	*what(void) const throw();
		
				~InvalidInput(void) throw();
		};

		~BitcoinExchange(void);
};


#endif
