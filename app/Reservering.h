/*
 * Reservering.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef RESERVERING_H_
#define RESERVERING_H_

#include "DatastoreModel.h"
#include "Product.h"
#include "Tarief.h"
#include "TariefSoort.h"
#include "Klant.h"

class Verhuur;
class Deelauto;

class Reservering : public DatastoreModel<Reservering>, public Product
{
	friend DatastoreModel<Klant>;
	friend Verhuur;

public:

public:

	uint32_t					beginMoment;
	uint32_t					eindMoment;
	KlantPtr					klant;
	std::shared_ptr<Deelauto>	deelauto;
	tarieven::TariefSoortPtr 	tariefSoort;
	std::shared_ptr<Verhuur>	verhuur;

public:
	Reservering();
	Reservering(uint32_t beginMoment , uint32_t eindMoment, std::shared_ptr<Klant>& klant,
			std::shared_ptr<Deelauto>& deelauto, tarieven::TariefSoortPtr tariefSoort);
	virtual ~Reservering();

	tarieven::TariefPtr getTarief();
	Geld getKosten() override;
	std::shared_ptr<Verhuur> verzilveren();
	bool isIngecheckt();
	uint32_t getTariefSoortPeriodeAantal();
	virtual std::string asString() override;

};

#endif /* RESERVERING_H_ */
