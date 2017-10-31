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
#include "AutoType.h"
#include "AbonnementType.h"

namespace tarieven
{
class Tarief;

typedef std::shared_ptr<Tarief> TariefPtr;

class Tarief : public DatastoreModel<Tarief>
{
public:
	uint32_t kilometersVrij;
	Geld prijsPerKilometer;
	tariefSoortenPrijsLijst prijzen;
	std::shared_ptr<AutoType> autoType;
	std::shared_ptr<AbonnementType> aboType;

public:
	Tarief();
	Tarief(uint32_t kilometersVrij, Geld PrijsPerKilometer, tariefSoortenPrijsLijst prijzen, std::shared_ptr<AutoType> autoType, std::shared_ptr<AbonnementType> aboType);
	TariefSoortPrijsPtr getTariefSoortPrijs(const TariefSoortPtr& soort);
	virtual ~Tarief() = default;
	Geld berekenKosten(uint32_t aantalKilometers, TariefSoortPtr soort, uint32_t aantal);

private:
	friend DatastoreModel<Tarief>;
	Geld getKilometerPrijs(uint32_t aantalKilometers);
};

} /* namespace tarieven */

#endif /* APP_TARIEF_H_ */
