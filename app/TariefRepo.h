/*
 * TariefRepo.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef TARIEFREPO_H_
#define TARIEFREPO_H_


#include "IDataStore.h"
#include "Tarief.h"
#include "AutoType.h"
#include "AbonnementType.h"
#include <memory>


template <typename DataStoreType>
class TariefRepo
{
public:
	TariefRepo(IDataStore<DataStoreType>& dataStore)
	:	mDataStore(dataStore)
	{}
	~TariefRepo() = default;

	tarieven::TariefPtr getTariefByTypes(std::shared_ptr<AutoType> aut, std::shared_ptr<AbonnementType> abt)
	{
		auto tL = [aut, abt](tarieven::TariefPtr t)
		{
			return (t->autoType->id == aut->id && t->aboType->id == abt->id);
		};
		tarieven::TariefPtr tarief = mDataStore.loadModel(tL);
		return tarief;
	}


private:
	IDataStore<DataStoreType>& mDataStore;
};


#endif /* TARIEFREPO_H_ */
