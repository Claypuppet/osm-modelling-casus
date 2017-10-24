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

#include "KlantRepo.h"
#include "StaticDatastore.h"

class Application : public Singleton<Application>
{
public:
	Application();
	~Application();


	void init();
	void initUI();

	int main(int argc, char* argv[]);


	StaticDatastore& getDataStore();
	KlantRepo<StaticDatastore>& getKlantRepo();


private:

	bool	mQuit;
	cui::CUI mCUI;

	StaticDatastore mDatastore;
	KlantRepo<StaticDatastore> mKlantRepo;
};

#endif /* APPLICATION_H_ */
