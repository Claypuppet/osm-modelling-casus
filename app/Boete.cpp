/*
 * Boete.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#include "Boete.h"
#include "Application.h"

//namespace producten
//{

Boete::Boete(Geld kosten, std::string reden, uint32_t timeStamp)
: kosten(kosten), reden(reden), timeStamp(timeStamp)
{
}

std::string Boete::asString()
{
	return "hier komt boete string";
}

Boete::Boete(Geld kosten, std::string reden)
: kosten(kosten), reden(reden), timeStamp(Application::i().getNowMoment())
{
}

Geld Boete::getKosten()
{
	return kosten;
}
//} /* namespace producten */
