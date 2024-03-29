/*
 * DatastoreModel.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef DATASTOREMODEL_H_
#define DATASTOREMODEL_H_


#include <memory>

namespace Core {

struct IDatastoreModel {
	virtual ~IDatastoreModel() = default;
};

template<typename ModelType>
class DatastoreModel : public IDatastoreModel, public std::enable_shared_from_this<DatastoreModel<ModelType>>
{
public:

	typedef std::shared_ptr<ModelType> ModelPtr;
	typedef std::weak_ptr<ModelType> ptr;

	virtual ~DatastoreModel() = default;


	ModelPtr shared_from_this()
	{
		auto ptr = std::enable_shared_from_this<DatastoreModel<ModelType>>::shared_from_this();
		return std::static_pointer_cast<ModelType>(ptr);
	}

	template <typename... Args>
	static ModelPtr Create(Args&&... args)
	{
		return ModelPtr(new ModelType(std::forward<Args>(args)...));
	}


public:

	uint32_t id;

private:
	friend ModelType;
	DatastoreModel() : id(0) {}
	DatastoreModel(uint32_t id) : id(id) {}
};

}

#endif /* DATASTOREMODEL_H_ */
