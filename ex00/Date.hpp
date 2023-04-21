/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:24:01 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/21 15:36:47 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATE_HPP
# define DAT_HPP

#include <iostream>
#include "BitcoinExchange.hpp"

class BitcoinExchange;

class Date {
	public:
		Date();
		Date(int day, int month, int year);
		Date(Date const& src);
		~Date();
		Date &operator=(Date const& src);
		int	getDay() const;
		int getMonth()const;
		int getYear() const;
		void setDay(int day);
		void setMonth(int month);
		void setYear(int Year);
	private:
		int _day;
		int _month;
		int _year;
};


#endif