/*
 * VerhuurRepo.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef VERHUURREPO_H_
#define VERHUURREPO_H_

#include "IDataStore.h"
#include "BaseRepo.h"
#include "Geld.h"
#include "Verhuur.h"
#include <memory>


namespace Producten
{
	using Core::BaseRepo;
	using Core::IDataStore;
	using Klanten::Klant;

template <typename DataStoreType>
class VerhuurRepo : public BaseRepo<Verhuur, DataStoreType>
{
public:
	VerhuurRepo(IDataStore<DataStoreType>& dataStore)
	:	BaseRepo<Verhuur, DataStoreType>(dataStore)
	{}
	~VerhuurRepo() = default;


	std::shared_ptr<Verhuur> getActiefVerhuur(const std::shared_ptr<Klant>& klant);

	bool controleerKlantIngecheckt(const std::shared_ptr<Klant>& klant)
	{
		return !!getActiefVerhuur(klant);
	}

};


struct ActiefVerhuurVanKlant {
	ActiefVerhuurVanKlant(const std::shared_ptr<Klant>& klant)
	: klant(klant)
	{
	}

	bool operator()(const std::shared_ptr<Verhuur>& verhuur)
	{
		if(verhuur->reservering->klant->id != klant->id)
			return false;
		return verhuur->uitcheckMoment == 0;
	}

	const std::shared_ptr<Klant>& klant;
};


template<typename DataStoreType>
inline std::shared_ptr<Verhuur> VerhuurRepo<DataStoreType>::getActiefVerhuur(
		const std::shared_ptr<Klant>& klant)
{
	std::shared_ptr<Verhuur> result;
	return this->mDataStore.loadModel(result, ActiefVerhuurVanKlant(klant));
}

}

#endif /* VERHUURREPO_H_ */
