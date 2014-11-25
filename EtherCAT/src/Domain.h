/*
 * Domain.h
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Master.h"
#include "AbstractTerminal.h"
#include <vector>
#include <cinttypes>

namespace luna
{

class Domain
{
	public:
		enum class errors{ Unknown, Create, AddNull, FetchPD };
		Domain( Master &master );
		virtual ~Domain();
		void add( AbstractTerminal *term );
		void update();
		void fetchPD();

	private:
		ec_domain_t *_domain;
		uint8_t *_domain_pd;
		std::vector<AbstractTerminal *> _terminals;

};

} /* namespace luna */

#endif /* DOMAIN_H_ */
