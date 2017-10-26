/*
 * Verhuur.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Verhuur.h"
#include "Product.h"

Verhuur::Verhuur()
: incheckMoment(0)
, uitcheckMoment(0)
{
}

Verhuur::Verhuur(std::shared_ptr<Reservering>& reservering, uint32_t incheckMoment, uint32_t uitcheckMoment)
: reservering(reservering)
, incheckMoment(incheckMoment)
, uitcheckMoment(uitcheckMoment)
{

}

Geld Verhuur::berekenTeLaatBoeteKosten()
{
	/* TODO
	int32_t deltaSec = reservering->eindMoment - uitcheckMoment;
	if(deltaSec < 0) {
		deltaSec = -deltaSec;
		float uren = (float)deltaSec / 60 / 60;
	}
	*/
	return 50;
}
