/*
 * IO.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: john
 */

#include "IO.h"
#include <cstdint>
#include <sstream>

namespace luna
{

template<class T>
IO<T>::IO()
	  : _value{ std::make_shared<std::pair<T, std::mutex>>() }, pimpl_{ std::make_shared<IOImpl<T>>() }
{
}
template<class T>
IO<T>::IO( const IO<T> &other ) :  _value{ other._value }, pimpl_{ other.pimpl_ }
{
}

template<class T>
IO<T>::~IO()
{
}

template<class T>
Input<T> IO<T>::toInput() const
{
	return Input<T>( *this );
}

template<class T>
Variant IO<T>::toVariant()
{
	std::lock_guard<std::mutex> lock( _value->second );
	return Variant( true, _value->first );
}

template<class T>
const T IO<T>::value() const
{
	std::lock_guard<std::mutex> lock( _value->second );
	return _value->first;
}

template<class T>
void IO<T>::setValue( const T value )
{
	std::lock_guard<std::mutex> lock( _value->second );
	_value->first = value;
}

template<>
void IO<int8_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
	_value->first = value.toInt8();
}

template<>
void IO<uint8_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
	_value->first = value.toUint8();
}

template<>
void IO<int16_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<uint16_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<int32_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<uint32_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<int64_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<uint64_t>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<bool>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template<>
void IO<double>::setValue( Variant &value )
{
	if( value.type() != typeid( _value->first ) )
		throw errors::TypeMissmatch;

	std::lock_guard<std::mutex> lock( _value->second );
}

template class IO<int8_t>;
template class IO<uint8_t>;
template class IO<int16_t>;
template class IO<uint16_t>;
template class IO<int32_t>;
template class IO<uint32_t>;
template class IO<int64_t>;
template class IO<uint64_t>;
template class IO<bool>;
template class IO<double>;

template<class T>
Input<T>::Input( const IO<T> &io ) : IO<T>{ io }
{
}

template<class T>
Variant Input<T>::toVariant()
{
	std::lock_guard<std::mutex> lock( _value->second );
	return Variant( true, _value->first );
}

template<class T>
Input<T>::Input()
{
}

template class Input<int8_t>;
template class Input<uint8_t>;
template class Input<int16_t>;
template class Input<uint16_t>;
template class Input<int32_t>;
template class Input<uint32_t>;
template class Input<int64_t>;
template class Input<uint64_t>;
template class Input<bool>;
template class Input<double>;

}	//namespace luna
