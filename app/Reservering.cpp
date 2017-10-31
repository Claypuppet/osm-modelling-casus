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
		throw std::logic_error("Reservering moet tot een deelauto behoren");
	if(!tariefSoort)
		throw std::logic_error("Reservering moet een tariefsoort bevatten");
}

std::shared_ptr<Verhuur> Reservering::verzilveren()
{
	if(verhuur)
		throw std::logic_error("Reservering is al verzilvert");


	verhuur = Verhuur::Create(std::static_pointer_cast<Reservering>(shared_from_this()), Application::getNowMoment());
	Application::getInstance().getVehuurRepo().save(verhuur);

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

uint32_t Reservering::getTariefSoortPeriodeAantal()
{
	uint32_t timeDelta = eindMoment - beginMoment;
	uint32_t betalingPer = tariefSoort->periode;
	return (timeDelta / betalingPer) + 1;
}

Geld Reservering::getKosten()
{
	tarieven::TariefPtr t = getTarief();
	uint32_t aantal = getTariefSoortPeriodeAantal();
	uint32_t kilometers = verhuur != NULL ? verhuur->aantalKilometers : 0;
	return t->berekenKosten(kilometers, tariefSoort, aantal);
}

std::string Reservering::asString()
{
	return "hier komt reservering string";
}
