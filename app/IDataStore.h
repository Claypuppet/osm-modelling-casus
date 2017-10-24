/*
 * IDataStore.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef IDATASTORE_H_
#define IDATASTORE_H_

#include <functional>
#include <type_traits>


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

template<typename Derrived>
class IDataStore
{
public:
	IDataStore() = default;
	~IDataStore() = default;


	template<typename ModelType, typename InstancePredicate=ModelById<ModelType>>
	bool loadModel(ModelType& out, const InstancePredicate& predicate)
	{
		Derrived& d = static_cast<Derrived&>(*this);
		// prevent inf recursion
		if(&d.loadModel<ModelType, InstancePredicate> == &loadModel)
			return false;

		return d.loadModel(out, predicate);
	}

	template<typename ModelType, typename InstancePredicate=ModelById<ModelType>>
	bool saveModel(const ModelType& in, const InstancePredicate& predicate)
	{
		Derrived& d = static_cast<Derrived&>(*this);
		// prevent inf recursion
		if(&d.saveModel<ModelType, InstancePredicate> == &saveModel)
			return false;

		return d.saveModel(in, predicate);
	}

};



#endif /* IDATASTORE_H_ */
