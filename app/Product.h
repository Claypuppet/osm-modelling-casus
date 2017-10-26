/*
 * Producten.h
 *
 *  Created on: 25 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

#include "Geld.h"

class Product
{
public:
	virtual ~Product() = default;
	virtual Geld getKosten() = 0;
};



#endif /* PRODUCTEN_H_ */
