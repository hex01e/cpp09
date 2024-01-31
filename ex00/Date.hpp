/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:35:21 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/31 01:10:16 by houmanso         ###   ########.fr       */
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
		size_t	day;
		size_t	year;
		size_t	date;
		size_t	month;

	public:
		Date(void);
		Date(const Date& cpy);
		Date(std::string date_str);

		Date&	operator=(const Date& cpy);
		bool	operator>(const Date& cpy) const;
		bool	operator<(const Date& cpy) const;
		bool	operator==(const Date& cpy) const;
		bool	operator<=(const Date& cpy) const;
		bool	operator>=(const Date& cpy) const;

		size_t	getDay(void) const;
		size_t	getYear(void) const;
		size_t	getDate(void) const;
		size_t	getMonth(void) const;

		void	check_date();

		~Date(void);
};

std::ostream	&operator<<(std::ostream& out, Date &date);

#endif
