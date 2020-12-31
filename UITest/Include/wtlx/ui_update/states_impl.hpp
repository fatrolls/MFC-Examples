//
// states_impl.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STATES_IMPL_HPP
#define STATES_IMPL_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

//#ifdef _MAP_
//#else
//#endif

namespace wtlx {

/////////////////////////////////////////////////////////////////////////////
// CUIStates

template<STATE_TMPL> 
class CUIStates : public typelist::inherit_all<make_list<STATE_TMPL_ARG>::result> {

public:
	typedef CUIStates self;
	typedef make_list<STATE_TMPL_ARG>::result state_list_t;

/*
	enum { 
		state_id01 = 0x00000001, state_id02 = 0x00000002, state_id03 = 0x00000004, state_id04 = 0x00000008, 
		state_id05 = 0x00000010, state_id06 = 0x00000020, state_id07 = 0x00000040, state_id08 = 0x00000080,
		state_id09 = 0x00000100, state_id10 = 0x00000200, state_id11 = 0x00000400, state_id12 = 0x00000800,
		state_id13 = 0x00001000, state_id14 = 0x00002000, state_id15 = 0x00004000, state_id16 = 0x00008000,
		state_id17 = 0x00010000, state_id18 = 0x00020000, state_id19 = 0x00040000, state_id20 = 0x00080000,
		state_id21 = 0x00100000, state_id22 = 0x00200000, state_id23 = 0x00400000, state_id24 = 0x00800000,
		state_id25 = 0x01000000, state_id26 = 0x02000000, state_id27 = 0x04000000, state_id28 = 0x08000000,
		state_id29 = 0x10000000, state_id30 = 0x20000000, state_id31 = 0x40000000, state_id32 = 0x80000000
	};
*/
	// converts type of UI element to UI's id
/*
	template<class State> struct state2id { 
		enum{ id = 0x00000001 << typelist::index_of<state_list_t, State>::value };
	};
*/
//public:
//	typedef S01 State01; typedef S02 State02; typedef S03 State03; typedef S04 State04;
//	typedef S05 State05; typedef S06 State06; typedef S07 State07; typedef S08 State08;
//	typedef S09 State09; typedef S10 State10; typedef S11 State11; typedef S12 State12;
//	typedef S13 State13; typedef S14 State14; typedef S15 State15; typedef S16 State16; 
//	typedef S17 State17; typedef S18 State18; typedef S19 State19; typedef S20 State20; 
//	typedef S21 State21; typedef S22 State22; typedef S23 State23; typedef S24 State24; 
//	typedef S25 State25; typedef S26 State26; typedef S27 State27; typedef S28 State28; 
//	typedef S29 State29; typedef S30 State30; typedef S31 State31; typedef S32 State32;

public:
	void UISetDefault() {
		helper<state_list_t>::set_default_state(*this);
	}

public:
	// apply_states
	template<class Handle, class UI>
	void apply_states(Handle h, UI& ui) {
		helper<state_list_t>::update_state(*this, h, ui);
	}

	// clean_states
	void clean_states(ui_type id = status_dirty) {
		helper<state_list_t>::clean_state(*this, id);
	}

//private:
public:
	// helper
	template<class L> struct helper {
		// set_default_state
		static void set_default_state(self& x) {
			static_cast<L::head&>(x).set_default_value();
			helper<L::tail>::set_default_state(x);
		}

		// update_state
		template<typename Handle, typename UI>
		static void update_state(self& x, Handle h, UI& ui) {
			ui.update_state(h, static_cast<L::head&>(x));
			helper<L::tail>::update_state(x, h, ui);
		}

		// clean_state_helper
		static void clean_state(self& x, ui_type id) {
			static_cast<L::head&>(x).clean(id);
			helper<L::tail>::clean_state(x, id);
		}
	};
	template<> struct helper<nil> {
		static void set_default_state(self&) {}
		template<typename Handle, typename UI> static void update_state(self&, Handle, UI&) {}
		static void clean_state(self&, ui_type) {}
	};
};

/////////////////////////////////////////////////////////////////////////////
// single_state_base

template<class Value>
class single_state_base {

public:
	typedef Value value_type;

private:
	ui_type m_dirty;
	bool m_default;
	value_type m_value;
	value_type m_default_value;

public:
	single_state_base() : m_dirty(status_clear), m_default(false), m_value(value_type()), 
		m_default_value(value_type()) {}

	bool set_state(const value_type& value, const value_type& valueDef, bool isDefault) {
		m_value = value; 
		m_default_value = valueDef;
		m_default = isDefault;
		m_dirty = status_dirty;
		return true;
	}
	bool set_state(const value_type& value) {
		m_value = value; 
		m_dirty = status_dirty;
		return true;
	}
	const value_type& value() const { 
		return m_value;
	}
	bool is_default() const {
		return m_default;
	}
	const value_type& default_value() const { 
		return m_default_value;
	}
	void set_default_value() { 
		if(m_default)
			set_state(m_default_value);
	}
	bool dirty(ui_type id) const { 
		return ((m_dirty & id) != 0);
	}
	void clean(ui_type id = status_dirty) {
		m_dirty &= ~id;
	}
};

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // STATES_IMPL_HPP
