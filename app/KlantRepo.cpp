/*
 * KlantRepo.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "KlantRepo.h"
#include "Klant.h"



template <typename T>
bool KlantRepo<T>::getKlantByPasNummer(uint32_t pasNummer, Klant& klant)
{
	auto klantByPasNummer = [pasNummer](const Klant& k){
		return k.pasNummmer == pasNummer; };
	return mDataStore.loadModel(klant, klantByPasNummer);
}
