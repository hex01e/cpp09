/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:06:00 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/25 11:42:07 by houmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char const *av[])
{
	if (ac != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange	btc(av[1]);
		// btc.exchange();
	}
	catch(const BitcoinExchange::OpenFileFailed& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}
