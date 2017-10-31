/*
 * Producten.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "Geld.h"
#include <vector>
#include <memory>
#include <numeric>

class Boete;

typedef std::shared_ptr<Boete> BoetePtr;
typedef std::vector<BoetePtr> boeteList;

class Product
{

public:
	virtual ~Product() = default;
	virtual Geld getKosten() = 0;
	virtual Geld getExtraKosten() final;
	virtual Geld getTotaalKosten() final;
	virtual std::string asString() = 0;

protected:
	boeteList boetes;

protected:
	Product() = default;
	Product(boeteList boetes) : boetes(boetes){};
	void addBoete(const BoetePtr b);
	void maakFactuur();

};



#endif /* PRODUCTEN_H_ */
