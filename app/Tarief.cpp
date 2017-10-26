/*
 * Tarief.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#include "Tarief.h"
#include <algorithm>

namespace tarieven
{


Tarief::Tarief(uint32_t kilometersVrij, Geld prijsPerKilometer, tariefSoortenPrijsLijst prijzen)
: kilometersVrij(kilometersVrij), prijsPerKilometer(prijsPerKilometer), prijzen(prijzen)
{
	// TODO Auto-generated constructor stub

}

Geld Tarief::berekenKosten(uint32_t aantalKilometers, TariefSoortPtr soort,
		uint32_t aantalPeriodes)
{
	TariefSoortPrijsPtr soortPrijs = getTariefSoortPrijs(soort);
	Geld kosten = soortPrijs->berekenKosten(aantalPeriodes);
	kosten += getKilometerPrijs(aantalKilometers);
	return kosten;
}

TariefSoortPrijsPtr Tarief::getTariefSoortPrijs(const TariefSoortPtr& soort)
{
	auto soortPrijs = std::find_if(prijzen.begin(), prijzen.end(),
			[soort](const TariefSoortPrijsPtr& tsp){ return tsp->soort->id == soort->id;});

	if(soortPrijs == prijzen.end())
		throw std::logic_error("Tarief soort niet ondersteunt door dit tarief");
	return soortPrijs;
}

Geld Tarief::getKilometerPrijs(uint32_t aantalKilometers)
{
	Geld kosten;
	if(aantalKilometers > kilometersVrij){
		kosten = prijsPerKilometer * (aantalKilometers- kilometersVrij);
	}
	else{
		kosten = 0;
	}
	return kosten;
}

} /* namespace tarieven */
