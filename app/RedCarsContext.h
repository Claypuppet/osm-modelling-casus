/*
 * RedCarsContext.h
 *
 *  Created on: 28 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef REDCARSCONTEXT_H_
#define REDCARSCONTEXT_H_

#include "Singleton.h"
#include "KlantRepo.h"
#include "TariefRepo.h"
#include "VerhuurRepo.h"
#include "StaticDatastore.h"


namespace detail {
	template <typename DataStoreType>
	class RedCarsContextImpl : public Singleton<RedCarsContextImpl<DataStoreType>>
	{
		friend Singleton<RedCarsContextImpl<DataStoreType>>;

		RedCarsContextImpl()
		:	mKlantRepo(mDatastore)
		,	mVehuurRepo(mDatastore)
		,	mTariefRepo(mDatastore)
		{

		}

	public:
		~RedCarsContextImpl() = default;


		IDataStore<DataStoreType>& getDataStore()  { return mDatastore; }
		KlantRepo<DataStoreType>& getKlantRepo()  { return mKlantRepo; }
		VerhuurRepo<DataStoreType>& getVehuurRepo()  { return mVehuurRepo; }
		TariefRepo<DataStoreType>& getTariefRepo()  { return mTariefRepo; }

	private:
		DataStoreType mDatastore;
		KlantRepo<DataStoreType> mKlantRepo;
		VerhuurRepo<DataStoreType> mVehuurRepo;
		TariefRepo<DataStoreType> mTariefRepo;

	};
}

class RedCarsContext : public detail::RedCarsContextImpl<StaticDatastore> {
	using super = RedCarsContextImpl<StaticDatastore>;
public:
	static RedCarsContext& getInstance() { return static_cast<RedCarsContext&>(super::getInstance()); }
};



#endif /* REDCARSCONTEXT_H_ */
