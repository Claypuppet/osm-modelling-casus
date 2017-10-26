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
#include "AutoType.h"
#include "Deelauto.h"
#include "Tarief.h"

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

Reservering::Reservering(uint32_t beginMoment, uint32_t eindMoment, std::shared_ptr<Klant>& klant, std::shared_ptr<Deelauto>& deelauto)
: beginMoment(beginMoment)
, eindMoment(eindMoment)
, klant(klant)
, deelauto(deelauto)
, verhuur(nullptr)
{
	if(!klant)
		throw std::logic_error("Reservering moet tot een klant behoren");
	if(!deelauto)
		throw std::logic_error("Reservering moet tot een deelauto behoren");
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
	std::shared_ptr<AutoType> autoType = deelauto->type;
	std::shared_ptr<AbonnementType> aboType = klant->abbonomentType;

	auto repo = Application::getInstance().getTariefRepo();

	tarieven::TariefPtr tarief = repo.getTariefByTypes(autoType, aboType);

	if(tarief == NULL)
		throw std::logic_error("Geen tarief voor deze combinatie!");

	return tarief;
}

Geld Reservering::getKosten()
{
	return Geld(0);
}
