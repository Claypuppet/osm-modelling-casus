/*
 * Signals.h
 *
 *  Created on: 28 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

#include "Singleton.h"
#include <boost/signals2.hpp>
#include <memory>

#define FDW_DECLARE_SHARED_OBJECT(namespaze, className) \
namespace namespaze { class className; } \
typedef std::shared_ptr<namespaze::className> className##Ptr

FDW_DECLARE_SHARED_OBJECT(Producten, Verhuur);


#undef FDW_DECLARE_SHARED_OBJECT


namespace Core {


class Signals : public Singleton<Signals> {
	friend Singleton<Signals>;
	Signals() = default;
	~Signals() = default;

public:

	template<typename... Args>
	using s = boost::signals2::signal<Args...>;

	s<void(VerhuurPtr verhuur)> VehuurIngecheckt;
	s<void(VerhuurPtr verhuur)> VehuurWasAlIngecheckt;
	s<void(VerhuurPtr verhuur)> VehuurUitgeckect;
	s<void(VerhuurPtr verhuur)> VehuurUitcheckAutoNietOpLocatie;
};

}




#endif /* SIGNALS_H_ */
