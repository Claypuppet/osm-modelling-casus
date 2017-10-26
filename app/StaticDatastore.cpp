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
#include "AutoType.h"

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

	// AutoTypes
	auto personenAuto = createModel<AutoType>(AutoType::Create(0, "Personsen auto"));
	auto stationWagen = createModel<AutoType>(AutoType::Create(0, "Stationwagen"));

	// Abbonomenten
	createModel<AbbonomentType>(AbbonomentType::Create(0, "Gratis", 0));
	createModel<AbbonomentType>(AbbonomentType::Create(0, "Betaald", Geld(49, 95)));


	// Klanten
	//Klant::Create(0, 112233, )
}
