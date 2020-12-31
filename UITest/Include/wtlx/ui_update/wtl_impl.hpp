//
// wtl_impl.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef WTL_IMPL_HPP
#define WTL_IMPL_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

#include <atlmisc.h>
#include <wtlx/type_list.hpp>

namespace wtlx
{
/////////////////////////////////////////////////////////////////////////////
// state_base

template<class Value>
class state_base {

public:
	typedef Value value_type;
	typedef int iterator;

private:
	struct holder_t {
		holder_t(ui_type dirty, bool bDef, const value_type& val, const value_type& valDef) :
			m_dirty(dirty), m_default(bDef), m_value(val), m_default_value(valDef) {}
		ui_type m_dirty;
		bool m_default;
		value_type m_value;
		value_type m_default_value;
	};
	typedef CSimpleMap<command_t, holder_t> container_t;

public:
	state_base() : m_dirty(status_clear) {}

	bool add_state(command_t nCmd, const value_type& value, const value_type& valueDef = value_type(), 
		bool isDefault = false) {
		
		holder_t holder(status_dirty, isDefault, value, valueDef); 

		int it = m_commands.FindKey(nCmd);
		if(it == -1) {
			if(m_commands.Add(nCmd, holder) == FALSE)
				return false;
		}
		else {
			m_commands.GetValueAt(it).~holder_t();
			m_commands.SetAtIndex(it, nCmd, holder);
		}
		m_dirty = status_dirty;
		return true;
	}
	bool remove_state(command_t nCmd) {
		// BUG: CSimpleMap::Remove() does not call destructors then size is 1
		if(m_commands.GetSize() == 1 && m_commands.GetKeyAt(0) == nCmd) {
			// RemoveAll does
			m_commands.RemoveAll();
			return true;
		}
		return (m_commands.Remove(nCmd) != FALSE); 
	}
	bool set_state(command_t nCmd, const value_type& value) {
		int it = m_commands.FindKey(nCmd);
		if(it == -1)
			return false;

		holder_t& holder = m_commands.GetValueAt(it);
		holder.m_dirty = status_dirty; 
		holder.m_value = value; 
		m_dirty = status_dirty;
		return true;
	}

public:
	iterator begin() const { 
		return 0; 
	}
	iterator end() const { 
		return m_commands.GetSize(); 
	}
	command_t command(iterator it) const { 
		return m_commands.GetKeyAt(it); 
	}
	const value_type& value(iterator it) const { 
		return m_commands.GetValueAt(it).m_value; 
	}
	bool value(command_t command, value_type& val) const {
		int i = m_commands.FindKey(command);
		if(i == -1)
			return false;

		val = m_commands.GetValueAt(i).m_value;
		return true;
	}
	bool is_default(iterator it) const {
		return m_commands.GetValueAt(it).m_default;
	}
	const value_type& default_value(iterator it) const { 
		return m_commands.GetValueAt(it).m_default_value;
	}
	void default_value(iterator it, const value_type& value) { 
		m_commands.GetValueAt(it).m_default_value = value;
	}
	void set_default_value() { 
		for(iterator it = begin(); it != end(); ++it) {
			holder_t& holder = m_commands.GetValueAt(it);
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
		return ((m_commands.GetValueAt(it).m_dirty & id) != 0); 
	}
	void clean(ui_type id = status_dirty) {
		m_dirty &= ~id;
		for(int it = 0; it < m_commands.GetSize(); ++it)
			m_commands.GetValueAt(it).m_dirty &= ~id;
	}

private:
	container_t m_commands;
	ui_type m_dirty;
};

/////////////////////////////////////////////////////////////////////////////
// CText state

class CText : public state_base<CString> {

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


		for(int i = 0; i < m_windows.GetSize(); ++i) {
			HWND hwnd = m_windows.GetKeyAt(i);
			ui_type flags = m_windows.GetValueAt(i);
			helper<ui_list_t>::update(pT, *this, hwnd, flags);
		}

		pT->clean_states(status_dirty);
	}

public:
	void add_window(HWND hwnd, ui_type id) {
		int i = m_windows.FindKey(hwnd);
		if(i == -1)
			m_windows.Add(hwnd, id);
		else {
			ui_type byte = m_windows.GetValueAt(i)|id;
			m_windows.SetAtIndex(i, hwnd, byte);
		}
	}

	void remove_window(HWND hwnd, ui_type id) {
		int i = m_windows.FindKey(hwnd)
		if(i == -1)
			return;

		if(m_windows.GetValueAt(i) == id)
			m_windows.Remove(hwnd);
		else {
			ui_type byte = m_windows.GetValueAt(i) & ~id;
			m_windows.SetAtIndex(i, hwnd, byte);
		}
	}

	template<class UI> 
	void update_ui(UI& ui) {
		T* pT = static_cast<T*>(this);
		for(int i = 0; i < m_windows.GetSize(); ++i) {
			if(m_windows.GetValueAt(i) & type2id<UI>::id) {
				pT->apply_states(m_windows.GetKeyAt(i), ui);
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
	typedef CSimpleMap<HWND, ui_type> container_t;
	container_t m_windows;
};

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // WTL_IMPL_HPP
