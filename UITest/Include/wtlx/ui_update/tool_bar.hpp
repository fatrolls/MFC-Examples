//
// tool_bar.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef TOOL_BAR_HPP
#define TOOL_BAR_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

namespace wtlx
{

/////////////////////////////////////////////////////////////////////////////
// CUIToolBar

template<class T>
class CUIToolBar {
public:
	typedef CUIToolBar<T> self;

public:
	void UIAddToolBar(HWND hwnd) {
		T* pT = static_cast<T*>(this);
		pT->add_window(hwnd, T::type2id<self>::id);
	}

	void UIUpdateToolBar() {
		T* pT = static_cast<T*>(this);
		pT->update_ui(*this);
		pT->clean_states(T::type2id<self>::id);
	}

public:
	template<class State>
	void update_state(HWND hwnd, State& state) {
		wtlx::UIUpdateToolBar(hwnd, state, T::type2id<self>::id);
	}
};

/////////////////////////////////////////////////////////////////////////////

template<class State>
inline void UIUpdateToolBar(HWND, const State&, ui_type) {}

/////////////////////////////////////////////////////////////////////////////

inline void UIUpdateToolBar(HWND hwnd, CStyle& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CStyle::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(state.dirty(id, it)) {
			command_t cmd = state.command(it);
			CStyle::value_type val = state.value(it);
			::SendMessage(hwnd, TB_ENABLEBUTTON, cmd, (LPARAM)(val&CStyle::Enable ? TRUE : FALSE));
			::SendMessage(hwnd, TB_HIDEBUTTON, cmd, (LPARAM)(val&CStyle::Visible ? FALSE : TRUE));
			::SendMessage(hwnd, TB_CHECKBUTTON, cmd, (LPARAM)(val&CStyle::Checked ? TRUE : FALSE));
			::SendMessage(hwnd, TB_PRESSBUTTON, cmd, (LPARAM)(val&CStyle::Radio ? TRUE : FALSE));
		}
	}
}

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // TOOL_BAR_HPP
