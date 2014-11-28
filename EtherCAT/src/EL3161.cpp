/*
 * EL3161.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: john
 */

#include "EL3161.h"
#include <bitset>

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

	_underrange.setValue( EC_READ_BIT( totOffs + 0, 0 ) );
	_overrange.setValue( EC_READ_BIT( totOffs + 0, 1 ) );

	std::bitset<2> tmp;
	tmp.set( 0, EC_READ_BIT( totOffs + 0, 2 ) );
	tmp.set( 1, EC_READ_BIT( totOffs + 0, 3 ) );
	_limit1.setValue( tmp.to_ulong() );

	tmp.set( 0, EC_READ_BIT( totOffs + 0, 4 ) );
	tmp.set( 0, EC_READ_BIT( totOffs + 0, 5 ) );
	_limit2.setValue( tmp.to_ulong() );

	_error.setValue( EC_READ_BIT( totOffs + 0, 6 ) );

	_tx_pdo_state.setValue( EC_READ_BIT( totOffs + 1, 6 ) );
	_tx_pdo_toggle.setValue( EC_READ_BIT( totOffs + 1, 7 ) );

	_value.setValue( EC_READ_S32( totOffs + 2 ) );
}

Input<int32_t> EL3161::getInput()
{
	return _value.toInput();
}

int32_t EL3161::getValue()
{
	return _value.value();
}

Input<bool> EL3161::getUnderrange()
{
	return _underrange.toInput();
}

Input<bool> EL3161::getOverrange()
{
	return _overrange.toInput();
}

Input<uint8_t> EL3161::getLimit1()
{
	return _limit1.toInput();
}

Input<uint8_t> EL3161::getLimit2()
{
	return _limit2.toInput();
}

Input<bool> EL3161::getError()
{
	return _error.toInput();
}

Input<bool> EL3161::getTxPdoState()
{
	return _tx_pdo_state.toInput();
}

Input<bool> EL3161::getTxPdoToggle()
{
	return _tx_pdo_toggle.toInput();
}

} /* namespace luna */
