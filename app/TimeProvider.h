/*
 * timeProfider.h
 *
 *  Created on: Oct 31, 2017
 *      Author: klei
 */

#ifndef APP_TIMEPROFIDER_H_
#define APP_TIMEPROFIDER_H_

#include <chrono>

namespace Core {

class ITimeProvider
{
public:
	virtual ~ITimeProvider() = default;
	virtual uint32_t getTime() const = 0;
protected:
	ITimeProvider() = default;
};

class RealTimeProvider : public ITimeProvider
{
public:
	RealTimeProvider() = default;
	virtual ~RealTimeProvider() = default;
	virtual uint32_t getTime() const override
	{
		return std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()).time_since_epoch().count();
	}
};

class FakeTimeProvider : public ITimeProvider
{
public:
	FakeTimeProvider(uint32_t fakeTime):fakeTime(fakeTime){};
	virtual ~FakeTimeProvider() = default;
	virtual uint32_t getTime() const override
	{
		return fakeTime;
	}
private:
	uint32_t fakeTime;
};

}


#endif /* APP_TIMEPROFIDER_H_ */
