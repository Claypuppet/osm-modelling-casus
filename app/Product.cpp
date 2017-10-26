/*
 * Producten.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Product.h"
#include "Boete.h"

Geld Product::getExtraKosten()
{
	return Geld(0);
	return std::accumulate(boetes.begin(), boetes.end(), Geld(0), [](Geld& g, const BoetePtr& b)
		{
			return g + b->getKosten();
		}
	);
}

Geld Product::getTotaalKosten()
{
	return getKosten() + getExtraKosten();
}
