//
// style.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STYLE_HPP
#define STYLE_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

namespace wtlx
{
/////////////////////////////////////////////////////////////////////////////
// CStyle state

class CStyle : public state_base<BYTE> {

public:
	enum { Enable = 0x01, Visible = 0x02, Checked = 0x04, Radio = 0x08, Default = 0x10 };

public:
	// base operations
	bool UIAddStyle(command_t nCmd, value_type val = Enable|Visible) { 
		return add_state(nCmd, val, val, false);
	}
	bool UIAddLocalStyle(command_t nCmd, value_type valDefault = Visible) { 
		return add_state(nCmd, valDefault, valDefault, true);
	}
	bool UIAddLocalStyle(command_t nCmd, value_type valDefault, value_type val) { 
		return add_state(nCmd, val, valDefault, true);
	}
	bool UIDeleteStyle(command_t nCmd) { 
		return remove_state(nCmd);
	}

	// styles
	bool UISetStyle(command_t nCmd, value_type val) {
		value_type prev;
		if(!value(nCmd, prev) || !(~prev & val))
			return false;
		return set_state(nCmd, prev|val);
	}
	bool UIGetStyle(command_t nCmd, value_type& val) {
		return value(nCmd, val);
	}
	bool UIRemoveStyle(command_t nCmd, value_type val) {
		value_type prev;
		if(!value(nCmd, prev) || !(prev & val))
			return false;
		return set_state(nCmd, prev & ~val);
	}

	// enable
	bool UISetEnable(command_t nCmd, bool val = true) {
		if(val)
			return UISetStyle(nCmd, Enable);
		return UIRemoveStyle(nCmd, Enable);
	}
	bool UIGetEnable(command_t nCmd, bool& val) {
		value_type v;
		if(!value(nCmd, v))
			return false;
		val = ((Enable&v) != 0);
		return true;
	}

	// visible
	bool UISetVisible(command_t nCmd, bool val = true) {
		if(val)
			return UISetStyle(nCmd, Visible);
		return UIRemoveStyle(nCmd, Visible);
	}
	bool UIGetVisible(command_t nCmd, bool& val) {
		value_type v;
		if(!value(nCmd, v))
			return false;
		val = ((Visible&v) != 0);
		return true;
	}

	// checked
	bool UISetCheck(command_t nCmd, bool val = true) {
		if(val)
			return UISetStyle(nCmd, Checked);
		return UIRemoveStyle(nCmd, Checked);
	}
	bool UIGetCheck(command_t nCmd, bool& val) {
		value_type v;
		if(!value(nCmd, v))
			return false;
		val = ((Checked&v) != 0);
		return true;
	}
};

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // STYLE_HPP
