/*
 * AbstractHMIVar.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: john
 */

#include "AbstractHMIVar.h"
#include <sstream>
#include <stdexcept>

namespace luna
{

AbstractHMIVar::AbstractHMIVar( std::string varname )
			   : name_{ varname }, writeable_{ true }, type_{ VarTypes::Unknown }
{
}

AbstractHMIVar::AbstractHMIVar( std::string varname, bool writeable )
			   : name_{ varname }, writeable_{ writeable }, type_{ VarTypes::Unknown }
{
}

AbstractHMIVar::AbstractHMIVar( std::string varname, bool writeable, VarTypes type )
			   : name_{ varname }, writeable_{ writeable }, type_{ type }
{
}

AbstractHMIVar::AbstractHMIVar( const AbstractHMIVar &other, std::string new_name ) : name_{ new_name }, writeable_{ other.writeable_ }, type_{ other.type_ }
{
}

AbstractHMIVar::~AbstractHMIVar()
{
}

const std::string AbstractHMIVar::compose()
{
	std::ostringstream ret;

	if( type_ == VarTypes::Unknown )
		throw std::runtime_error( "Var with unknown type published to HMI server." );
	if( name_.size() <= 0 )
		throw std::runtime_error( "Unnamed var published to HMI server." );

	ret << "n=" << name_ << ":v=" << stringval() << ":w=" << std::to_string( writeable_ ) << ":t=" << static_cast<int>( type_ );

	return ret.str();
}

const std::string AbstractHMIVar::name()
{
	return name_;
}

} /* namespace luna */
