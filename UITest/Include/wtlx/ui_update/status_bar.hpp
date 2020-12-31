//
// status_bar.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

#ifdef _MAP_
#	include <string>
#else // _MAP_
#	include <atlmisc.h>
#endif // _MAP_

namespace wtlx
{

/////////////////////////////////////////////////////////////////////////////
// CUIStatusBar

template<class T>
class CUIStatusBar {

public:
	typedef CUIStatusBar<T> self;

public:
	void UIAddStatusBar(HWND hwnd) {
		T* pT = static_cast<T*>(this);
		pT->add_window(hwnd, T::type2id<self>::id);
	}
	void UIUpdateStatusBar() {
		T* pT = static_cast<T*>(this);
		pT->update_ui(*this);
		pT->clean_states(T::type2id<self>::id);
	}

public:
	template<class State>
	void update_state(HWND hwnd, State& state) {
		wtlx::UIUpdateStatusBar(hwnd, state, T::type2id<self>::id);
	}
};

/////////////////////////////////////////////////////////////////////////////

template<class State>
inline void UIUpdateStatusBar(HWND, const State&, ui_type) {}

/////////////////////////////////////////////////////////////////////////////

inline void UIUpdateStatusBar(HWND hwnd, CParts& state, ui_type id) {

	if(!state.dirty(id))
		return;

	CParts::value_type val = state.value();
	::SendMessage(hwnd, SB_SETPARTS, (WPARAM)val.Parts(), (LPARAM)val.Widths());
}

/////////////////////////////////////////////////////////////////////////////

#ifdef _MAP_

inline void UIUpdateStatusBar(HWND hwnd, CText& state, ui_type id) {

	if(!state.dirty(id))
		return;

	INT nCount = ::SendMessage(hwnd, SB_GETPARTS, 0, 0L);

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		command_t nCmd = state.command(it);
		if(nCmd < nCount && state.dirty(id, it)) {
			::SendMessage(hwnd, SB_SETTEXT, nCmd, (LPARAM)(state.value(it).c_str()));
		}
	}
}

#else // _MAP_

inline void UIUpdateStatusBar(HWND hwnd, CText& state, ui_type id) {

	if(!state.dirty(id))
		return;

	INT nCount = ::SendMessage(hwnd, SB_GETPARTS, 0, 0L);

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		command_t nCmd = state.command(it);
		if(nCmd < nCount && state.dirty(id, it))
			::SendMessage(hwnd, SB_SETTEXT, nCmd, (LPARAM)(LPCTSTR)state.value(it));
	}
}

#endif // _MAP_

} // wtlx

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // STATUS_BAR_HPP
