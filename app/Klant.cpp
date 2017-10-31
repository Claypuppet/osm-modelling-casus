/*
 * Klant.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Klant.h"

namespace Klanten {

Klant::Klant()
: pasNummmer(0)
{
}

Klant::Klant(std::string naam, std::string email, uint32_t pasNummer, std::shared_ptr<AbonnementType>& abbonomentType)
: naam(naam)
, email(email)
, pasNummmer(pasNummer)
, abbonomentType(abbonomentType)
{
}


Klant::~Klant()
{
	// TODO Auto-generated destructor stub
}

}
