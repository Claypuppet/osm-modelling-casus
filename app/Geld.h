/*
 * Geld.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef GELD_H_
#define GELD_H_

#include <stdint.h>
#include <string>

class Geld
{
public:

	Geld()
	: waarde(0)
	{
	}

	Geld(int32_t centen)
	: waarde(centen)
	{
	}

	Geld(int32_t euros, int32_t centen)
	:	waarde(centen + euros*100)
	{
	}

	Geld(const Geld& other)
	: waarde(other.waarde)
	{
	}

	~Geld() = default;

	Geld& operator=(const Geld& other)
	{
		if(&other != this)
			waarde = other.waarde;
		return *this;
	}

	Geld operator+(const Geld& other)
	{
		Geld result(*this);
		result += other;
		return result;
	}

	Geld& operator+=(const Geld& other)
	{
		waarde += other.waarde;
		return *this;
	}

	Geld operator-(const Geld& other)
	{
		Geld result(*this);
		result -= other;
		return result;
	}

	Geld& operator-=(const Geld& other)
	{
		waarde -= other.waarde;
		return *this;
	}


	Geld operator*(int32_t i)
	{
		Geld result(*this);
		result *= i;
		return result;
	}

	Geld& operator*=(int32_t i)
	{
		waarde *= i;
		return *this;
	}

	Geld operator/(int32_t i)
	{
		Geld result(*this);
		result /= i;
		return result;
	}

	Geld& operator/=(int32_t i)
	{
		waarde /= i;
		return *this;
	}

	int32_t getEuros()
	{
		return waarde / 100;
	}

	int32_t getCenten()
	{
		return waarde % 100;
	}

	std::string toString(char seperator=',')
	{
		return std::to_string(getEuros()) + seperator + std::to_string(getCenten());
	}

	explicit operator bool()
	{
		return waarde != 0;
	}

private:
	int32_t waarde;
};

#endif /* GELD_H_ */
