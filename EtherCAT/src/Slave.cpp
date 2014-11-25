/*
 * Slave.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#include "Slave.h"

namespace luna
{

Slave::Slave() : _slave_config{ nullptr }
{
}

Slave::Slave( Master *master, uint16_t alias, uint16_t position, uint16_t vendor_id, uint32_t product_code )
{
	if( !( _slave_config = ecrt_master_slave_config( master->_master, alias, position, vendor_id, product_code )) )
		throw errors::CreateSlaveConfig;
}

Slave::~Slave()
{
}

} /* namespace luna */
