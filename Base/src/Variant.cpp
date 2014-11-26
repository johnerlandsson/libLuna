/*
 * Variant.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: john
 */

#include "Variant.h"

namespace luna
{

Variant::Variant() : _wr{ false }, _type{ nullptr }, _value{}
{
}

Variant::Variant( bool writeable, std::type_info type, std::string value ) : _wr{ writeable }, _type{ new std::type_index( type ) }, _value{ value }
{
}

Variant::~Variant()
{
}

} /* namespace luna */
