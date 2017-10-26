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

class Verhuur : public DatastoreModel<Verhuur>
{
	friend DatastoreModel<Verhuur>;
	Verhuur();

public:
	~Verhuur();

	std::shared_ptr<Reservering> reservering;

};

#endif /* VERHUUR_H_ */
