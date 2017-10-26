/*
 * Deelauto.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Deelauto.h"

Deelauto::Deelauto()
{
}

Deelauto::Deelauto(const std::string& kenteken, std::shared_ptr<Standplaats>& standplaats, std::shared_ptr<RedcarModule>& redcardModule)
: kenteken(kenteken)
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
