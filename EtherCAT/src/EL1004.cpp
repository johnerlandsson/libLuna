
#include "EL1004.h"

namespace luna
{
/* Constructor
 *
 */
EL1004::EL1004()
{
}

/** @param master Pointer to the overlaying master object
 * @param alias Slave alias
 * @param position Slave position
 */
EL1004::EL1004( Master *master, uint16_t alias, uint16_t position )
		 : AbstractTerminal( master, alias, position, VENDOR_BECKHOFF, PRODUCTCODE_EL1004 )
{
	_channels = new ec_pdo_entry_info_t[4];
	for( int i = 0; i < 4; i++ )
	{
		_channels[i].index = 0x6000 + (i * 0x10);
		_channels[i].subindex = 0x01;
		_channels[i].bit_length = 1;
	}

	_pdos = new ec_pdo_info_t[4];
	for( int i = 0; i < 4; i++ )
		_pdos[i] = { 0xA00 + 1, 1, &_channels[i] };

	_syncs = new ec_sync_info_t[2];
	_syncs[0] = { 0, EC_DIR_INPUT, 4, _pdos, EC_WD_DISABLE };
	_syncs[1] = { 0xFF };
}

EL1004::~EL1004()
{
}

/** Getter for input object
 * @param input Input number to return
 */
Input<bool> EL1004::getInput( uint8_t input )
{
	return inputs[input].toInput();
}

/** Register pdo entry with index relevant to this terminal
 *  @param domain Pointer to overlaying domain object
 */
void EL1004::regPdoEntry( ec_domain_t *domain )
{
	regPdo( 0x6000, 0x01, domain );
}

/** Implementation of update.\n
 * Fetch process data for this terminal.
 * @param domain_pd Offset for overlaying domains process data
 */
void EL1004::update( uint8_t *domain_pd )
{
	uint8_t *totOffs = domain_pd + _offset;

	for( int i = 0; i < 4; i++ )
		inputs[i].setValue( (bool)EC_READ_BIT( totOffs, i ) );
}

}
