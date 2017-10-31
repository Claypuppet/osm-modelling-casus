/*
 * Application.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Application.h"

#include "RedCarsContext.h"
#include "StaticDatastore.h"
#include "ReserveringController.h"

#include <iostream>
#include <thread>
#include <chrono>

namespace Core {

Application::Application()
: mQuit(false)
{
	timeProvider = std::make_shared<RealTimeProvider>();
}

Application::~Application()
{
	// TODO Auto-generated destructor stub
}

void Application::initUI()
{
	mCUI.initialize();
}

void Application::init()
{
	// initialize the context
//	initUI();

	Producten::ReserveringController rc;



	setTimeProvider(std::make_shared<FakeTimeProvider>(0));
	rc.verzilverReservering(12345678);
	setTimeProvider(std::make_shared<FakeTimeProvider>(getNowMoment() + (60 * 60 * 8))); // 8 hours later...
	rc.voltooiVerhuur(12345678);


}

int Application::main(int argc, char* argv[])
{
	init();
	while(!mQuit) {
//		mCUI.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}

Tarieven::TariefSoortPtr Application::getBoeteTariefSoort() const
{
	return boeteTariefSoort;
}

void Application::setBoeteTariefSoort(Tarieven::TariefSoortPtr boeteTariefSoort)
{
	this->boeteTariefSoort = boeteTariefSoort;
}

}
