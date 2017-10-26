/*
 * TariefSoortPrijs.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#include "TariefSoortPrijs.h"

namespace tarieven
{

TariefSoortPrijs::TariefSoortPrijs(TariefSoortPtr soort, Geld prijs)
: soort(soort), prijs(prijs)
{
}

Geld tarieven::TariefSoortPrijs::berekenKosten(uint32_t aantalPeriodes)
{
	return prijs * aantalPeriodes;
}


} /* namespace tarieven */

