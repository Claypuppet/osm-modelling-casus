/*
 * Verhuur.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Verhuur.h"
#include "Product.h"
#include "Boete.h"
#include "Signals.h"
#include "Application.h"


namespace Producten
{
	using Core::Application;
	using Core::Signals;
	using Tarieven::TariefSoortPtr;

Verhuur::Verhuur()
: incheckMoment(0)
, uitcheckMoment(0)
, aantalKilometers(0)
{
}

Verhuur::Verhuur(std::shared_ptr<Reservering> reservering, uint32_t incheckMoment, uint32_t uitcheckMoment, uint32_t aantalKilometers)
: reservering(reservering)
, incheckMoment(incheckMoment)
, uitcheckMoment(uitcheckMoment)
, aantalKilometers(aantalKilometers)
{

}

Geld Verhuur::berekenTeLaatBoeteKosten()
{
	int32_t deltaSec = uitcheckMoment - reservering->eindMoment;
	Geld kosten;
	if(deltaSec > 0) {
		TariefSoortPtr boeteSoort = Application::i().getBoeteTariefSoort();
		uint32_t aantal = deltaSec / boeteSoort->periode + (deltaSec % boeteSoort->periode ? 1 : 0);
		Tarieven::TariefPtr tarief = reservering->getTarief();
		kosten = tarief->berekenKosten(0, boeteSoort, aantal);
	}

	return kosten;
}

void Verhuur::setIncheckMoment(uint32_t moment)
{
	incheckMoment = moment;
}

void Verhuur::setUitcheckMoment(uint32_t moment)
{
	uitcheckMoment = moment;
}

void Verhuur::voltooi()
{
	if(!reservering->deelauto->checkOpLocatie()) {
		reservering->deelauto->verhuurVoltooid();
		setUitcheckMoment(Application::i().getNowMoment());
		if(uitcheckMoment > reservering->eindMoment){
			Geld kosten = berekenTeLaatBoeteKosten();
			auto boete = Boete::Create(kosten, "TE LAAT TERUG GEBRACHT!! :((");
			reservering->addBoete(boete);
		}
		reservering->maakFactuur();
		Signals::i().VehuurUitgeckect(shared_from_this());
	}
	else {
		Signals::i().VehuurUitcheckAutoNietOpLocatie(shared_from_this());
	}
}

}

