/*
 * Tarief.h
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#ifndef APP_TARIEF_H_
#define APP_TARIEF_H_

#include "Geld.h"
#include "TariefSoortPrijs.h"


namespace tarieven
{

class Tarief : public DatastoreModel<Tarief>
{
public:
	uint32_t kilometersVrij;
	Geld prijsPerKilometer;
	tariefSoortenPrijsLijst prijzen;

public:
	virtual ~Tarief() = default;
	Geld berekenKosten(uint32_t aantalKilometers, TariefSoortPtr soort, uint32_t aantal);

private:
	Tarief::Tarief(uint32_t kilometersVrij, Geld PrijsPerKilometer, tariefSoortenPrijsLijst prijzen);
	TariefSoortPrijsPtr getTariefSoortPrijs(const TariefSoortPtr& soort);
	Geld getKilometerPrijs(uint32_t aantalKilometers);
};

typedef std::shared_ptr<Tarief> TariefPtr;

} /* namespace tarieven */

#endif /* APP_TARIEF_H_ */
