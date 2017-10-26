/*
 * StaticDatastore.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "StaticDatastore.h"
#include "Klant.h"
#include "Reservering.h"
#include "Verhuur.h"
#include "AbbonomentType.h"
#include "Deelauto.h"

#include <algorithm>

StaticDatastore::StaticDatastore()
{
	// TODO Auto-generated constructor stub


	//auto& store = StaticDatastoreStoreage<Klant>::store;
	//std::sort(store.begin(), store.end(), [](auto& a, auto& b){ return a.id < b.id; });
}

StaticDatastore::~StaticDatastore()
{
	// TODO Auto-generated destructor stub
}


void StaticDatastore::initStaticTestData()
{

	createModel<Deelauto>(Deelauto::Create());
	//&saveModel<Deelauto, ModelById>;


	// Abbonomenten
	//createModel<AbbonomentType>(AbbonomentType::Create(0, "Gratis", 0));


	// Klanten
	//Klant::Create(0, 112233, )
}
