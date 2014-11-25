/*
 * AbstractTerminal.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#include "AbstractTerminal.h"

namespace luna
{

AbstractTerminal::AbstractTerminal() : _offset{ 0 }, _syncs{ nullptr }, _channels{ nullptr }, _pdos{ nullptr }
{
}

AbstractTerminal::AbstractTerminal( Master *master, uint16_t alias, uint16_t position, uint16_t vendor_id, uint32_t product_code )
				: Slave( master, alias, position, vendor_id, product_code ), _offset{ 0 }, _syncs{ nullptr }, _channels{ nullptr }, _pdos{ nullptr }
{
}

AbstractTerminal::~AbstractTerminal()
{
	if( _syncs != nullptr )
		delete _syncs;
	if( _channels != nullptr )
		delete _channels;
	if( _pdos != nullptr )
		delete _pdos;
}

/** Call the ecrt function to configure pdo using a ec_slave_syncs struct that should be setup in the derived class*/
void AbstractTerminal::configPdos()
{
	if( _syncs == nullptr )
		throw errors::SyncsIsNull;
	else
		ecrt_slave_config_pdos( _slave_config, EC_END, _syncs );
}

/** calls ecrt_slave_config_reg_pdo_entry to get offset for reading and writing
*/
unsigned int AbstractTerminal::regPdo( uint16_t index, uint8_t subindex, ec_domain_t *domain )
{
	_offset = ecrt_slave_config_reg_pdo_entry( _slave_config, index, subindex, domain, nullptr );

	return _offset;
}

} /* namespace luna */
