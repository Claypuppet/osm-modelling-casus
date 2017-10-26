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


template<typename DataStoreType>
inline std::shared_ptr<Verhuur> VerhuurRepo<DataStoreType>::getActiefVerhuur(
		const std::shared_ptr<Klant>& klant)
{
	return nullptr;
}

template<typename DataStoreType>
inline void VerhuurRepo<DataStoreType>::save(std::shared_ptr<Verhuur> verhuur)
{
	mDataStore.saveModel(verhuur, ModelById<Verhuur>(verhuur->id));
}

#endif /* VERHUURREPO_H_ */
