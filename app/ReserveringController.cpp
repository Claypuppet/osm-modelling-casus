/*
 * ReserveringController.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: klei
 */

#include "ReserveringController.h"
#include "RedCarsContext.h"
#include <iostream>


namespace Producten
{
	using Core::RedCarsContext;
	using Klanten::KlantRepo;

ReserveringController::ReserveringController()
{
	// TODO Auto-generated constructor stub

}

ReserveringController::~ReserveringController()
{
	// TODO Auto-generated destructor stub
}

void ReserveringController::verzilverReservering(uint32_t pasnummer)
{
	RedCarsContext& context = RedCarsContext::getInstance();
	KlantPtr k = context.getKlantRepo().getKlantByPasNummer(pasnummer);
	if(!k)
		throw std::logic_error("Hee dit is geen klant!");
	bool ingecheckt = context.getVehuurRepo().controleerKlantIngecheckt(k);
	if(ingecheckt)
		throw std::logic_error("Hee de klant is al ingecheckt!");
	std::shared_ptr<Reservering> r = context.getReserveringRepo().getBeschikbareReservering(k);
	if(!r)
		throw std::logic_error("Hee er is helemaal geen reservering voor deze klant!");

	std::shared_ptr<Verhuur> v =  r->verzilveren();

	context.getVehuurRepo().create(v);
	context.getReserveringRepo().save(r);

	std::cout << "Reservering ingecheckt!" << std::endl;
	std::cout << r->asString() << std::endl;
}

void ReserveringController::voltooiVerhuur(uint32_t pasnummer)
{
	RedCarsContext& context = RedCarsContext::getInstance();
	KlantPtr k = context.getKlantRepo().getKlantByPasNummer(pasnummer);
	if(!k)
		throw std::logic_error("Hee dit is geen klant!");
	std::shared_ptr<Verhuur> v = context.getVehuurRepo().getActiefVerhuur(k);
	if(!v)
		throw std::logic_error("Hee de klant heeft geen actief verhuur!");

	v->voltooi();

	context.getVehuurRepo().save(v);

	std::cout << "Verhuur voltooid!" << std::endl;
	std::cout << v->reservering->asString() << std::endl;
}

} /* namespace reserveringen */
