/*
 * RedcarModule.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef REDCARMODULE_H_
#define REDCARMODULE_H_

#include "DatastoreModel.h"

class RedcarModule : public DatastoreModel<RedcarModule>
{
	RedcarModule();
	RedcarModule(float aantalKilometers, uint32_t pasNummer);
public:
	~RedcarModule() = default;

	uint32_t getLocatie() const;
	void setPasNummer(uint32_t pasNummer);
	uint32_t getPasNummer() const;
	float getAantalKilometers() const;

public:
	float		aantalKilometers;
	uint32_t	pasNummer;
};

#endif /* REDCARMODULE_H_ */