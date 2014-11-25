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
		Input<uint16_t> getValue();

	private:
		IO<uint16_t> _value;
};

} /* namespace luna */

#endif /* EL3161_H_ */
