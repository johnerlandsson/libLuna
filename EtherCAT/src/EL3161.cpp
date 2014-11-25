/*
 * EL3161.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: john
 */

#include "EL3161.h"

namespace luna
{

EL3161::EL3161()
{
}

EL3161::EL3161( Master* master, uint16_t alias, uint16_t position )
	   : AbstractTerminal( master, alias, position, VENDOR_BECKHOFF, PRODUCTCODE_EL3161 )
{
	_channels = new ec_pdo_entry_info_t[11];
	_channels[0] = { 0x6000, 0x01, 1 };		//Status underrange
	_channels[1] = { 0x6000, 0x02, 1 };		//Status overrange
	_channels[2] = { 0x6000, 0x03, 2 };		//Status limit1
	_channels[3] = { 0x6000, 0x05, 2 };		//Status limit2
	_channels[4] = { 0x6000, 0x07, 1 };		//Status error
	_channels[5] = { 0x0000, 0x00, 1 };		//Gap
	_channels[6] = { 0x0000, 0x00, 5 };		//Gap
	_channels[7] = { 0x6000, 0x0e, 1 };		//Sync error
	_channels[8] = { 0x6000, 0x0f, 1 };		//Status TxPDO
	_channels[9] = { 0x6000, 0x10, 1 };		//Status TxPDO
	_channels[10] = { 0x6000, 0x11, 16 };	//Value

	_pdos = new ec_pdo_info_t;
	_pdos[0] = { 0x1A00, 11, _channels };


	_syncs = new ec_sync_info_t[5];
	_syncs[0] = { 0, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE };
	_syncs[1] = { 1, EC_DIR_INPUT, 0, nullptr, EC_WD_DISABLE };
	_syncs[2] = { 2, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE };
	_syncs[3] = { 3, EC_DIR_INPUT, 2, nullptr, EC_WD_DISABLE };
	_syncs[4] = { 0xFF };
}

EL3161::~EL3161()
{
}

void EL3161::regPdoEntry( ec_domain_t* domain )
{
	regPdo( 0x6000, 0x01, domain );
}

void EL3161::update( uint8_t* domain_pd )
{
	uint8_t *totOffs = domain_pd + _offset;
	_value.setValue( EC_READ_U16( totOffs + 2 ) );
}

Input<uint16_t> EL3161::getValue()
{
	return _value.toInput();
}

} /* namespace luna */
