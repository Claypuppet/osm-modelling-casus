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
#include "Deelauto.h"
#include "AutoType.h"

#include <algorithm>
#include "AbonnementType.h"

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

	// AutoTypes
	auto personenAuto = createModel<AutoType>(AutoType::Create("Personsen auto"));
	auto stationWagen = createModel<AutoType>(AutoType::Create("Stationwagen"));

	// Abbonomenten
	createModel<AbonnementType>(AbonnementType::Create("Gratis", 0));
	createModel<AbonnementType>(AbonnementType::Create("Betaald", Geld(49, 95)));


	// Klanten
	//Klant::Create(0, 112233, )
}
