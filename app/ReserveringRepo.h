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
#include "Application.h"

#include <stdint.h>
#include <memory>
#include <chrono>

template <typename T> class IDataStore;


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
class ReserveringRepo
{
public:
	ReserveringRepo(IDataStore<DataStoreType>& dataStore)
	:	mDataStore(dataStore)
	{}
	~ReserveringRepo() = default;

	std::shared_ptr<Reservering> getBeschrikbareReservering(std::shared_ptr<Klant>& klant)
	{
		return mDataStore.loadModel(ReserverMetKlantEnMoment(klant, Application::getNowMoment()));
	}



private:
	IDataStore<DataStoreType>& mDataStore;
};



#endif /* RESERVERINGREPO_H_ */
