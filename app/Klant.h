/*
 * Klant.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANT_H_
#define KLANT_H_


#include "DatastoreModel.h"
#include "AbbonomentType.h"

#include <stdint.h>

class Klant : public DatastoreModel<Klant>
{
	friend DatastoreModel<Klant>;

	Klant()
	: DatastoreModel(0)
	, pasNummmer(0)
	{}

	Klant(uint32_t id, uint32_t pasNummer, std::shared_ptr<AbbonomentType>& abbonomentType)
	: DatastoreModel(id)
	, pasNummmer(pasNummer)
	, abbonomentType(abbonomentType)
	{}


public:

	~Klant();

	uint32_t pasNummmer;
	std::shared_ptr<AbbonomentType> abbonomentType;
};

#endif /* KLANT_H_ */
