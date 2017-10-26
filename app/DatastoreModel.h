/*
 * DatastoreModel.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef DATASTOREMODEL_H_
#define DATASTOREMODEL_H_

#include <memory>

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

	template <typename... Args>
	static ModelPtr Create(Args&&... args)
	{
		return ModelPtr(new ModelType(std::forward<Args>(args)...));
	}

private:
	friend ModelType;
	DatastoreModel() = default;
};

#endif /* DATASTOREMODEL_H_ */
