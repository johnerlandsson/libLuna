/*
 * AbstractHMIServer.h
 *
 *  Created on: Mar 25, 2014
 *      Author: john
 */

#ifndef ABSTRACTHMISERVER_H_
#define ABSTRACTHMISERVER_H_

#include <vector>
#include <string>
#include <thread>
#include <ostream>
//#include <cstdint>
#include <inttypes.h>

namespace luna
{
class AbstractHMIVar;
class AbstractHMIServer
{
	public:
		typedef struct
		{
			bool writeable;
			char name[32];
			char value[32];
			uint8_t type;
		}send_data_t;

		AbstractHMIServer();
		virtual ~AbstractHMIServer();
		void addVar( AbstractHMIVar *var );
//		AbstractHMIServer &operator<<( const AbstractHMIVar &var );

	protected:
		const std::string compose() const;

	private:
		std::vector<AbstractHMIVar*> vars;
		bool check_duplicate_entry( const std::string name );
//		std::ostream<send_data_t> send_buffer;
};

}	//namespace luna

#endif /* ABSTRACTHMISERVER_H_ */
