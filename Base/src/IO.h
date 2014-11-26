/*
 * IO.h
 *
 *  Created on: Mar 25, 2014
 *      Author: john
 */

#ifndef IO_H_
#define IO_H_

#include <mutex>
#include <memory>

namespace luna
{
template<class T>class IOImpl { };
template<class T>class Input;

template<class T>class IO
{
	public:
		IO();
		IO( const IO<T> &other );
		virtual ~IO();
		Input<T> toInput() const;
		const T value() const;
		void setValue( const T value );
		T operator++();
		T operator--();
		T operator+=( const T &other );
		T operator-=( const T &other );
		const std::string stringval() const;

	private:
		std::shared_ptr<std::pair<T, std::mutex>> _value;
		std::shared_ptr<IOImpl<T>> pimpl_;
};

template<class T>class Input : public IO<T>
{
	public:
		Input( const IO<T> &io );

	private:
		using IO<T>::setValue;
		using IO<T>::toInput;
};

}	//namespace luna


#endif /* IO_H_ */
