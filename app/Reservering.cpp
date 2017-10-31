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
#include "RedCarsContext.h"
#include "Signals.h"

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

Reservering::Reservering(uint32_t beginMoment, uint32_t eindMoment, std::shared_ptr<Klant>& klant,
		std::shared_ptr<Deelauto>& deelauto, tarieven::TariefSoortPtr tariefSoort)
: beginMoment(beginMoment)
, eindMoment(eindMoment)
, klant(klant)
, deelauto(deelauto)
, tariefSoort(tariefSoort)
, verhuur(nullptr)
{
	if(!klant)
		throw std::logic_error("Reservering moet tot een klant behoren");
	if(!deelauto)
		throw std::logic_error("Reservering moet aan deelauto gekoppelt zijn");
	if(!tariefSoort)
		throw std::logic_error("Reservering moet een tariefsoort bevatten");
}

std::shared_ptr<Verhuur> Reservering::verzilveren()
{
	if(verhuur) {
		Signals::i().VehuurWasAlIngecheckt(verhuur);
		return nullptr;
	}


	verhuur = Verhuur::Create(std::static_pointer_cast<Reservering>(shared_from_this()), Application::getNowMoment());
	RedCarsContext::getInstance().getVehuurRepo().save(verhuur);

	Signals::i().VehuurIngecheckt(verhuur);

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

	auto repo = RedCarsContext::getInstance().getTariefRepo();

	tarieven::TariefPtr tarief = repo.getTariefByTypes(autoType, aboType);

	if(!tarief)
		throw std::logic_error("Geen tarief voor deze combinatie!");

	return tarief;
}

uint32_t Reservering::getTariefSoortPeriodeAantal()
{
	uint32_t timeDelta = eindMoment - beginMoment;
	uint32_t betalingPer = tariefSoort->periode;
	return (timeDelta / betalingPer) + (timeDelta % betalingPer ? 1 : 0);
}

Geld Reservering::getKosten()
{
	tarieven::TariefPtr t = getTarief();
	uint32_t aantal = getTariefSoortPeriodeAantal();
	uint32_t kilometers = verhuur  ? verhuur->aantalKilometers : 0;
	return t->berekenKosten(kilometers, tariefSoort, aantal);
}

std::string Reservering::asString()
{
	return "hier komt reservering string";
}
