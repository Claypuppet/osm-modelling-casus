/*
 * Application.h
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Singleton.h"
#include "cui/CUI.h"

#include "StaticDatastore.h"
#include "KlantRepo.h"
#include "VerhuurRepo.h"
#include "TariefRepo.h"
#include "TimeProvider.h"

namespace Core {
using Tarieven::TariefSoortPtr;

class Application : public Singleton<Application>
{
public:
	Application();
	~Application();


	void init();
	void initUI();

	int main(int argc, char* argv[]);

	uint32_t getNowMoment()
	{
		return timeProvider->getTime();
	}

	void setTimeProvider(std::shared_ptr<ITimeProvider> aTimeProvider){
		timeProvider = aTimeProvider;
	}

	TariefSoortPtr getBoeteTariefSoort() const;
	void setBoeteTariefSoort(TariefSoortPtr boeteTariefSoort);

private:

	bool	mQuit;
	cui::CUI mCUI;
	TariefSoortPtr boeteTariefSoort;
	std::shared_ptr<ITimeProvider> timeProvider;

};

}

#endif /* APPLICATION_H_ */
