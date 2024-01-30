/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:06:00 by houmanso          #+#    #+#             */
/*   Updated: 2024/01/29 16:04:29 by houmanso         ###   ########.fr       */
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
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}
