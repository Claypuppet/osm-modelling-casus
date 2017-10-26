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
	static bool save(const ModelPtr model, const SelectPredicate& selectPredicate)
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
	typename ModelType::ModelPtr loadModel(const SelectPredicate& predicate)
	{
		return StaticDatastoreStoreage<ModelType>::load(predicate);
	}

	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>>
	typename ModelType::ModelPtr saveModel(typename ModelType::ModelPtr& model, const SelectPredicate& predicate)
	{
		return StaticDatastoreStoreage<ModelType>::save(model, predicate);
	}


	template<typename ModelType>
	typename ModelType::ModelPtr createModel(typename ModelType::ModelPtr model)
	{
		StaticDatastoreStoreage<ModelType>::create(model);
		return model;
	}

};

class StaticDatastoreNew : public IDataStoreNew
{

public:
	StaticDatastoreNew() = default;
	~StaticDatastoreNew() = default;

	/*
	template<typename ModelType>
	void createStore()
	{
		mDataStores.insert(std::make_pair(ctti::unnamed_type_id<ModelType>().hash(),1));

	}


	template<typename ModelType>
	void createStore(std::vector<std::shared_ptr<ModelType>>&& models)
	{
		mDataStores.insert({ctti::unnamed_type_id<ModelType>().hash(), models});
	}
	*/



protected:

	struct DataStore {


		DataStore(std::function<void(std::shared_ptr<IDatastoreModel>&, uint32_t)> modelIdSetter)
		: modelIdSetter(modelIdSetter)
		{
		}

		template <typename ModelType>
		static DataStore Create()
		{
			return DataStore([](std::shared_ptr<IDatastoreModel>& modelPtr, uint32_t id){
				std::static_pointer_cast<ModelType>(modelPtr)->id = id;});
		}


		template<typename ModelType>
		DataStore(std::vector<std::shared_ptr<ModelType>>&& models)
		: modelIdSetter()
		, models(std::move(models))
		{
		}


		std::atomic<uint32_t> idCounter;
		std::vector<std::shared_ptr<IDatastoreModel>> models;
		std::function<void(std::shared_ptr<IDatastoreModel>&, uint32_t)> modelIdSetter;
	};


	virtual std::shared_ptr<IDatastoreModel> _load(TypeHash modelHash, std::function<bool(const std::shared_ptr<IDatastoreModel>&)> selectPredicate)
	{
		std::shared_ptr<IDatastoreModel> result;
		auto iter = mDataStores.find(modelHash);
		if(iter != mDataStores.end()) {
			DataStore& store = iter->second;
			auto modelIter = std::find_if(store.models.begin(), store.models.end(), selectPredicate);
			if(modelIter != store.models.end())
				result = *modelIter;
		}
		return result;
	}

	virtual bool _save(TypeHash modelHash, const std::shared_ptr<IDatastoreModel>& modelPtr)
	{
		auto iter = mDataStores.find(modelHash);
		if(iter != mDataStores.end()) {
			DataStore& store = iter->second;
			auto modelIter = std::find_if(store.models.begin(), store.models.end(),[modelPtr](std::shared_ptr<IDatastoreModel>& a){ return a == modelPtr; });
			if(modelIter != store.models.end()) {
				return true;
			}
		}
		return false;
	}

	virtual bool _insert(TypeHash modelHash, std::shared_ptr<IDatastoreModel> modelPtr)
	{
		auto iter = mDataStores.find(modelHash);
		if(iter != mDataStores.end()) {
			DataStore& store = iter->second;
			store.modelIdSetter(modelPtr, ++store.idCounter);
			store.models.emplace_back(modelPtr);
			return true;
		}
		return false;
	}

protected:

	std::unordered_map<TypeHash, DataStore> mDataStores;

};

#endif /* STATICDATASTORE_H_ */
