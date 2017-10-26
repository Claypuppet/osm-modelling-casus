/*
 * Reservering.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Reservering.h"
#include "Verhuur.h"
#include "Klant.h"
#include "ReserveringRepo.h"

#include <stdexcept>

Reservering::Reservering()
: beginMoment(0)
, eindMoment(0)
, klant(nullptr)
, verhuur(nullptr)
{
}

Reservering::~Reservering()
{
}

Reservering::Reservering(uint32_t beginMoment, uint32_t eindMoment, std::shared_ptr<Klant>& klant)
: beginMoment(beginMoment)
, eindMoment(eindMoment)
, klant(klant)
, verhuur(nullptr)
{
	if(!klant)
		throw std::logic_error("Reservering moet tot een klant behoren");
}

std::shared_ptr<Verhuur> Reservering::verzilveren()
{
	if(verhuur)
		throw std::logic_error("Reservering is al verzilvert");




	return verhuur;
}

bool Reservering::isIngecheckt()
{
	return verhuur != nullptr;
}

tarieven::TariefPtr Reservering::getTarief()
{

	return NULL;
}

Geld Reservering::getKosten()
{
	return Geld(0);
}
