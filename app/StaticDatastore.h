/*
 * StaticDatastore.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef STATICDATASTORE_H_
#define STATICDATASTORE_H_

#include "Singleton.h"
#include "IDataStore.h"
#include "DatastoreModel.h"
#include "ctti/type_id.hpp"

#include <functional>
#include <algorithm>
#include <vector>
#include <atomic>
#include <type_traits>
#include <map>
#include <unordered_map>


class StaticDatastore;
//class Klant;S
//class Deelauto;

//template <typename ModelType, typename Enable = void>
//struct StaticDatastoreStoreage : public std::false_type {};


template <typename ModelType>
struct StaticDatastoreStoreage : public std::true_type
{
private:
	friend StaticDatastore;
	typedef typename ModelType::ModelPtr ModelPtr;
	using VectorType = std::vector<ModelPtr>;


	template<typename SelectPredicate>
	static ModelPtr load(const SelectPredicate& selectPredicate)
	{
		auto iter = std::find_if(store.begin(), store.end(), selectPredicate);
		if(iter != store.end())
			return *iter;
		return ModelPtr();
	}

	template<typename SelectPredicate>
	static bool save(ModelPtr& model, const SelectPredicate& selectPredicate)
	{
		auto iter = std::find_if(store.begin(), store.end(), selectPredicate);
		if(iter != store.end()) {
			*iter = model;
			return true;
		}
		return false;
	}

	static void create(const ModelPtr model)
	{
		model->id = ++idCounter;
		store.push_back(model);
	}

private:
	static std::atomic<uint32_t> idCounter;
	static VectorType store;

};

template<typename ModelType>
std::vector<typename ModelType::ModelPtr> StaticDatastoreStoreage<ModelType>::store;

template<typename ModelType>
std::atomic<uint32_t> StaticDatastoreStoreage<ModelType>::idCounter;


class StaticDatastore : public IDataStore<StaticDatastore>
{
public:
	StaticDatastore();
	~StaticDatastore();

	friend IDataStore<StaticDatastore>;

	void initStaticTestData();

protected:


	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>>
	std::shared_ptr<ModelType> loadModel(const std::shared_ptr<ModelType>& out, const SelectPredicate& predicate)
	{
		return StaticDatastoreStoreage<ModelType>::load(predicate);
	}

	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>>
	std::shared_ptr<ModelType> saveModel(std::shared_ptr<ModelType>& model, const SelectPredicate& predicate)
	{
		return StaticDatastoreStoreage<ModelType>::save(model, predicate), model;
	}


	template<typename ModelType>
	std::shared_ptr<ModelType> createModel(std::shared_ptr<ModelType> model)
	{
		StaticDatastoreStoreage<ModelType>::create(model);
		return model;
	}

};

#endif /* STATICDATASTORE_H_ */
