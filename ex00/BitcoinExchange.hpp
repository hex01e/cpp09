/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/26 03:49:07 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include "Date.hpp"
#include <fstream>
#include <iostream>

#define DB_FILENAME "data.csv"

class BitcoinExchange
{
	private:
		std::fstream	in;
		std::fstream	db;
		std::map<Date, double>	data;

		BitcoinExchange(void);

		void	processData(void);
		std::pair<Date, double>	parseLine(const std::string& line);

	public:
		BitcoinExchange(const BitcoinExchange& cpy);
		BitcoinExchange(const std::string& inputFile);

		BitcoinExchange&	operator=(const BitcoinExchange& cpy);


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

		~BitcoinExchange(void);
};

#endif
