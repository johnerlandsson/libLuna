/* Copyright (C) 2013 John Erlandsson

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "EL3202.h"
#include <iostream>
#include <bitset>

namespace luna
{

/** @param master Pointer to the overlaying master object
 * @param alias Slave alias
 * @param position Slave position
 */
EL3202::EL3202( Master *master, uint16_t alias, uint16_t position )
		 : AbstractTerminal( master, alias, position, VENDOR_BECKHOFF, PRODUCTCODE_EL3202 )
{
	_channels = new ec_pdo_entry_info_t[18];
	_channels[0] = { 0x6000, 0x01, 1 };		//Status underrange channel 1
	_channels[1] = { 0x6000, 0x02, 1 };		//Status overrange channel 1
	_channels[2] = { 0x6000, 0x03, 2 };		//Status limit1 channel 1
	_channels[3] = { 0x6000, 0x05, 2 };		//Status limit2 channel 1
	_channels[4] = { 0x6000, 0x07, 1 };		//Status error channel 1
	_channels[5] = { 0x0000, 0x00, 7 };		//Gap
	_channels[6] = { 0x1800, 0x07, 1 };		//Status TxPDO state channel 1
	_channels[7] = { 0x1800, 0x09, 1 };		//Status TxPDO toggle channel 1
	_channels[8] = { 0x6000, 0x11, 16 };		//Value channel 1
	_channels[9] = { 0x6010, 0x01, 1 };		//Status underrange channel 2
	_channels[10] = { 0x6010, 0x02, 1 };		//Status overrange channel 2
	_channels[11] = { 0x6010, 0x03, 2 };		//Status limit1 channel 2
	_channels[12] = { 0x6010, 0x05, 2 };		//Status limit2 channel 2
	_channels[13] = { 0x6010, 0x07, 1 };		//Status error channel 2
	_channels[14] = { 0x0000, 0x00, 7 };		//Gap
	_channels[15] = { 0x1810, 0x07, 1 };		//Status TxPDO state channel 2
	_channels[16] = { 0x1810, 0x09, 1 };		//Status TxPDO toggle channel 2
	_channels[17] = { 0x6010, 0x11, 16 };	//Value channel 2

	_pdos = new ec_pdo_info_t[2];
	_pdos[0] = { 0x1A00, 9, _channels };
	_pdos[1] = { 0x1A01, 9, _channels + 9 };

	_syncs = new ec_sync_info_t[5];
	_syncs[0] = { 0, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE };
	_syncs[1] = { 1, EC_DIR_INPUT, 0, nullptr, EC_WD_DISABLE };
	_syncs[2] = { 2, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE };
	_syncs[3] = { 3, EC_DIR_INPUT, 2, nullptr, EC_WD_DISABLE };
	_syncs[4] = { 0xFF };
}

EL3202::~EL3202()
{
}

/** Register pdo entry with index relevant to this terminal
 *  @param domain Pointer to overlaying domain object
 */
void EL3202::regPdoEntry( ec_domain_t *domain )
{
	regPdo( 0x6000, 0x01, domain );
}

/** Implementation of update.\n
 * Fetch process data for this terminal.
 * @param domain_pd Offset for overlaying domains process data
 */
void EL3202::update( uint8_t *domain_pd )
{
	uint8_t *totOffs = domain_pd + _offset;

	//Update underranges
	underranges[0].setValue( EC_READ_BIT( totOffs, 0 ) );
	underranges[1].setValue( EC_READ_BIT( totOffs + 4, 0 ) );

	//Update overranges
	overranges[0].setValue( EC_READ_BIT( totOffs, 1 ) );
	overranges[1].setValue( EC_READ_BIT( totOffs + 4, 1 ) );

	//Update limit 1
	std::bitset<2> tmp;
	tmp.set( 0, EC_READ_BIT( totOffs, 2 ) );
	tmp.set( 1, EC_READ_BIT( totOffs, 3 ) );
	limits1[0].setValue( tmp.to_ulong() );
	tmp.set( 0, EC_READ_BIT( totOffs + 4, 2 ) );
	tmp.set( 1, EC_READ_BIT( totOffs + 4, 3 ) );
	limits1[1].setValue( tmp.to_ulong() );

	//Update limit 1
	tmp.set( 0, EC_READ_BIT( totOffs, 4 ) );
	tmp.set( 1, EC_READ_BIT( totOffs, 5 ) );
	limits2[0].setValue( tmp.to_ulong() );
	tmp.set( 0, EC_READ_BIT( totOffs + 4, 4 ) );
	tmp.set( 1, EC_READ_BIT( totOffs + 4, 5 ) );
	limits2[1].setValue( tmp.to_ulong() );

	//Update errors
	errors[0].setValue( EC_READ_BIT( totOffs, 6 ) );
	errors[1].setValue( EC_READ_BIT( totOffs + 4, 6 ) );

	//Update TxPDO States
	tx_pdo_states[0].setValue( EC_READ_BIT( totOffs + 1, 6 ) );
	tx_pdo_states[1].setValue( EC_READ_BIT( totOffs + 4 + 1, 6 ) );

	//Update TxPDO Toggles
	tx_pdo_toggles[0].setValue( EC_READ_BIT( totOffs + 1, 7 ) );
	tx_pdo_toggles[1].setValue( EC_READ_BIT( totOffs + 4 + 1, 7 ) );

	//Update temperature values
	values[0].setValue( EC_READ_S16( totOffs + 2 ) );
	values[1].setValue( EC_READ_S16( totOffs + 4 + 2 ) );
	//TODO handle high resolution mode
	fValues[0].setValue( (double)values[0].value() / 10.0f );
	fValues[1].setValue( (double)values[1].value() / 10.0f );
}

Input<bool> EL3202::getUnderrangeStatus( const unsigned int channel )
{
	return underranges[channel].toInput();
}

Input<bool> EL3202::getOverrangeStatus( const unsigned int channel )
{
	return overranges[channel].toInput();
}

Input<bool> EL3202::getErrorStatus( const unsigned int channel )
{
	return errors[channel].toInput();
}

Input<bool> EL3202::getTxPdoStateStatus( const unsigned int channel )
{
	return tx_pdo_states[channel].toInput();
}

Input<bool> EL3202::getTxPdoToggleStatus( const unsigned int channel )
{
	return tx_pdo_toggles[channel].toInput();
}

Input<uint8_t> EL3202::getLimit1Status( const unsigned int channel )
{
	return limits1[channel].toInput();
}

Input<uint8_t> EL3202::getLimit2Status( const unsigned int channel )
{
	return limits2[channel].toInput();
}

Input<int16_t> EL3202::getInput( const unsigned int channel )
{
	return values[channel].toInput();
}

int16_t EL3202::getValue( const unsigned int channel )
{
	return values[channel].value();
}

Input<double> EL3202::getFormattedValue( const unsigned int channel )
{
	return fValues[channel].toInput();
}

} //namespace luna
