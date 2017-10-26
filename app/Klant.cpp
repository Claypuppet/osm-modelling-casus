/*
 * Klant.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Klant.h"

Klant::Klant()
: pasNummmer(0)
{
}

Klant::Klant(uint32_t pasNummer, std::shared_ptr<AbonnementType>& abbonomentType)
: pasNummmer(pasNummer)
, abbonomentType(abbonomentType)
{
}


Klant::~Klant()
{
	// TODO Auto-generated destructor stub
}

