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


#include <chrono>

class Application : public Singleton<Application>
{
public:
	Application();
	~Application();


	void init();
	void initUI();

	int main(int argc, char* argv[]);

	static uint32_t getNowMoment()
	{
		return std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()).time_since_epoch().count();
	}


	StaticDatastore& getDataStore();
	KlantRepo<StaticDatastore>& getKlantRepo();
	VerhuurRepo<StaticDatastore>& getVehuurRepo();
	TariefRepo<StaticDatastore>& getTariefRepo();

private:

	bool	mQuit;
	cui::CUI mCUI;

	StaticDatastore mDatastore;
	KlantRepo<StaticDatastore> mKlantRepo;
	VerhuurRepo<StaticDatastore> mVehuurRepo;
	TariefRepo<StaticDatastore> mTariefRepo;
};

#endif /* APPLICATION_H_ */
