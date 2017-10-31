/*
 * TariefSoortPrijs.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#include "TariefSoortPrijs.h"

namespace Tarieven
{

TariefSoortPrijs::TariefSoortPrijs(TariefSoortPtr soort, Geld prijs)
: soort(soort), prijs(prijs)
{
}

Geld Tarieven::TariefSoortPrijs::berekenKosten(uint32_t aantalPeriodes)
{
	return prijs * aantalPeriodes;
}


} /* namespace tarieven */

