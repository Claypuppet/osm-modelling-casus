/*
 * Application.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Application.h"

#include "RedCarsContext.h"
#include "StaticDatastore.h"
#include "Klant.h"

#include <iostream>
#include <thread>
#include <chrono>

Application::Application()
: mQuit(false)
{
	// TODO Auto-generated constructor stub

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
	RedCarsContext::getInstance();

	initUI();

}

int Application::main(int argc, char* argv[])
{
	init();
	while(!mQuit) {
		mCUI.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}

tarieven::TariefSoortPtr Application::getBoeteTariefSoort() const
{
	return boeteTariefSoort;
}

void Application::setBoeteTariefSoort(tarieven::TariefSoortPtr boeteTariefSoort)
{
	this->boeteTariefSoort = boeteTariefSoort;
}
