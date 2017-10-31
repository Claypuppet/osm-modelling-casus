/*
 * RedcarModule.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#include "RedcarModule.h"

namespace RedcardModule {

RedcarModule::RedcarModule()
: aantalKilometers(0)
, pasNummer(0)
{
	// TODO Auto-generated constructor stub

}

RedcarModule::RedcarModule(float aantalKilometers, uint32_t pasNummer)
: aantalKilometers(aantalKilometers)
, pasNummer(pasNummer)
{
}

uint32_t RedcarModule::getLocatie() const
{
	return 1;
}

void RedcarModule::reset()
{
	this->pasNummer = 0;
	this->aantalKilometers = 0;
}

uint32_t RedcarModule::getPasNummer() const
{
	return pasNummer;
}


float RedcarModule::getAantalKilometers() const
{
	return aantalKilometers;
}

void RedcarModule::setPasNummer(uint32_t pasNummer)
{
	this->pasNummer = pasNummer;
}

}
