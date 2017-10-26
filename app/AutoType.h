/*
 * AutoType.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef AUTOTYPE_H_
#define AUTOTYPE_H_

#include "DatastoreModel.h"

class AutoType : public DatastoreModel<AutoType>
{
	friend  DatastoreModel<AutoType>;
	AutoType();
	AutoType(uint32_t id, const std::string& naam);

public:

	~AutoType() = default;

	uint32_t id;
	std::string naam;
};

#endif /* AUTOTYPE_H_ */
