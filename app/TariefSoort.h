/*
 * TariefSoort.h
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#ifndef APP_TARIEFSOORT_H_
#define APP_TARIEFSOORT_H_

#include <memory>

namespace tarieven
{

class TariefSoort
{
public:
	TariefSoort();
	virtual ~TariefSoort();

private:
	std::string naam;
	uint8_t weekMask;
	uint32_t periode;
};

typedef std::shared_ptr<TariefSoort> TariefSoortPtr;

} /* namespace tarieven */

#endif /* APP_TARIEFSOORT_H_ */
