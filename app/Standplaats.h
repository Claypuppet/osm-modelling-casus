/*
 * Standplaats.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef STANDPLAATS_H_
#define STANDPLAATS_H_

#include "DatastoreModel.h"

class Standplaats : public DatastoreModel<Standplaats>
{
	Standplaats();
	Standplaats(uint32_t locatie);
public:

	~Standplaats() = default;

	bool controlleerLocatie(uint32_t locatie);

public:
	uint32_t locatie;
};

#endif /* STANDPLAATS_H_ */
