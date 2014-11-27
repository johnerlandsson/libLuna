/*
 * Variant.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: john
 */

#include "Variant.h"

namespace luna
{

Variant::Variant() : _wr{ false }
{
}

Variant::Variant( const Variant &other ) : _value{ other._value }, _wr{ other._wr }, _type( new std::type_index( *other._type ) )
{
}

Variant::Variant( const bool writeable, int8_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	_value.push_back( value );
}

Variant::Variant( const bool writeable, uint8_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	_value.push_back( (int8_t)value );
}

Variant::Variant( const bool writeable, bool value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	_value.push_back( (int8_t)value );
}

Variant::Variant( const bool writeable, int16_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	int8_t *p = reinterpret_cast<int8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( p[i] );
}

Variant::Variant( const bool writeable, uint16_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	uint8_t *p = reinterpret_cast<uint8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( (int8_t)p[i] );
}

Variant::Variant( const bool writeable, int32_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	int8_t *p = reinterpret_cast<int8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( p[i] );
}

Variant::Variant( const bool writeable, uint32_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	uint8_t *p = reinterpret_cast<uint8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( (int8_t)p[i] );
}

Variant::Variant( const bool writeable, int64_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	int8_t *p = reinterpret_cast<int8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( p[i] );
}

Variant::Variant( const bool writeable, uint64_t value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	uint8_t *p = reinterpret_cast<uint8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( (int8_t)p[i] );
}

Variant::Variant( const bool writeable, double value ) : _wr{ (int8_t)writeable }, _type( new std::type_index( typeid( value ) ) )
{
	int8_t *p = reinterpret_cast<int8_t*>(&value);

	for( unsigned int i = 0; i < sizeof( value ); i++ )
		_value.push_back( p[i] );
}

Variant::~Variant()
{
}

std::string Variant::type_name()
{
	if( _type == nullptr )
		throw errors::NoType;

	return std::string{ _type->name() };
}

std::type_index Variant::type()
{
	if( _type == nullptr )
		throw errors::NoType;

	return *_type;
}

int8_t Variant::toInt8()
{
	if( _value.size() < 1 )
		throw errors::EmptyValue;

	return _value.at( 0 );
}

uint8_t Variant::toUint8()
{
	if( _value.size() < 1 )
		throw errors::EmptyValue;

	return (uint8_t)_value.at( 0 );
}

} /* namespace luna */
