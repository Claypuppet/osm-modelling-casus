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
#include "BaseRepo.h"
#include <memory>


template <typename DataStoreType>
class TariefRepo : public BaseRepo<tarieven::Tarief, DataStoreType>
{
public:
	TariefRepo(IDataStore<DataStoreType>& dataStore)
	:	BaseRepo<tarieven::Tarief, DataStoreType>(dataStore)
	{}
	~TariefRepo() = default;

	tarieven::TariefPtr getTariefByTypes(std::shared_ptr<AutoType> aut, std::shared_ptr<AbonnementType> abt)
	{
		auto tL = [aut, abt](tarieven::TariefPtr t)
		{
			return (t->autoType->id == aut->id && t->aboType->id == abt->id);
		};
		auto tp = tarieven::TariefPtr();
		tarieven::TariefPtr tarief = this->mDataStore.loadModel(tp, tL);
		return tarief;
	}

};


#endif /* TARIEFREPO_H_ */
