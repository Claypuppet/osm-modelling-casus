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
#include "RedcarModule.h"

#include <vector>
#include <algorithm>
#include <iostream>

namespace Core {

	using Deelautos::AutoType;
	using Deelautos::Deelauto;
	using Deelautos::Standplaats;
	using Klanten::Klant;
	using Producten::AbonnementType;
	using Producten::Reservering;
	using Tarieven::TariefSoort;
	using Tarieven::Tarief;
	using Tarieven::TariefSoortPrijs;
	using Tarieven::tariefSoortenPrijsLijst;
	using RedcardModule::RedcarModule;


StaticDatastore::StaticDatastore()
{
	// TODO Auto-generated constructor stub


	//auto& store = StaticDatastoreStoreage<Klant>::store;
	//std::sort(store.begin(), store.end(), [](auto& a, auto& b){ return a.id < b.id; });
	initStaticTestData();
}

StaticDatastore::~StaticDatastore()
{
	// TODO Auto-generated destructor stub
}


void StaticDatastore::initStaticTestData()
{
	std::cout << "INIT STATIC DATA" << std::endl;

	// AutoTypes
	auto personenAuto = createModel<AutoType>(AutoType::Create("Personsen auto"));
	auto stationWagen = createModel<AutoType>(AutoType::Create("Stationwagen"));

	// Abbonomenten
	auto abboGratis = createModel<AbonnementType>(AbonnementType::Create("Gratis", 0));
	auto abboBetlaad = createModel<AbonnementType>(AbonnementType::Create("Betaald", Geld(49, 95)));

	// Tariefsoorten
	auto tariefPerUur = createModel<TariefSoort>(TariefSoort::Create("Per uur", 0, 3600));
	auto tariefPerDag = createModel<TariefSoort>(TariefSoort::Create("Per dag", 0, 3600*24));
	auto tariefPerWeek = createModel<TariefSoort>(TariefSoort::Create("Per week", 0, 3600*24*7));
	auto tariefPerWeekend = createModel<TariefSoort>(TariefSoort::Create("Per weekend", (1 << 6) | (1 << 7), 3600*24*2));

	// Tariefsoort prijzen
	// Gratis / Personenauto
	auto tspGPU = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerUur, Geld(6,0)));
	auto tspGPD = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerDag, Geld(50,0)));
	auto tspGPW = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeekend, Geld(70,0)));
	auto tspGPWK = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeek, Geld(150,0)));
	// Betaald / Personenauto
	auto tspBPU = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerUur, Geld(4,0)));
	auto tspBPD = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerDag, Geld(40,0)));
	auto tspBPW = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeekend, Geld(60,0)));
	auto tspBPWK = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeek, Geld(140,0)));
	// Gratis / Stationwagon
	auto tspGSU = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerUur, Geld(7,50)));
	auto tspGSD = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerDag, Geld(60,0)));
	auto tspGSW = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeekend, Geld(90,0)));
	auto tspGSWK = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeek, Geld(180,0)));
	// Betaad / Stationwagon
	auto tspBSU = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerUur, Geld(5,50)));
	auto tspBSD = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerDag, Geld(50,0)));
	auto tspBSW = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeekend, Geld(80,0)));
	auto tspBSWK = createModel<TariefSoortPrijs>(TariefSoortPrijs::Create(tariefPerWeek, Geld(170,0)));

	// Tarieven
	tariefSoortenPrijsLijst tarievenGP = {tspGPU, tspGPD, tspGPWK, tspGPW};
	tariefSoortenPrijsLijst tarievenBP = {tspBPU, tspBPD, tspBPWK, tspBPW};
	tariefSoortenPrijsLijst tarievenGS = {tspGSU, tspGSD, tspGSWK, tspGSW};
	tariefSoortenPrijsLijst tarievenBS = {tspBSU, tspBSD, tspBSWK, tspBSW};
	auto tariefGP = createModel<Tarief>(Tarief::Create(0, Geld(0,30), tarievenGP, personenAuto, abboGratis));
	auto tariefBP = createModel<Tarief>(Tarief::Create(0, Geld(0,35), tarievenBP, personenAuto, abboBetlaad));
	auto tariefGS = createModel<Tarief>(Tarief::Create(100, Geld(0,25), tarievenGS, stationWagen, abboGratis));
	auto tariefBS = createModel<Tarief>(Tarief::Create(100, Geld(0,30), tarievenBS, stationWagen, abboBetlaad));

	// Klanten
	auto klant1 = createModel<Klant>(Klant::Create("Jelle Bouwhuis", "jelle@email.nl", 12345678, abboGratis));
	auto klant2 = createModel<Klant>(Klant::Create("Michel Peters", "michel@email.nl", 87654321, abboBetlaad));

	// RedCarModules
	auto moduleVoorDeelauto1 = createModel<RedcarModule>(RedcarModule::Create());
	auto moduleVoorDeelauto2 = createModel<RedcarModule>(RedcarModule::Create());

	// Standplaatsen
	auto standPlaatsVoorDeelauto1 = createModel<Standplaats>(Standplaats::Create(23432, "Arnhem"));
	auto standPlaatsVoorDeelauto2 = createModel<Standplaats>(Standplaats::Create(52342, "Arnhem"));

	// Deelautos
	auto deelAuto1 = createModel<Deelauto>(Deelauto::Create("AB-04-20", personenAuto, standPlaatsVoorDeelauto1, moduleVoorDeelauto1));
	auto deelAuto2 = createModel<Deelauto>(Deelauto::Create("AB-04-21", stationWagen, standPlaatsVoorDeelauto2, moduleVoorDeelauto2));

	// Reserveringen
	// 1509444000 = Tuesday, October 31, 2017 10:00:00
	// 1509472800 = Tuesday, October 31, 2017 18:00:00
	// 1509616800 = Thursday, November 2, 2017 10:00:00
	auto reservering1 = createModel<Reservering>(Reservering::Create(0, 60*60*7, klant1, deelAuto1, tariefPerUur));
	auto reservering2 = createModel<Reservering>(Reservering::Create(1509444000, 1509616800, klant2, deelAuto2, tariefPerDag));

	// Set boete tariefsoort
	Application::getInstance().setBoeteTariefSoort(tariefPerUur);

}

}
