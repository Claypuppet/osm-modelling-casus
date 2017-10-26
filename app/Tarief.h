/*
 * Tarief.h
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#ifndef APP_TARIEF_H_
#define APP_TARIEF_H_

#include "Geld.h"
#include "TariefSoort.h"


namespace tarieven
{

class Tarief
{
public:
	uint32_t kilometersVrij;
	Geld PrijsPerKilometer;


public:
	Tarief();
	virtual ~Tarief();
};

typedef std::shared_ptr<Tarief> TariefPtr;

} /* namespace tarieven */

#endif /* APP_TARIEF_H_ */
