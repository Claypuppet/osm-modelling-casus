/*
 * Boete.h
 *
 *  Created on: Oct 26, 2017
 *      Author: klei
 */

#ifndef APP_BOETE_H_
#define APP_BOETE_H_

#include "DatastoreModel.h"
#include "Product.h"


namespace Producten
{

class Boete : public DatastoreModel<Boete>, public Product
{
	friend DatastoreModel<Boete>;

public:
	Geld getKosten();
	virtual ~Boete() = default;
	virtual std::string asString() override;

private:
	Boete(Geld kosten, std::string reden, uint32_t timeStamp);
	Boete(Geld kosten, std::string reden);

private:
	Geld kosten;
	std::string reden;
	uint32_t timeStamp;
};

}

#endif /* APP_BOETE_H_ */
