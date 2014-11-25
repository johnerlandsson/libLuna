/*
 * AbstractTerminal.h
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#ifndef ABSTRACTTERMINAL_H_
#define ABSTRACTTERMINAL_H_

#include "Master.h"
#include "Slave.h"

extern "C"
{
#include <ecrt.h>
}

namespace luna
{

class Domain;
class AbstractTerminal : public Slave
{
	friend class Domain;
	public:
		enum class errors{ Unknown, SyncsIsNull };
		AbstractTerminal();
		AbstractTerminal( Master *master, uint16_t alias, uint16_t position, uint16_t vendor_id, uint32_t product_code );
		virtual ~AbstractTerminal();
		void configPdos();

	protected:
		virtual void update( uint8_t *domain_pd ) = 0;
		virtual void regPdoEntry( ec_domain_t *domain ) = 0;
		unsigned int regPdo( uint16_t index, uint8_t subindex, ec_domain_t *domain );
		unsigned int _offset;
		ec_sync_info_t *_syncs;
		ec_pdo_entry_info_t *_channels;
		ec_pdo_info_t *_pdos;
};

} /* namespace luna */

#endif /* ABSTRACTTERMINAL_H_ */
