/*
 * Verhuur.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef VERHUUR_H_
#define VERHUUR_H_

#include "DatastoreModel.h"
#include "Reservering.h"
#include "Geld.h"

class Verhuur : public DatastoreModel<Verhuur>
{
	friend DatastoreModel<Verhuur>;
	Verhuur();
	Verhuur(std::shared_ptr<Reservering> reservering, uint32_t incheckMoment, uint32_t uitcheckMoment = 0, uint32_t aantalKilometers = 0);



public:
	~Verhuur() = default;

	Geld berekenTeLaatBoeteKosten();

	void setIncheckMoment(uint32_t moment);
	void setUitcheckMoment(uint32_t moment);
	void voltooi();
	Geld bekerenTeLaatBoeteKosten();



public:
	std::shared_ptr<Reservering> reservering;
	uint32_t incheckMoment;
	uint32_t uitcheckMoment;
	uint32_t aantalKilometers;

};

#endif /* VERHUUR_H_ */
