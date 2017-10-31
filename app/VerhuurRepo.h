/*
 * VerhuurRepo.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef VERHUURREPO_H_
#define VERHUURREPO_H_

#include "IDataStore.h"
#include "Geld.h"
#include "Verhuur.h"
#include <memory>

class Klant;
class Verhuur;

template <typename DataStoreType>
class VerhuurRepo
{
public:
	VerhuurRepo(IDataStore<DataStoreType>& dataStore)
	:	mDataStore(dataStore)
	{}
	~VerhuurRepo() = default;


	std::shared_ptr<Verhuur> getActiefVerhuur(const std::shared_ptr<Klant>& klant);
	void save(std::shared_ptr<Verhuur> verhuur);



private:
	IDataStore<DataStoreType>& mDataStore;
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
	return mDataStore.loadModel(result, ActiefVerhuurVanKlant(klant));
}

template<typename DataStoreType>
inline void VerhuurRepo<DataStoreType>::save(std::shared_ptr<Verhuur> verhuur)
{
	if(verhuur->id)
		mDataStore.saveModel(verhuur, ModelById<Verhuur>(verhuur->id));
	else
		mDataStore.createModel(verhuur);
}

#endif /* VERHUURREPO_H_ */
