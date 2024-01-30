/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:35:21 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/30 03:18:33 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATE_HPP
#define DATE_HPP

#include <sstream>
#include <iostream>
#include "BitcoinExchange.hpp"

class Date
{
	private:
		size_t	date;

	public:
		Date(void);
		Date(const Date& cpy);
		Date(std::string date_str);

		Date&	operator=(const Date& cpy);
		bool	operator>(const Date& cpy);
		bool	operator<(const Date& cpy);
		bool	operator==(const Date& cpy);
		bool	operator<=(const Date& cpy);
		bool	operator>=(const Date& cpy);

		size_t	getDate(void) const;

		~Date(void);
};

std::ostream	&operator<<(std::ostream& out, Date &date);

#endif
