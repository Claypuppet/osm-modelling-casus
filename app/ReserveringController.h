/*
 * ReserveringController.h
 *
 *  Created on: Oct 31, 2017
 *      Author: klei
 */

#ifndef APP_RESERVERINGCONTROLLER_H_
#define APP_RESERVERINGCONTROLLER_H_

#include "Reservering.h"
#include <stdint.h>

namespace reserveringen
{

class ReserveringController
{
public:
	ReserveringController();
	virtual ~ReserveringController();

	void verzilverReservering(uint32_t pasnummer);
	void voltooiVerhuur(uint32_t pasnummer);
};

} /* namespace reserveringen */

#endif /* APP_RESERVERINGCONTROLLER_H_ */
