#ifndef EL1004_H_
#define EL1004_H_

#include "AbstractTerminal.h"
#include <IO.h>

#define PRODUCTCODE_EL1004 0x03EC3052

/** Implementation of LEcAbstractTerminal\n
 * Describes a Beckoff EL1004 terminal.\n
 * \n
 * 4 channel digital input terminal 24 VDC, 3 ms input filter
 */
namespace luna
{
class EL1004 : public AbstractTerminal
{
	public:
		EL1004();
		EL1004( Master *master, uint16_t alias, uint16_t position );
		virtual ~EL1004();
		Input<bool> getInput( uint8_t input );
		void regPdoEntry( ec_domain_t *domain ) override;
		void update( uint8_t *domain_pd ) override;

	private:
		IO<bool> inputs[4];

};

}
#endif /* EL1004_H_ */

/** @}*/
