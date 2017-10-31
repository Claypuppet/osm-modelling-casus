/*
 * Producten.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#include "Product.h"
#include "Boete.h"
#include "RedCarsContext.h"

namespace Producten
{
using Core::RedCarsContext;

Geld Product::getExtraKosten()
{
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

void Product::addBoete(const BoetePtr boete)
{
	boetes.push_back(boete);
	RedCarsContext::i().getDataStore().createModel(boete);
}

void Product::maakFactuur()
{
}

}
