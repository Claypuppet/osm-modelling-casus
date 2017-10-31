/*
 * AbbonomentType.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "AbonnementType.h"

namespace Producten
{

AbonnementType::AbonnementType()
{
}

AbonnementType::AbonnementType(const std::string& naam,const Geld& kosten)
: naam(naam)
, kosten(kosten)
{
}

AbonnementType::~AbonnementType()
{
	// TODO Auto-generated destructor stub
}

}

