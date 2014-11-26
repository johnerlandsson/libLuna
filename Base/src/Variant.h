/*
 * Variant.h
 *
 *  Created on: Nov 26, 2014
 *      Author: john
 */

#ifndef VARIANT_H_
#define VARIANT_H_

#include <string>
#include <typeindex>
#include <memory>

namespace luna
{

class Variant
{
	public:
		struct invalid {};
		Variant();
		Variant( const bool writeable, const std::type_info type, const std::string value );
		virtual ~Variant();

	protected:
		bool _wr;
		std::unique_ptr<std::type_index> _type;
		std::string _value;
};

} /* namespace luna */

#endif /* VARIANT_H_ */
