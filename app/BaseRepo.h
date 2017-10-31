/*
 * VerhuurRepo.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef BASEREPO_H_
#define BASEREPO_H_

#include "IDataStore.h"
#include <memory>

namespace Core {


template <typename ModelType, typename DataStoreType>
class BaseRepo
{
protected:
	IDataStore<DataStoreType>& mDataStore;

public:
	BaseRepo(IDataStore<DataStoreType>& dataStore)
	:	mDataStore(dataStore)
	{}
	~BaseRepo() = default;

	void save(std::shared_ptr<ModelType> model){
		if(model->id)
			mDataStore.saveModel(model, ModelById<ModelType>(model->id));
		else
			mDataStore.createModel(model);
	}
	void create(std::shared_ptr<ModelType> model){
		mDataStore.createModel(model);
	}
	std::shared_ptr<ModelType> getById(uint32_t id){
		return nullptr;
	}

};

}


#endif /* BASEREPO_H_ */
