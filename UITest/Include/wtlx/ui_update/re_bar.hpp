//
// re_bar.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef RE_BAR_HPP
#define RE_BAR_HPP

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
// CUIReBar

template<class T>
class CUIReBar {
public:
	typedef CUIReBar<T> self;

public:
	void UIAddReBar(HWND hwnd) {
		T* pT = static_cast<T*>(this);
		pT->add_window(hwnd, T::type2id<self>::id);
	}

	void UIUpdateReBar() {
		T* pT = static_cast<T*>(this);
		pT->update_ui(*this);
		pT->clean_states(T::type2id<self>::id);
	}

public:
	template<class State>
	void update_state(HWND hwnd, State& state) {
		wtlx::UIUpdateReBar(hwnd, state, T::type2id<self>::id);
	}
};

/////////////////////////////////////////////////////////////////////////////

template<class State>
inline void UIUpdateReBar(HWND, const State&, ui_type) {}

/////////////////////////////////////////////////////////////////////////////

inline void UIUpdateReBar(HWND hwnd, CStyle& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CStyle::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(!state.dirty(id, it)) 
			continue;

		CStyle::value_type val = state.value(it);
		int band = ::SendMessage(hwnd, RB_IDTOINDEX, state.command(it), 0L);
		::SendMessage(hwnd, RB_SHOWBAND, band, val&CStyle::Visible);
	}
}

/////////////////////////////////////////////////////////////////////////////

#ifdef _MAP_

inline void UIUpdateReBar(HWND hwnd, CText& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(!state.dirty(id, it)) 
			continue;

		int band = ::SendMessage(hwnd, RB_IDTOINDEX, state.command(it), 0L);
		
		REBARBANDINFO bbi;
		bbi.cbSize = sizeof(bbi);
		bbi.fMask = RBBIM_TEXT;
		bbi.lpText = const_cast<LPTSTR>(state.value(it).c_str());
		bbi.cch = 0;
		::SendMessage(hwnd, RB_SETBANDINFO, band, (LPARAM)&bbi);
	}
}

#else // _MAP_

inline void UIUpdateReBar(HWND hwnd, CText& state, ui_type id) {

	if(!state.dirty(id))
		return;

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		if(!state.dirty(id, it)) 
			continue;

		int band = ::SendMessage(hwnd, RB_IDTOINDEX, state.command(it), 0L);
		
		REBARBANDINFO bbi;
		bbi.cbSize = sizeof(bbi);
		bbi.fMask = RBBIM_TEXT;
		bbi.lpText = (LPTSTR)(LPCTSTR)state.value(it);
		bbi.cch = 0;
		::SendMessage(hwnd, RB_SETBANDINFO, band, (LPARAM)&bbi);
	}
}

#endif // _MAP_

} // wtlx

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // RE_BAR_HPP
