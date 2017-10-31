/*
 * ReserveringRepo.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef RESERVERINGREPO_H_
#define RESERVERINGREPO_H_


#include "Reservering.h"
#include "Klant.h"
#include "BaseRepo.h"
#include "Application.h"

#include <stdint.h>
#include <memory>
#include <chrono>

namespace Producten
{
	using Core::BaseRepo;
	using Core::Application;
	using Klanten::Klant;

struct ReserverMetKlantEnMoment
{
	ReserverMetKlantEnMoment(std::shared_ptr<Klant>& klant, uint32_t moment)
	:	klant(klant)
	,	moment(moment)
	{
	}

	bool operator()(const std::shared_ptr<Reservering>& reservering)
	{
		if(reservering->klant->id != klant->id)
			return false;
		if(reservering->beginMoment > moment || reservering->eindMoment < moment)
			return false;
		if(reservering->isIngecheckt())
			return false;
		return true;
	}

private:
	std::shared_ptr<Klant>& klant;
	uint32_t moment;
};


template <typename DataStoreType>
class ReserveringRepo : public BaseRepo<Reservering, DataStoreType>
{
public:
	ReserveringRepo(IDataStore<DataStoreType>& dataStore)
	:	BaseRepo<Reservering, DataStoreType>(dataStore)
	{}
	~ReserveringRepo() = default;

	std::shared_ptr<Reservering> getBeschikbareReservering(std::shared_ptr<Klant>& klant)
	{
		std::shared_ptr<Reservering> r;
		return this->mDataStore.loadModel(r, ReserverMetKlantEnMoment(klant, Application::i().getNowMoment()));
	}

};

}

#endif /* RESERVERINGREPO_H_ */
