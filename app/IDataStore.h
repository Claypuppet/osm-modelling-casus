/*
 * IDataStore.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef IDATASTORE_H_
#define IDATASTORE_H_


#include "DatastoreModel.h"

#include <functional>
#include <type_traits>
#include <memory>
#include <utility>

#include <boost/type_index/ctti_type_index.hpp>

using boost::typeindex::ctti_type_index;

template<typename ModelType, typename ModelIdFieldType=uint32_t>
struct ModelById
{
	ModelById(const ModelIdFieldType& id) : id(id) {}

	bool operator()(const std::shared_ptr<ModelType>& model)
	{
		return model->id == id;
	}

public:
	const ModelIdFieldType& id;
};

template<typename Derrived>
class IDataStore
{
public:
	IDataStore() = default;
	~IDataStore() = default;

	template<typename ModelType>
	using IsValidModelType = std::is_same<bool,bool>; //std::is_base_of<DatastoreModel<ModelType>*, ModelType*>

	template<typename ModelType>
	using ValidModelType = std::enable_if<IsValidModelType<ModelType>::value,ModelType>;

	template <typename T, typename = uint32_t>
	struct HasId : std::false_type { };

	template <typename T>
	struct HasId <T, decltype((void) T::x, 0)> : std::true_type {};


	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>>
	std::shared_ptr<ModelType> loadModel(const std::shared_ptr<ModelType>& out, const SelectPredicate& predicate)
	{
		Derrived& d = static_cast<Derrived&>(*this);
		using DT = decltype(&Derrived::template loadModel<ModelType,SelectPredicate>);
		using BT = decltype(&IDataStore<Derrived>::template loadModel<ModelType,SelectPredicate>);
		static_assert(ctti_type_index::type_id<DT>() != ctti_type_index::type_id<BT>(),
				"Derrived did not implement loadModel method");

		return d.loadModel(out, predicate);
	}




	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>>
	std::shared_ptr<ModelType> saveModel(std::shared_ptr<ModelType> in, const SelectPredicate& predicate)
	{
		Derrived& d = static_cast<Derrived&>(*this);
		using DT = decltype(&Derrived::template saveModel<ModelType,SelectPredicate>);
		using BT = decltype(&IDataStore<Derrived>::template saveModel<ModelType,SelectPredicate>);
		static_assert(ctti_type_index::type_id<DT>() != ctti_type_index::type_id<BT>(),
				"Derrived did not implement saveModel method");

		return d.saveModel(in, predicate);
	}


	template<typename ModelType>
	std::shared_ptr<ModelType> createModel(std::shared_ptr<ModelType> model)
	{
		static_assert(!HasId<ModelType>::value, "Model needs to have an id member as primary key");
		if(!model)
			throw std::invalid_argument("nullptr value");
		if(model->id != 0)
			throw std::invalid_argument("model already has an id assigned, did you mean to save it?");
		Derrived& d = static_cast<Derrived&>(*this);

		using DT = decltype(&Derrived::template createModel<ModelType>);
		using BT = decltype(&IDataStore<Derrived>::template createModel<ModelType>);
		static_assert(ctti_type_index::type_id<DT>() != ctti_type_index::type_id<BT>(),
				"Derrived did not implement createModel method");


		return d.createModel(model);
	}

};



#endif /* IDATASTORE_H_ */
