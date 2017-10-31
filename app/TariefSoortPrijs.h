/*
 * TariefSoortPrijs.h
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#ifndef APP_TARIEFSOORTPRIJS_H_
#define APP_TARIEFSOORTPRIJS_H_

#include <vector>
#include "TariefSoort.h"
#include "Geld.h"

namespace tarieven
{

class TariefSoortPrijs : public DatastoreModel<TariefSoortPrijs>
{

public:
	virtual ~TariefSoortPrijs() = default;
	Geld berekenKosten(uint32_t aantalPeriodes);

	TariefSoortPtr soort;
	Geld prijs;

private:
	friend DatastoreModel<TariefSoortPrijs>;
	TariefSoortPrijs(TariefSoortPtr soort, Geld prijs);
};

typedef std::shared_ptr<TariefSoortPrijs> TariefSoortPrijsPtr;
typedef std::vector<TariefSoortPrijsPtr> tariefSoortenPrijsLijst;

} /* namespace tarieven */

#endif /* APP_TARIEFSOORTPRIJS_H_ */
