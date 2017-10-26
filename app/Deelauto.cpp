/*
 * Deelauto.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Deelauto.h"

Deelauto::Deelauto()
: id(0)
{


}

Deelauto::Deelauto(uint32_t id, std::string kenteken)
: id(id)
, kenteken(kenteken)
{
}

Deelauto::~Deelauto()
{
}

