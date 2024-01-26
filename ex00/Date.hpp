/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:35:21 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/26 03:59:29 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATE_HPP
#define DATE_HPP

#include <sstream>
#include <iostream>

class Date
{
	private:
		size_t	date;

	public:
		Date(void);
		Date(const Date& cpy);
		Date(const std::string& date_str);

		Date&	operator=(const Date& cpy);
		bool	operator>(const Date& cpy);
		bool	operator<(const Date& cpy);
		bool	operator==(const Date& cpy);
		bool	operator<=(const Date& cpy);
		bool	operator>=(const Date& cpy);

		size_t	getDate(void) const;

		class InvalidDate : public std::exception
		{
			private:
				const char	*msg;
			public:
				InvalidDate(void);
				InvalidDate(const char *msg);
				InvalidDate(const InvalidDate& cpy);
		
				InvalidDate&	operator=(const InvalidDate& cpy);

				const char	*what() const throw();

				~InvalidDate(void) throw();
		};

		~Date(void);
};

std::ostream	&operator<<(std::ostream& out, Date &date);

#endif
