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



class AbbonomentType : public DatastoreModel<AbbonomentType>
{
	friend DatastoreModel<AbbonomentType>;
	AbbonomentType();
	AbbonomentType(uint32_t id, const std::string& naam, const Geld& kosten);
	~AbbonomentType();

public:
	uint32_t id;
	std::string	naam;
	Geld kosten;
};

#endif /* ABBONOMENTTYPE_H_ */
