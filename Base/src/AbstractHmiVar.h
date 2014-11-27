/*
 * AbstractHmiVar.h
 *
 *  Created on: Nov 26, 2014
 *      Author: john
 */

#ifndef ABSTRACTHMIVAR_H_
#define ABSTRACTHMIVAR_H_

#include <vector>
#include "Variant.h"

namespace luna
{

class AbstractHmiVar
{
	public:
		AbstractHmiVar();
		virtual ~AbstractHmiVar();
		virtual Variant toVariant() = 0;
		virtual void setValue( Variant &value ) = 0;
};

} /* namespace luna */

#endif /* ABSTRACTHMIVAR_H_ */
