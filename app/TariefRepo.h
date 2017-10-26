/*
 * TariefRepo.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef TARIEFREPO_H_
#define TARIEFREPO_H_


#include "IDataStore.h"
#include "Geld.h"
#include "Verhuur.h"
#include <memory>

class Klant;
class Verhuur;

template <typename DataStoreType>
class TariefRepo
{
public:
	TariefRepo(IDataStore<DataStoreType>& dataStore)
	:	mDataStore(dataStore)
	{}
	~TariefRepo() = default;




private:
	IDataStore<DataStoreType>& mDataStore;
};




#endif /* TARIEFREPO_H_ */
