/*
 * StaticDatastore.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef STATICDATASTORE_H_
#define STATICDATASTORE_H_

#include "IDataStore.h"
#include "Singleton.h"

#include <functional>
#include <algorithm>
#include <vector>

class Klant;


template <typename ModelType>
struct StaticDatastoreStoreage
{
	static const bool value = false;
};

template<>
struct StaticDatastoreStoreage<Klant>
{
	static const bool value = true;
	static std::vector<Klant> store;
};


class StaticDatastore : public IDataStore<StaticDatastore>, public Singleton<StaticDatastore>
{
public:
	StaticDatastore();
	~StaticDatastore();


	template<typename ModelType, typename InstancePredicate=ModelById<ModelType>>
	bool loadModel(ModelType& out, const InstancePredicate& predicate)
	{
		if(!StaticDatastoreStoreage<ModelType>::value)
			return false;
		auto& store = StaticDatastoreStoreage<ModelType>::store;
		auto iter = std::find_if(store.begin(), store.end(), predicate);
		if(iter != store.end()) {
			out = *iter;
			return true;
		}
		return false;
	}

	template<typename ModelType, typename InstancePredicate=ModelById<ModelType>>
	bool saveModel(const ModelType& in, const InstancePredicate& predicate, bool allowCreate=true)
	{
		if(!StaticDatastoreStoreage<ModelType>::value)
					return false;
		auto& store = StaticDatastoreStoreage<ModelType>::store;
		auto iter = std::find_if(store.begin(), store.end(), predicate);
		if(iter != store.end()) {
			*iter = in;
			return true;
		}
		if(allowCreate) {
			store.push_back(in);
			return true;
		}
		return false;
	}

};

#endif /* STATICDATASTORE_H_ */
