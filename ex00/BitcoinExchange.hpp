/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:10:08 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/25 00:29:13 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <iostream>

class BitcoinExchange
{
	private:
		std::fstream	input;
		std::fstream	database;

		BitcoinExchange(void);

	public:
		BitcoinExchange(const BitcoinExchange& cpy);
		BitcoinExchange(const std::string& inputFile);

		BitcoinExchange&	operator=(const BitcoinExchange& cpy);

		~BitcoinExchange(void);
};

#endif
