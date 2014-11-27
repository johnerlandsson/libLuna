/*
 * Variant.h
 *
 *  Created on: Nov 26, 2014
 *      Author: john
 */

#ifndef VARIANT_H_
#define VARIANT_H_

#include <vector>
#include <cinttypes>
#include <typeindex>
#include <memory>
#include <string>

namespace luna
{

class Variant
{
		friend class AbstractHmiVar;
	public:
		enum class errors{ NoType, EmptyValue };
		Variant();
		Variant( const Variant &other );
		Variant( const bool writeable, int8_t value );
		Variant( const bool writeable, uint8_t value );
		Variant( const bool writeable, int16_t value );
		Variant( const bool writeable, uint16_t value );
		Variant( const bool writeable, int32_t value );
		Variant( const bool writeable, uint32_t value );
		Variant( const bool writeable, int64_t value );
		Variant( const bool writeable, uint64_t value );
		Variant( const bool writeable, double value );
		Variant( const bool writeable, bool value );
		virtual ~Variant();
		std::string type_name();
		std::type_index type();
		int8_t toInt8();
		uint8_t toUint8();

	private:
		std::vector<int8_t> _value;
		int8_t _wr;
		std::unique_ptr<std::type_index> _type;

};

} /* namespace luna */

#endif /* VARIANT_H_ */
