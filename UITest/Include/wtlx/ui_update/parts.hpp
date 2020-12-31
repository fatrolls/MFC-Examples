//
// parts.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef PARTS_HPP
#define PARTS_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

namespace wtlx
{
/////////////////////////////////////////////////////////////////////////////
// CParts state

class CPartsValue {
public:
	CPartsValue() : m_nParts(1) { m_aWidths[0] = -1; }
	CPartsValue(INT nParts, const INT* aWidths) : m_nParts(nParts) {
		memcpy(m_aWidths, aWidths, nParts * sizeof(INT));
	}
	INT Parts() const { return m_nParts; }
	INT* Widths() { return m_aWidths; }

private:
	INT m_nParts;
	INT m_aWidths[256];
};

class CParts : public single_state_base<CPartsValue> {
public:
	// Init
	bool UIInitParts(const value_type& val) {
		return set_state(val, value_type(), false);
	}
	template<class IntArray>
	bool UIInitParts(IntArray& array) {
		return set_state(value_type(sizeof(array)/sizeof(INT), array), value_type(), false);
	}
	bool UIInitLocalParts(const value_type& valDefault = value_type()) {
		return set_state(valDefault, valDefault, true);
	}
	template<class IntArray>
	bool UIInitLocalParts(IntArray& arrayDefault) {
		value_type status(sizeof(arrayDefault)/sizeof(INT), arrayDefault);
		return set_state(status, status, true);
	}
	bool UIInitLocalParts(const value_type& valDefault, const value_type& val) {
		return set_state(valDefault, val, true);
	}
	template<class IntArray>
	bool UIInitLocalParts(IntArray& arrayDefault, IntArray& array) {
		return set_state(value_type(sizeof(arrayDefault)/sizeof(INT), arrayDefault), 
			value_type status(sizeof(array)/sizeof(INT), array), true);
	}

	// Set
	bool UISetParts(const value_type& value) {
		return set_state(value);
	}
	template<class IntArray>
	bool UISetParts(IntArray& array) {
		return set_state(value_type(sizeof(array)/sizeof(INT), array));
	}
};

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // PARTS_HPP
