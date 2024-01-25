/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/25 01:50:21 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <iostream>

#define DB_FILENAME "data.csv"

class BitcoinExchange
{
	private:
		std::fstream	in;
		std::fstream	db;

		BitcoinExchange(void);
		void	process(void);

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
