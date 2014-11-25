/*
 * Slave.h
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#ifndef SLAVE_H_
#define SLAVE_H_

#define VENDOR_BECKHOFF 0x00000002

extern "C"
{
#include <ecrt.h>
}

#include "Master.h"

namespace luna
{

class Slave
{
	public:
		enum class errors{ Unknown, CreateSlaveConfig };
		Slave();
		Slave( Master *master, uint16_t alias, uint16_t position, uint16_t vendor_id, uint32_t product_code );
		virtual ~Slave();

	protected:
		ec_slave_config_t *_slave_config;
};

} /* namespace luna */

#endif /* SLAVE_H_ */
