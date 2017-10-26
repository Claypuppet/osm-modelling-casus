/*
 * AbbonomentType.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "AbbonomentType.h"

AbbonomentType::AbbonomentType()
: id(0)
{
	// TODO Auto-generated constructor stub
}

AbbonomentType::AbbonomentType(uint32_t id, const std::string& naam,const Geld& kosten)
: id(id)
, naam(naam)
, kosten(kosten)
{
}

AbbonomentType::~AbbonomentType()
{
	// TODO Auto-generated destructor stub
}

