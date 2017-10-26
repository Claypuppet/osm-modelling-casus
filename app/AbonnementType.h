/*
 * AbbonomentType.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef ABBONOMENTTYPE_H_
#define ABBONOMENTTYPE_H_


#include "Geld.h"
#include "DatastoreModel.h"

#include <stdint.h>
#include <string>



class AbonnementType : public DatastoreModel<AbonnementType>
{
	friend DatastoreModel<AbonnementType>;
	AbonnementType();
	AbonnementType(const std::string& naam, const Geld& kosten);

public:
	~AbonnementType();

	std::string	naam;
	Geld kosten;
};

#endif /* ABBONOMENTTYPE_H_ */
