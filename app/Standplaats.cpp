/*
 * Standplaats.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Standplaats.h"

namespace Deelautos {

Standplaats::Standplaats()
: locatie(0)
{
	// TODO Auto-generated constructor stub

}

Standplaats::Standplaats(uint32_t locatie, const std::string& naam)
: locatie(locatie)
, naam(naam)
{
}

bool Standplaats::controlleerLocatie(uint32_t locatie)
{
	return this->locatie == locatie;
}

}
