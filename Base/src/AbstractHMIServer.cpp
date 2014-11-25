/*
 * AbstractHMIServer.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: john
 */

#include "AbstractHMIServer.h"
#include <sstream>
#include <exception>
#include "AbstractHMIVar.h"

namespace luna
{

AbstractHMIServer::AbstractHMIServer()
{
}

AbstractHMIServer::~AbstractHMIServer()
{
}

void AbstractHMIServer::addVar( AbstractHMIVar* var )
{
	if( var == nullptr )
		throw std::invalid_argument( "AbstractHMIServer::addVar. var was nullptr." );
	if( check_duplicate_entry( var->name() ) )
		throw std::invalid_argument( "AbstractHMIServer::addVar. Duplicate entry." );

	vars.push_back( var );
}

const std::string AbstractHMIServer::compose() const
{
	std::ostringstream ret;

	for( auto i : vars )
		ret << i->compose() << '\n';

	return ret.str();
}

bool AbstractHMIServer::check_duplicate_entry( const std::string name )
{
	for( auto v : vars )
		if( v->stringval().substr( 0, name.size() ) == name )
			return true;

	return false;
}

//AbstractHMIServer& AbstractHMIServer::operator <<( const AbstractHMIVar& var )
//{
//	return *this;
//}

}	//namespace luna
