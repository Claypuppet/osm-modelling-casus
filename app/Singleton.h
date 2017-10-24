/*
 * Singleton.h
 *
 *  Created on: 9 Oct 2017
 *      Author: Vuurvlieg
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_


template <typename T>
class Singleton
{
		friend T;

		Singleton() = default;
		Singleton(const Singleton&) = delete;

public:

#if __cplusplus >= 201103L
	static T& getInstance() { static T instance; return instance; }
#else
	// https://en.wikipedia.org/wiki/Double-checked_locking#Usage_in_C++11
# error "TODO: implement a double checked locking version for C++ versions < C++11"
#endif
};


#endif /* SINGLETON_H_ */
