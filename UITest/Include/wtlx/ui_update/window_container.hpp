//
// window_container.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef WINDOW_CONTAINER_HPP
#define WINDOW_CONTAINER_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

#ifdef _MAP_
#else // _MAP_
#	include <atlmisc.h>
#endif // _MAP_

namespace wtlx
{

/////////////////////////////////////////////////////////////////////////////
// CUIWindowContainer

template<class T>
class CUIWindowContainer {
public:
	typedef CUIWindowContainer<T> self;

public:
	void UIAddWindowContainer(HWND hwnd) {
		T* pT = static_cast<T*>(this);
		pT->add_window(hwnd, T::type2id<self>::id);
	}
	void UIUpdateWindowContainer() {
		T* pT = static_cast<T*>(this);
		pT->update_ui(*this);
		pT->clean_states(T::type2id<self>::id);
	}

public:
	template<class State>
	void update_state(HWND hwnd, State& state) {
		wtlx::UIUpdateWindowContainer(hwnd, state, T::type2id<self>::id);
	}
};

template<class State>
inline void UIUpdateWindowContainer(HWND, const State&, ui_type) {}

inline void UIUpdateWindowContainer(HWND hwnd, CStyle& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CStyle::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(state.dirty(id, it)) {
			CStyle::value_type val = state.value(it);
			command_t cmd = state.command(it);

			HWND hchild = ::GetDlgItem(hwnd, cmd);
			::EnableWindow(hchild, val&CStyle::Enable ? TRUE : FALSE);
			::SendMessage(hchild, BM_SETCHECK, val&CStyle::Checked || val&CStyle::Radio, 0L);

			if(val&CStyle::Visible && !IsWindowVisible(hchild))
				::ShowWindow(hchild, SW_SHOWNA);
			
			if(!(val&CStyle::Visible) && IsWindowVisible(hchild))
				::ShowWindow(hchild, SW_HIDE);

			if(val&CStyle::Default) {
				DWORD ret = (DWORD)::SendMessage(hwnd, DM_GETDEFID, 0, 0L);
				if(HIWORD(ret) == DC_HASDEFID) {
					HWND hodldef = ::GetDlgItem(hwnd, (int)(short)LOWORD(ret));
					::SendMessage(hodldef, BM_SETSTYLE, BS_PUSHBUTTON, MAKELPARAM(TRUE, 0));
				}
				::SendMessage(hwnd, DM_SETDEFID, cmd, 0L);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

#ifdef _MAP_

inline void UIUpdateWindowContainer(HWND hwnd, CText& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(state.dirty(id, it))
			::SetWindowText(::GetDlgItem(hwnd, state.command(it)), state.value(it).c_str());
	}
}

#else // _MAP_

inline void UIUpdateWindowContainer(HWND hwnd, CText& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(state.dirty(id, it))
			::SetWindowText(::GetDlgItem(hwnd, state.command(it)), state.value(it));
	}
}
#endif // _MAP_

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // WINDOW_CONTAINER_HPP
