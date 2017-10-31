/*
 * KlantRepo.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANTREPO_H_
#define KLANTREPO_H_

#include "Klant.h"
#include "BaseRepo.h"
#include <stdint.h>


template <typename DataStoreType>
class KlantRepo : public BaseRepo<Klant, DataStoreType>
{
public:
	KlantRepo(IDataStore<DataStoreType>& dataStore)
		: BaseRepo<Klant, DataStoreType>(dataStore)
	{}

	~KlantRepo() {}

	KlantPtr getKlantByPasNummer(uint32_t pasNummer){
		auto klantByPasNummer = [pasNummer](const KlantPtr& k){
			return k->pasNummmer == pasNummer; };
		KlantPtr klant;
		return this->mDataStore.loadModel(klant, klantByPasNummer);
	}
};


#endif /* KLANTREPO_H_ */
