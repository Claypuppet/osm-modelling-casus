/*
 * KlantRepo.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef KLANTREPO_H_
#define KLANTREPO_H_

#include <stdint.h>

class Klant;
template <typename T> class IDataStore;

template <typename DataStoreType>
class KlantRepo
{
public:
	KlantRepo(IDataStore<DataStoreType>& dataStore);
	~KlantRepo() {}

	bool getKlantByPasNummer(uint32_t pasNummer, Klant& klant);

private:
	IDataStore<DataStoreType>& mDataStore;
};

template<typename DataStoreType>
inline KlantRepo<DataStoreType>::KlantRepo(IDataStore<DataStoreType>& dataStore)
: mDataStore(dataStore)
{
}

#endif /* KLANTREPO_H_ */
