#ifndef EL3202_H_
#define EL3202_H_


#include "AbstractTerminal.h"
#include <IO.h>

#define PRODUCTCODE_EL3202 0x0C823052

namespace luna
{

/** Implementation of LEcAbstractTerminal\n
 * Describes a Beckoff EL3202 terminal.\n
 * \n
 * 2 - channel input terminals Pt100 (RTD)
 */
class EL3202 : public AbstractTerminal
{
	public:
		EL3202();
		EL3202( Master *master, uint16_t alias, uint16_t position );
		virtual ~EL3202();
		void regPdoEntry( ec_domain_t *domain ) override;
		void update( uint8_t *domain_pd ) override;
		Input<bool> getUnderrangeStatus( const unsigned int channel );
		Input<bool> getOverrangeStatus( const unsigned int channel );
		Input<bool> getErrorStatus( const unsigned int channel );
		Input<bool> getTxPdoStateStatus( const unsigned int channel );
		Input<bool> getTxPdoToggleStatus( const unsigned int channel );
		Input<uint8_t> getLimit1Status( const unsigned int channel );
		Input<uint8_t> getLimit2Status( const unsigned int channel );
		Input<int16_t> getInput( const unsigned int channel );
		int16_t getValue( const unsigned int channel );
		Input<double> getFormattedValue( const unsigned int channel );

	private:
		IO<bool> underranges[2];
		IO<bool> overranges[2];
		IO<bool> errors[2];
		IO<bool> tx_pdo_states[2];
		IO<bool> tx_pdo_toggles[2];
		IO<uint8_t>limits1[2];
		IO<uint8_t>limits2[2];
		IO<int16_t> values[2];
		IO<double> fValues[2];
};

} //namespace luna

#endif /* LECEL3202_H_ */

/** @}*/
