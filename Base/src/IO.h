/*
 * IO.h
 *
 *  Created on: Mar 25, 2014
 *      Author: john
 */

#ifndef IO_H_
#define IO_H_

#include "AbstractHMIVar.h"
#include <mutex>
#include <memory>

namespace luna
{
template<class T>class IOImpl { };
template<class T>class Input;

template<class T>class IO : public AbstractHMIVar
{
	public:
		IO();
		IO( const std::string varname );
		IO( const std::string varname, const bool writeable );
		IO( const IO<T> &other );
		IO( const IO<T> &other, std::string new_name );
		Input<T> toInput() const;
		Input<T> toInput( std::string new_name );
		const T value() const;
		void setValue( const T value );
		T operator++();
		T operator--();
		T operator+=( const T &other );
		T operator-=( const T &other );
		const std::string stringval() const;


	protected:
		AbstractHMIVar::VarTypes determineType() const;
		using AbstractHMIVar::compose;
		using AbstractHMIVar::writeable_;
		using AbstractHMIVar::name_;
		using AbstractHMIVar::type_;

	private:
		std::shared_ptr<std::pair<T, std::mutex>> _value;
		std::shared_ptr<IOImpl<T>> pimpl_;
};

template<class T>class Input : public IO<T>
{
	public:
		Input( const IO<T> &io );
		Input( const IO<T> &io, std::string new_name );

	private:
		using IO<T>::writeable_;
		using IO<T>::setValue;
		using IO<T>::toInput;
		using IO<T>::name_;
};

}	//namespace luna


#endif /* IO_H_ */
