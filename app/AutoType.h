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
	AutoType(const std::string& naam);

public:

	~AutoType() = default;

	std::string naam;
};

#endif /* AUTOTYPE_H_ */
