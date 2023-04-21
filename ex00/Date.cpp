/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:23:49 by eleotard          #+#    #+#             */
/*   Updated: 2023/04/21 17:17:21 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"

Date::Date() : _day(0), _month(0), _year(0) {
	std::cout << "class Date constructed" << std::endl;
}

Date::Date(int day, int month, int year) : _day(day), _month(month), _year(year) {
	std::cout << "class Date with args constructed" << std::endl;
}

Date::Date(Date const& src) {
	*this = src;
}

Date::~Date() {
	std::cout << "class Date destructed" << std::endl;
}

Date &Date::operator=(Date const& src) {
	setDay(src.getDay());
	setMonth(src.getMonth());
	setYear(src.getYear());
	return (*this);
}

int	Date::getDay() const {
	return (_day);
}

int	Date::getMonth() const {
	return (_month);
}

int	Date::getYear() const {
	return (_year);
}

void Date::setDay(int day) {
	_day = day;
}

void Date::setMonth(int month) {
	_month = month;
}

void Date::setYear(int year) {
	_year = year;
}