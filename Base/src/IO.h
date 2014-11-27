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
#include "AbstractHmiVar.h"
#include <vector>
//#include "Variant.h"

namespace luna
{
template<class T>class IOImpl { };
template<class T>class Input;

template<class T>class IO : public AbstractHmiVar
{
	public:
		enum class errors{ TypeMissmatch };
		IO();
		IO( const IO<T> &other );
		virtual ~IO();
		Input<T> toInput() const;
		Variant toVariant() override;
		const T value() const;
		void setValue( const T value );
		void setValue( Variant &value ) override;

	protected:
		std::shared_ptr<std::pair<T, std::mutex>> _value;

	private:
		std::shared_ptr<IOImpl<T>> pimpl_;
};

template<class T>class Input : public IO<T>
{
	public:
		Input( const IO<T> &io );
		Variant toVariant() override;

	private:
		Input();
		using IO<T>::setValue;
		using IO<T>::toInput;
		using IO<T>::_value;
};

}	//namespace luna


#endif /* IO_H_ */
