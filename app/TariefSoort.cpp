/*
 * TariefSoort.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#include "TariefSoort.h"

namespace tarieven
{

TariefSoort::TariefSoort(std::string naam, uint8_t weekMask, uint32_t periode)
: naam(naam), weekMask(weekMask), periode(periode)
{
}


} /* namespace tarieven */
