/*
 * Deelauto.h
 *
 *  Created on: 26 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef DEELAUTO_H_
#define DEELAUTO_H_

#include "DatastoreModel.h"
#include <string>
#include <memory>

class Standplaats;
class RedcarModule;
class AutoType;

class Deelauto : public DatastoreModel<Deelauto>
{
	friend DatastoreModel<Deelauto>;
	Deelauto();
	Deelauto(const std::string& kenteken, std::shared_ptr<Standplaats>& standplaats, std::shared_ptr<RedcarModule>& redcardModule);

public:
	~Deelauto() = default;

	std::shared_ptr<Standplaats> getStandPlaats() const;
	std::shared_ptr<RedcarModule> getRedcarModule() const;

public:
	std::string kenteken;
	std::shared_ptr<Standplaats> standplaats;
	std::shared_ptr<RedcarModule> redcardModule;
	std::shared_ptr<AutoType> type;

};

#endif /* DEELAUTO_H_ */
