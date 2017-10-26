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
	friend DatastoreModel<Boete>;

public:
	Geld getKosten();
	virtual ~Boete() = default;

private:
	Boete(Geld kosten, std::string reden, uint32_t timeStamp);
	Boete(Geld kosten, std::string reden);

private:
	Geld kosten;
	std::string reden;
	uint32_t timeStamp;
};

//} /* namespace producten */

#endif /* APP_BOETE_H_ */
