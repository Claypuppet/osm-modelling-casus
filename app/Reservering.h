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

class Klant;
class Verhuur;

class Reservering : public DatastoreModel<Reservering>, public Product
{
	friend DatastoreModel<Klant>;
	Reservering();
	Reservering(uint32_t id, uint32_t beginMoment , uint32_t eindMoment, std::shared_ptr<Klant>& klant);
	~Reservering();

public:
	std::shared_ptr<Verhuur>	verzilveren();
	bool						isIngecheckt();

public:

	uint32_t					id;
	uint32_t					beginMoment;
	uint32_t					eindMoment;
	std::shared_ptr<Klant>		klant;
	std::shared_ptr<Verhuur>	verhuur;

public:
	virtual tarieven::TariefPtr getTarief();
	virtual Geld getKosten() override;

};

#endif /* RESERVERING_H_ */
