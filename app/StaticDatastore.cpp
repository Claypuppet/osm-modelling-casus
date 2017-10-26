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
#include "AbonnementType.h"
#include "TariefSoort.h"
#include "Tarief.h"
#include "TariefSoortPrijs.h"
#include "Application.h"
#include "Standplaats.h"


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

	// AutoTypes
	auto personenAuto = createModel<AutoType>(AutoType::Create("Personsen auto"));
	auto stationWagen = createModel<AutoType>(AutoType::Create("Stationwagen"));

	// Abbonomenten
	auto abboGratis = createModel<AbonnementType>(AbonnementType::Create("Gratis", 0));
	auto abboBetlaad = createModel<AbonnementType>(AbonnementType::Create("Betaald", Geld(49, 95)));

	// Tariefsoorten
	auto tariefPerUur = createModel<tarieven::TariefSoort>(tarieven::TariefSoort::Create("Per uur", 0, 3600));
	auto tariefPerDag = createModel<tarieven::TariefSoort>(tarieven::TariefSoort::Create("Per dag", 0, 3600*24));
	auto tariefPerWerk = createModel<tarieven::TariefSoort>(tarieven::TariefSoort::Create("Per week", 0, 3600*24*7));
	auto tatiefPerWeekend = createModel<tarieven::TariefSoort>(tarieven::TariefSoort::Create("Per weekend", (1 << 6) | (1 << 7), 3600*24*2));

	// Standplaatsen
	//auto standPlaats1 = createMode<Standplaats>(Standplaats::Create())


	Application::getInstance().setBoeteTariefSoort(tariefPerUur);



}
