/*
 * IO.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: john
 */

#include "IO.h"
#include <cstdint>
#include <sstream>
#include <bitset>

//TODO debug includes
#include <iostream>

namespace luna
{

template<class T>
IO<T>::IO()
	  : AbstractHMIVar{ "unnamed" }, _value{ std::make_shared<std::pair<T, std::mutex>>() }, pimpl_{ std::make_shared<IOImpl<T>>() }
{
	type_ = determineType();
}

template<class T>
IO<T>::IO( const std::string varname )
	  : AbstractHMIVar{ varname }, _value{ std::make_shared<std::pair<T, std::mutex>>() }, pimpl_{ std::make_shared<IOImpl<T>>() }
{
	type_ = determineType();
}

template<class T>
IO<T>::IO( const std::string varname, const bool writeable )
	  : AbstractHMIVar{ varname, writeable }, _value{ std::make_shared<std::pair<T, std::mutex>>() }, pimpl_{ std::make_shared<IOImpl<T>>() }
{
	type_ = determineType();
}

template<class T>
IO<T>::IO( const IO<T> &other ) : AbstractHMIVar( other ), _value{ other._value }, pimpl_{ other.pimpl_ }
{
}

template<class T>
IO<T>::IO( const IO<T> &other, std::string new_name ) : AbstractHMIVar( other, new_name ), _value{ other._value }, pimpl_{ other.pimpl_ }
{
}

template<class T>
Input<T> IO<T>::toInput() const
{
	return Input<T>( *this );
}

template<class T>
Input<T> IO<T>::toInput( std::string new_name )
{
	return Input<T>( *this, new_name );
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

template<class T>
T IO<T>::operator++()
{
	static_assert( std::is_arithmetic<T>::value, "Type needs to be arithmatic" );

	std::lock_guard<std::mutex> lock( _value->second );
	return (_value->first += 1);
}

template<class T>
T IO<T>::operator--()
{
	static_assert( std::is_arithmetic<T>::value, "Type needs to be arithmatic" );

	std::lock_guard<std::mutex> lock( _value->second );
	return (_value->first -= 1);
}

template<class T>
T IO<T>::operator+=( const T& other )
{
	static_assert( std::is_arithmetic<T>::value, "Type needs to be arithmatic" );

	std::lock_guard<std::mutex> lock( _value->second );
	return (_value->first += other);
}

template<class T>
T IO<T>::operator-=( const T& other )
{
	static_assert( std::is_arithmetic<T>::value, "Type needs to be arithmatic" );

	std::lock_guard<std::mutex> lock( _value->second );
	return (_value->first -= other);
}

template<class T>
const std::string IO<T>::stringval() const
{
	std::lock_guard<std::mutex> lock( _value->second );
	return std::to_string( _value->first );
}

template<class T>
AbstractHMIVar::VarTypes IO<T>::determineType() const
{
	if( std::is_same<T, int8_t>::value )
		return AbstractHMIVar::VarTypes::Int8;
	else if( std::is_same<T, uint8_t>::value )
		return AbstractHMIVar::VarTypes::UInt8;
	else if( std::is_same<T, int16_t>::value )
		return AbstractHMIVar::VarTypes::Int16;
	else if( std::is_same<T, uint16_t>::value )
		return AbstractHMIVar::VarTypes::UInt16;
	else if( std::is_same<T, int32_t>::value )
		return AbstractHMIVar::VarTypes::Int32;
	else if( std::is_same<T, uint32_t>::value )
		return AbstractHMIVar::VarTypes::UInt32;
	else if( std::is_same<T, int64_t>::value )
		return AbstractHMIVar::VarTypes::Int64;
	else if( std::is_same<T, uint64_t>::value )
		return AbstractHMIVar::VarTypes::UInt64;
	else if( std::is_same<T, double>::value )
		return AbstractHMIVar::VarTypes::Float;
	else if( std::is_same<T, bool>::value )
		return AbstractHMIVar::VarTypes::Bool;

	return AbstractHMIVar::VarTypes::Unknown;
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
	writeable_ = false;
}

template<class T>
Input<T>::Input( const IO<T> &io, std::string new_name ) : IO<T>{ io, new_name }
{
	writeable_ = false;
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
