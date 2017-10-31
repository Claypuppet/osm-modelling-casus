/*
 * Klant.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANT_H_
#define KLANT_H_


#include "DatastoreModel.h"
#include "AbonnementType.h"

#include <stdint.h>

namespace Klanten {

using Core::DatastoreModel;
using Producten::AbonnementType;

class Klant : public DatastoreModel<Klant>
{
	friend DatastoreModel<Klant>;

	Klant();
	Klant(std::string naam, std::string email, uint32_t pasNummer, std::shared_ptr<AbonnementType>& abbonomentType);


public:

	~Klant();

	std::string naam;
	std::string email;
	uint32_t pasNummmer;
	std::shared_ptr<AbonnementType> abbonomentType;
};

typedef std::shared_ptr<Klant> KlantPtr;

}

#endif /* KLANT_H_ */
