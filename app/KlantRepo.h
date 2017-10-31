/*
 * KlantRepo.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANTREPO_H_
#define KLANTREPO_H_

#include "Klant.h"
#include <stdint.h>


template <typename T> class IDataStore;

template <typename DataStoreType>
class KlantRepo
{
public:
	KlantRepo(IDataStore<DataStoreType>& dataStore);
	~KlantRepo() {}

	KlantPtr getKlantByPasNummer(uint32_t pasNummer);

private:
	IDataStore<DataStoreType>& mDataStore;
};

template<typename DataStoreType>
inline KlantRepo<DataStoreType>::KlantRepo(IDataStore<DataStoreType>& dataStore)
: mDataStore(dataStore)
{
}


template <typename DataStoreType>
KlantPtr KlantRepo<DataStoreType>::getKlantByPasNummer(uint32_t pasNummer)
{
	auto klantByPasNummer = [pasNummer](const KlantPtr& k){
		return k->pasNummmer == pasNummer; };
	KlantPtr klant;
	return mDataStore.loadModel(klant, klantByPasNummer);
}

#endif /* KLANTREPO_H_ */
