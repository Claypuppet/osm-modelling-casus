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

//namespace producten
//{

class Boete : public DatastoreModel<Boete>, public Product
{

public:
	Geld getKosten();

private:
	Boete(Geld kosten, std::string reden, uint32_t timeStamp) : kosten(kosten), reden(reden), timeStamp(timeStamp){};
	Boete(Geld kosten, std::string reden): Boete(kosten, reden, 0){};
	virtual ~Boete() = default;

private:
	Geld kosten;
	std::string reden;
	uint32_t timeStamp;
};

//} /* namespace producten */

#endif /* APP_BOETE_H_ */
