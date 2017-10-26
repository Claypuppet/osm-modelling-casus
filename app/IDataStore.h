/*
 * IDataStore.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef IDATASTORE_H_
#define IDATASTORE_H_


#include "DatastoreModel.h"
#include "ctti/type_id.hpp"

#include <functional>
#include <type_traits>
#include <memory>
#include <utility>


template<typename ModelType, typename ModelIdFieldType=uint32_t>
struct ModelById
{
	ModelById(const ModelIdFieldType& id) : id(id) {}

	bool operator()(const ModelType& model)
	{
		return model.id == id;
	}

public:
	const ModelIdFieldType& id;
};

class IDataStoreNew
{
protected:
	template<typename ModelType>
	using IsValidModelType = typename std::is_convertible<ModelType*, IDatastoreModel*>::value;

	template<typename ModelType>
	using ValidModelType = typename std::enable_if<std::is_convertible<ModelType*, IDatastoreModel*>::value,ModelType>::type;

	template <typename T, typename = uint32_t>
	struct HasId : std::false_type { };

	template <typename T>
	struct HasId <T, decltype((void) T::x, 0)> : std::true_type {};

	typedef std::function<bool(const IDatastoreModel&)> SelectPredicateFn;

public:

	using TypeHash = decltype(std::declval<ctti::unnamed_type_id_t>().hash());

	virtual ~IDataStoreNew() = default;



	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>, ValidModelType<ModelType>>
	typename ModelType::ModelPtr loadModel(const SelectPredicate& predicate)
	{
		auto modelPtr = _load(ctti::unnamed_type_id<ModelType>().hash(), SelectPredicateFn(predicate));
		return std::static_pointer_cast<ModelType>(modelPtr);
	}


	template<typename ModelType, ValidModelType<ModelType>>
	bool saveModel(typename ModelType::ModelPtr& modelPtr)
	{
		return _save(ctti::unnamed_type_id<ModelType>().hash(), modelPtr);
	}



	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>, ValidModelType<ModelType>>
	bool insertModel(typename ModelType::ModelPtr& modelPtr)
	{
		static_assert(!HasId<ModelType>::value, "Model needs to have an id as primary key");
		if(!modelPtr)
			throw std::invalid_argument("nullptr value");
		if(modelPtr->id != 0)
			throw std::invalid_argument("model already has an id assigned");
		return _insert(ctti::unnamed_type_id<ModelType>().hash(), modelPtr);
	}



protected:

	virtual std::shared_ptr<IDatastoreModel> _load(TypeHash modelHash, std::function<bool(const std::shared_ptr<IDatastoreModel>&)> selectPredicate) = 0;
	virtual bool _save(TypeHash modelHash, const std::shared_ptr<IDatastoreModel>& modelPtr) = 0;
	virtual bool _insert(TypeHash modelHash, std::shared_ptr<IDatastoreModel> modelPtr) = 0;

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


	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>, typename ValidModelType<ModelType>::type>
	typename ModelType::ModelPtr loadModel(const SelectPredicate& predicate)
	{
		Derrived& d = static_cast<Derrived&>(*this);
		// prevent inf recursion
		if(&d.loadModel<ModelType, SelectPredicate> == &loadModel)
			throw std::logic_error("derrived did not overload this method");

		return d.loadModel(predicate);
	}

	template<typename ModelType, typename SelectPredicate=ModelById<ModelType>, typename ValidModelType<ModelType>::type>
	typename ModelType::ModelPtr saveModel(const ModelType& in, const SelectPredicate& predicate)
	{
		Derrived& d = static_cast<Derrived&>(*this);
		// prevent inf recursion
		if(&d.saveModel<ModelType, SelectPredicate> == &saveModel)
			throw std::logic_error("derrived did not overload this method");

		return d.saveModel(in, predicate);
	}


	template<typename ModelType, typename ValidModelType<ModelType>::type>
		typename ModelType::ModelPtr createModel(typename ModelType::ModelPtr& model)
	{
		static_assert(!HasId<ModelType>::value, "Model needs to have an id as primary key");
		if(!model)
			throw std::invalid_argument("nullptr value");
		if(model->id != 0)
			throw std::invalid_argument("model already has an id assigned");
		Derrived& d = static_cast<Derrived&>(*this);
		if(&d.createModel<ModelType> == &createModel)
			throw std::logic_error("derrived did not overload this method");
		return d.createModel(model);
	}

};



#endif /* IDATASTORE_H_ */
