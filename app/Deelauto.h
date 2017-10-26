/*
 * Deelauto.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef DEELAUTO_H_
#define DEELAUTO_H_

#include "DatastoreModel.h"
#include <string>

class Deelauto : public DatastoreModel<Deelauto>
{
	friend DatastoreModel<Deelauto>;
	Deelauto();
	Deelauto(uint32_t id, std::string kenteken);

public:
	~Deelauto();

public:
	uint32_t id;
	std::string kenteken;
};

#endif /* DEELAUTO_H_ */
