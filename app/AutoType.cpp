/*
 * AutoType.cpp
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#include "AutoType.h"

AutoType::AutoType()
{

}

AutoType::AutoType(uint32_t id, const std::string& naam)
: DatastoreModel(id)
, naam(naam)
{
}

