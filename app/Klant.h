/*
 * Klant.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANT_H_
#define KLANT_H_

#include <stdint.h>
#include <initializer_list>

class Klant
{
public:
	Klant() : id(0), pasNummmer(0) {}
	Klant(uint32_t id, uint32_t pasNummer) : id(id), pasNummmer(pasNummer) {}
	~Klant();

	uint32_t getId() const
	{
		return id;
	}

	uint32_t getPasNummmer() const
	{
		return pasNummmer;
	}

	uint32_t id;
	uint32_t pasNummmer;

};

#endif /* KLANT_H_ */
