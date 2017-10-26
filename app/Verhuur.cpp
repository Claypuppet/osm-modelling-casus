/*
 * Verhuur.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Verhuur.h"
#include "Product.h"
#include "Deelauto.h"
#include "Application.h"
#include "Boete.h"

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
		tarieven::TariefSoortPtr boeteSoort = Application::getInstance().getBoeteTariefSoort();
		uint32_t aantal = deltaSec / boeteSoort->periode;
		tarieven::TariefPtr tarief = reservering->getTarief();
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
		setUitcheckMoment(Application::getNowMoment());
		if(uitcheckMoment > reservering->eindMoment){
			Geld kosten = berekenTeLaatBoeteKosten();
			std::shared_ptr<Boete> boete = Boete::Create(kosten, "TE LAAT TERUG GEBRACHT!! :((");
			reservering->addBoete(boete);
		}
		reservering->maakFactuur();
	}
	else {

	}
}


