/*
 * Master.h
 *
 *  Created on: Nov 24, 2014
 *      Author: john
 */

#ifndef MASTER_H_
#define MASTER_H_

extern "C"
{
#include <ecrt.h>
}

namespace luna
{

class Domain;
class Slave;
class Master
{
	friend class Domain;
	friend class Slave;

	public:
		enum class errors{ Unknown, Request, Activate };
		Master();
		Master( unsigned int index );
		virtual ~Master();
		void activate();
		void deactivate();
		void updateDomain( Domain *domain );

	protected:
		ec_master_t *_master;
};

} /* namespace luna */

#endif /* MASTER_H_ */
