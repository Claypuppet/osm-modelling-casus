/*
 * TariefSoort.h
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#ifndef APP_TARIEFSOORT_H_
#define APP_TARIEFSOORT_H_

#include "DatastoreModel.h"
#include <memory>

namespace tarieven
{

class TariefSoort : public DatastoreModel<TariefSoort>
{
public:
	virtual ~TariefSoort() = default;

public:
	std::string naam;
	uint8_t weekMask;
	uint32_t periode;

private:
	friend DatastoreModel<TariefSoort>;
	TariefSoort(std::string naam, uint8_t weekMask, uint32_t periode);
};

typedef std::shared_ptr<TariefSoort> TariefSoortPtr;

} /* namespace tarieven */

#endif /* APP_TARIEFSOORT_H_ */
