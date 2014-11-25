/*
 * Domain.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#include "Domain.h"

namespace luna
{

Domain::Domain( Master &master ) : _domain_pd{ nullptr }
{
	_domain = ecrt_master_create_domain( master._master );
	if( _domain == nullptr )
		throw errors::Create;
}

Domain::~Domain()
{
}

void Domain::add( AbstractTerminal *term )
{
	if( term == nullptr )
		throw errors::AddNull;

	term->regPdoEntry( _domain );

	_terminals.push_back( term );
}

void Domain::update()
{
	ecrt_domain_process( _domain );

	for( auto t : _terminals )
		t->update( _domain_pd );

	ecrt_domain_queue( _domain );
}

void Domain::fetchPD()
{
	if( !(_domain_pd = ecrt_domain_data( _domain )) )
		throw errors::FetchPD;
}

} /* namespace luna */
