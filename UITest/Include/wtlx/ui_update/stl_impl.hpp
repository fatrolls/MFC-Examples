//
// stl_impl.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STL_IMPL_HPP
#define STL_IMPL_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

#include <string>
#include <wtlx/type_list.hpp>

namespace wtlx
{
/////////////////////////////////////////////////////////////////////////////
// state_base

template<class Value>
class state_base {

public:
	typedef Value value_type;

private:
	struct holder_t {
		holder_t() : m_dirty(status_clear), m_default(false), 
			m_value(value_type()), m_default_value(value_type()) {}
		holder_t(ui_type dirty, bool bDef, const value_type& val, const value_type& valDef) :
			m_dirty(dirty), m_default(bDef), m_value(val), m_default_value(valDef) {}
		ui_type m_dirty;
		bool m_default;
		value_type m_value;
		value_type m_default_value;
	};
	typedef std::map<command_t, holder_t> container_t;

public:
	typedef std::map<command_t, holder_t>::const_iterator iterator;

public:
	state_base() : m_dirty(status_clear) {}

	bool add_state(command_t command, const value_type& value, const value_type& valueDef = value_type(), 
		bool isDefault = false) {
		m_commands[command] = holder_t(status_dirty, isDefault, value, valueDef);
		m_dirty = status_dirty;
		return true;
	}
	bool remove_state(command_t command) { 
		return (m_commands.erase(command) != 0); 
	}
	bool set_state(command_t command, const value_type& value) {
		container_t::iterator it = m_commands.find(command);
		if(it == m_commands.end())
			return false;

		holder_t& holder = (*it).second;
		holder.m_dirty = status_dirty; 
		holder.m_value = value; 
		m_dirty = status_dirty;
		return true;
	}

public:
	iterator begin() const { 
		return m_commands.begin(); 
	}
	iterator end() const { 
		return m_commands.end(); 
	}
	command_t command(iterator it) const { 
		return (*it).first; 
	}
	const value_type& value(iterator it) const { 
		return (*it).second.m_value;
	}
	bool value(command_t command, value_type& val) const {
		iterator it = m_commands.find(command);
		if(it == m_commands.end())
			return false;

		val = (*it).second.m_value;
		return true;
	}
	bool is_default(iterator it) const {
		return (*it).second.m_default;
	}
	const value_type& default_value(iterator it) const { 
		return (*it).second.m_default_value;
	}
	void default_value(iterator it, const value_type& value) { 
		m_commands[(*it).first].second.m_default_value = value;
	}
	void set_default_value() { 
		for(container_t::iterator it = m_commands.begin(); it != m_commands.end(); ++it) {
			holder_t& holder = (*it).second;
			if(holder.m_default) {
				holder.m_dirty = status_dirty; 
				holder.m_value = holder.m_default_value;
				m_dirty = status_dirty;
			}
		}
	}
	bool dirty(ui_type id) const { 
		return ((m_dirty & id) != 0);
	}
	bool dirty(ui_type id, iterator it) const {
		return (((*it).second.m_dirty &id) != 0); 
	}
	void clean(ui_type id = status_dirty) {
		m_dirty &= ~id;
		for(container_t::iterator it = m_commands.begin(); it != m_commands.end(); ++it) {
			(*it).second.m_dirty &= ~id;
		}
	}

private:
	container_t m_commands;
	ui_type m_dirty;
};

/////////////////////////////////////////////////////////////////////////////
// CText state

class CText : public state_base< std::basic_string<TCHAR> > {

public:
	bool UIAddText(command_t nCmd, const value_type& val = value_type()) { 
		return add_state(nCmd, val, value_type(), false);
	}
	bool UIAddLocalText(command_t nCmd, const value_type& valDefault = value_type()) { 
		return add_state(nCmd, valDefault, valDefault, true);
	}
	bool UIAddLocalText(command_t nCmd, const value_type& valDefault, const value_type& val) { 
		return add_state(nCmd, val, valDefault, true);
	}
	bool UIDeleteText(command_t nCmd) { 
		return remove_state(nCmd);
	}
	bool UISetText(command_t nCmd, const value_type& val = value_type()) {
		return set_state(nCmd, val);
	}
	bool UIGetText(command_t nCmd, value_type& val) {
		return value(nCmd, val);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CUIUpdate

template<class T, UI_TMPL>
class CUIUpdate : public typelist::inherit_all<make_list<UI_TMPL_ARG>::result> {

public:
	typedef CUIUpdate self;
	typedef make_list<UI_TMPL_ARG>::result ui_list_t;

public:
	// converts type of UI element to UI's id
	template<class Type> struct type2id { 
		enum{ id = 0x00000001 << typelist::index_of<ui_list_t, Type>::value };
	};

public:
	void UIUpdate() {
		T* pT = static_cast<T*>(this);

		for(container_t::const_iterator i = m_windows.begin(); i != m_windows.end(); ++i) {
			helper<ui_list_t>::update(pT, *this, (*i).first, (*i).second);
		}
		pT->clean_states(status_dirty);
	}

public:
	void add_window(HWND hwnd, ui_type id) {
		container_t::iterator it = m_windows.find(hwnd);
		if(it == m_windows.end())
			m_windows[hwnd] = id;
		else
			(*it).second = (*it).second|id;
	}

	void remove_window(HWND hwnd, ui_type id) {
		container_t::iterator it = m_windows.find(hwnd);
		if(it == m_windows.end())
			return;

		if((*it).second == id)
			m_windows.erase(it);
		else
			(*it).second = (*it).second & ~id;
	}

	template<class UI> 
	void update_ui(UI& ui) {
		T* pT = static_cast<T*>(this);
		for(container_t::const_iterator it = m_windows.begin(); it != m_windows.end(); ++it) {
			if((*it).second & type2id<UI>::id) {
				pT->apply_states((*it).first, ui);
			}
		}
	}

	// helper
	template<typename L> struct helper {
		static void update(T* pT, self& x, HWND hwnd, ui_type flags) {
			if(flags & type2id<L::head>::id)
				pT->apply_states(hwnd, static_cast<L::head&>(x));
			helper<L::tail>::update(pT, x, hwnd, flags);
		}
	};
	template<> struct helper<nil> {
		static void update(T*, self&, HWND, ui_type) {}
	};

private:
	typedef std::map<HWND, ui_type> container_t;
	container_t m_windows;
};

} // wtlx

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // STL_IMPL_HPP
