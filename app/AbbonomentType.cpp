/*
 * AbbonomentType.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "AbbonomentType.h"

AbbonomentType::AbbonomentType()
{
}

AbbonomentType::AbbonomentType(const std::string& naam,const Geld& kosten)
: naam(naam)
, kosten(kosten)
{
}

AbbonomentType::~AbbonomentType()
{
	// TODO Auto-generated destructor stub
}

