/*
 * StaticDatastore.cpp
 *
 *  Created on: 24 Oct 2017
 *      Author: Vuurvlieg
 */

#include "StaticDatastore.h"
#include "Klant.h"
#include "Reservering.h"
#include "Verhuur.h"
#include "AbbonomentType.h"

#include <algorithm>

StaticDatastore::StaticDatastore()
{
	// TODO Auto-generated constructor stub


	//auto& store = StaticDatastoreStoreage<Klant>::store;
	//std::sort(store.begin(), store.end(), [](auto& a, auto& b){ return a.id < b.id; });
}

StaticDatastore::~StaticDatastore()
{
	// TODO Auto-generated destructor stub
}

#define DEFINE_STORE(ModelType) \
		template<> StaticDatastoreStoreage<ModelType, ModelType>::VectorType StaticDatastoreStoreage<ModelType, ModelType>::store

DEFINE_STORE(Klant);
DEFINE_STORE(Reservering);
DEFINE_STORE(Verhuur);
DEFINE_STORE(AbbonomentType);



