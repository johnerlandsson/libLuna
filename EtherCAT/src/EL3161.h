/*
 * EL3161.h
 *
 *  Created on: Nov 25, 2014
 *      Author: john
 */

#ifndef EL3161_H_
#define EL3161_H_

#define PRODUCTCODE_EL3161 0x0c593052

#include "AbstractTerminal.h"
#include <IO.h>

namespace luna
{

class EL3161 : public AbstractTerminal
{
	public:
		EL3161();
		EL3161( Master *master, uint16_t alias, uint16_t position );
		virtual ~EL3161();
		void regPdoEntry( ec_domain_t *domain ) override;
		void update( uint8_t *domain_pd ) override;
		Input<int32_t> getInput();
		int32_t getValue();
		Input<bool> getUnderrange();
		Input<bool> getOverrange();
		Input<uint8_t> getLimit1();
		Input<uint8_t> getLimit2();
		Input<bool> getError();
		Input<bool> getTxPdoState();
		Input<bool> getTxPdoToggle();

	private:
		IO<int32_t> _value;
		IO<bool> _underrange;
		IO<bool> _overrange;
		IO<uint8_t> _limit1;
		IO<uint8_t> _limit2;
		IO<bool> _error;
		IO<bool> _tx_pdo_state;
		IO<bool> _tx_pdo_toggle;
};

} /* namespace luna */

#endif /* EL3161_H_ */
