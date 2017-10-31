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

namespace Tarieven {
	using Core::BaseRepo;
	using Core::IDataStore;

template <typename DataStoreType>
class TariefRepo : public BaseRepo<Tarief, DataStoreType>
{
public:
	TariefRepo(IDataStore<DataStoreType>& dataStore)
	:	BaseRepo<Tarief, DataStoreType>(dataStore)
	{}
	~TariefRepo() = default;

	TariefPtr getTariefByTypes(std::shared_ptr<AutoType> aut, std::shared_ptr<AbonnementType> abt)
	{
		auto tL = [aut, abt](TariefPtr t)
		{
			return (t->autoType->id == aut->id && t->aboType->id == abt->id);
		};
		auto tp = TariefPtr();
		TariefPtr tarief = this->mDataStore.loadModel(tp, tL);
		return tarief;
	}

};

}


#endif /* TARIEFREPO_H_ */
