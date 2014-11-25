/*
 * Master.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#include "Master.h"
#include "Domain.h"

namespace luna
{

Master::Master()
{
	_master = ecrt_request_master( 0 );

	if( _master == nullptr )
		throw errors::Request;
}

Master::Master( unsigned int index )
{
	_master = ecrt_request_master( index );

	if( _master == nullptr )
		throw errors::Request;
}

Master::~Master()
{
}

void Master::activate()
{
	if( ecrt_master_activate( _master ) )
		throw errors::Activate;
}

void Master::deactivate()
{
	ecrt_master_deactivate( _master );
}

void Master::updateDomain( Domain *domain )
{
	ecrt_master_receive( _master );
	domain->update();
	ecrt_master_send( _master );
}

} /* namespace luna */
