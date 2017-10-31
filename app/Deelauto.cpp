/*
 * Deelauto.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Deelauto.h"
#include "RedcarModule.h"
#include "Standplaats.h"

namespace Deelautos {

Deelauto::Deelauto()
{
}

Deelauto::Deelauto(const std::string& kenteken, std::shared_ptr<AutoType> type,
		std::shared_ptr<Standplaats>& standplaats, std::shared_ptr<RedcarModule>& redcardModule)
: kenteken(kenteken)
, type(type)
, standplaats(standplaats)
, redcardModule(redcardModule)
{
}

std::shared_ptr<Standplaats> Deelauto::getStandPlaats() const
{
	return standplaats;
}

std::shared_ptr<RedcarModule> Deelauto::getRedcarModule() const
{
	return redcardModule;
}

std::shared_ptr<AutoType> Deelauto::getAutoType() const
{
	return type;
}

void Deelauto::verhuurActief(uint32_t pasNummer)
{
	redcardModule->setPasNummer(pasNummer);
}

bool Deelauto::checkOpLocatie() const
{
	return redcardModule->getLocatie() == standplaats->locatie;
}

void Deelauto::verhuurVoltooid()
{
	redcardModule->reset();
}

}
