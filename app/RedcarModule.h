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
	void reset();
	uint32_t getPasNummer() const;
	void setPasnummer(uint32_t pasNummer);
	float getAantalKilometers() const;

public:
	uint32_t	aantalKilometers;
	uint32_t	pasNummer;
};

#endif /* REDCARMODULE_H_ */
