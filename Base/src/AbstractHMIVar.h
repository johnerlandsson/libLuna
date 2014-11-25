/*
 * AbstractHMIVar.h
 *
 *  Created on: Mar 26, 2014
 *      Author: john
 */

#ifndef ABSTRACTHMIVAR_H_
#define ABSTRACTHMIVAR_H_

#include <string>
#include <cstdint>
#include <memory>
#include "AbstractHMIServer.h"

//class AbstractHMIServer;
namespace luna
{
class AbstractHMIVar
{
	public:
		enum class VarTypes : uint8_t { Unknown, Int8, Int16, Int32, Int64, UInt8, UInt16, UInt32, UInt64, Double, Float, Bool };
		AbstractHMIVar( std::string varname );
		AbstractHMIVar( std::string varname, bool writeable );
		AbstractHMIVar( std::string varname, bool writeable, VarTypes type );
		AbstractHMIVar( const AbstractHMIVar &other, std::string new_name );
		virtual ~AbstractHMIVar();
		virtual const std::string stringval() const = 0;
		const std::string name();

	protected:
		const std::string compose();
		std::string name_;
		bool writeable_;
		VarTypes type_;

	private:
		friend class AbstractHMIServer;
};

} /* namespace luna */

#endif /* ABSTRACTHMIVAR_H_ */
