/*
 * Klant.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANT_H_
#define KLANT_H_


#include "DatastoreModel.h"
#include <stdint.h>
#include "AbonnementType.h"

class Klant : public DatastoreModel<Klant>
{
	friend DatastoreModel<Klant>;

	Klant();
	Klant(uint32_t pasNummer, std::shared_ptr<AbonnementType>& abbonomentType);


public:

	~Klant();

	uint32_t pasNummmer;
	std::shared_ptr<AbonnementType> abbonomentType;
};

typedef std::shared_ptr<Klant> KlantPtr;

#endif /* KLANT_H_ */
