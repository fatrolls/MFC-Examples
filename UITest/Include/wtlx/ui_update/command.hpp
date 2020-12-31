//
// command.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_HPP
#define COMMAND_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4239 )
#endif // _MSC_VER

#ifdef _MAP_
#	include <string>
#else
#	include <atlmisc.h>
#endif

//#include <boost/type_traits.hpp>

namespace wtlx
{

/////////////////////////////////////////////////////////////////////////////
// Generic<Programming>: Mappings between Types and Values
// by Andrei Alexandrescu
// http://www.cuj.com/experts/1810/alexandr.htm?topic=experts

template <class T, class U>
class conversion
{
    typedef char Small;
    struct Big { char dummy[2]; };
    static Small Test(U);
    static Big Test(...);
	static T MakeT();

public:
    enum { exists = sizeof( Test(MakeT()) ) == sizeof(Small) };
};

/////////////////////////////////////////////////////////////////////////////
// CUICommand

template<class T>
class CUICommand {
public:
	typedef CUICommand<T> self;

public:
	template<class State> void update_state(HWND hwnd, State& state) {}
	
	template<class State> void update_state(HMENU hmenu, State& state) {
		wtlx::UIUpdateMenuBarElement(hmenu, state);
	}

public:
	BEGIN_MSG_MAP(self)
		MESSAGE_HANDLER(WM_INITMENUPOPUP, OnInitMenuPopup)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		MESSAGE_HANDLER(WM_SETUI, OnSetUI)
	END_MSG_MAP()

	LRESULT OnInitMenuPopup(UINT, WPARAM wParam, LPARAM, BOOL& bHandled) {
		bHandled = FALSE;
		HMENU hmenu = (HMENU)wParam;
		if(!hmenu)
			return 1;

		static_cast<T&>(*this).apply_states(hmenu, *this);
		return 0;
	}

	LRESULT OnSetUI(UINT, WPARAM, LPARAM, BOOL&) {
		T* pT = static_cast<T*>(this);
		pT->UISetDefault();
		return 0L;
	}

	LRESULT OnCommand(UINT, WPARAM wParam, LPARAM, BOOL& bHandled) {
		bHandled = FALSE;

		// if(m_bBlockAccelerators && HIWORD(wParam) == 1)	
		// accelerators only
		if(HIWORD(wParam) != 1)
			return 0L;

		const T* pT = static_cast<const T*>(this);
		//bHandled = accelerators_helper<boost::is_convertible<T, CStyle>::value>::process(LOWORD(wParam), pT);
		bHandled = accelerators_helper<conversion<T, CStyle>::exists>::process(LOWORD(wParam), pT);
		return 0L;
	}

	// accelerators_helper class
	template<const bool Conv> struct accelerators_helper {
		static bool process(WORD cmd, const T* pT) {
			const CStyle& style = static_cast<const CStyle&>(*pT);

			CStyle::value_type val;
			return (style.value(cmd, val) && !(val&CStyle::Enable));
		}
	};
	template<> struct accelerators_helper<false> {
		static bool process(WORD cmd, const T* pT) { return false; }
	};
};

/////////////////////////////////////////////////////////////////////////////

template<class State>
inline void UIUpdateMenuBarElement(HMENU, const State&) {}

/////////////////////////////////////////////////////////////////////////////

inline void UIUpdateMenuBarElement(HMENU hmenu, CStyle& state) {

	MENUITEMINFO mii;
	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STATE;

	typedef CStyle::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		CStyle::value_type val = state.value(it);
		command_t cmd = state.command(it);
		if(cmd > 0) {
			if(val&CStyle::Enable)
				mii.fState |= MFS_ENABLED;
			else
				mii.fState |= MFS_DISABLED|MFS_GRAYED;
			
			if(val&CStyle::Checked)
				mii.fState |= MFS_CHECKED;
			else
				mii.fState |= MFS_UNCHECKED;
			
			if(val&CStyle::Default)
				mii.fState |= MFS_DEFAULT;

			::SetMenuItemInfo(hmenu, state.command(it), FALSE, &mii);
			mii.fState = 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////

#ifdef _MAP_

inline void UIUpdateMenuBarElement(HMENU hmenu, CText& state) {

	MENUITEMINFO mii;
	memset(&mii, 0, sizeof(mii));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_TYPE;
	mii.fType = MFT_STRING;

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		mii.wID = state.command(it);
		if(mii.wID > 0) {
			mii.dwTypeData = const_cast<LPTSTR>(state.value(it).c_str());
			::SetMenuItemInfo(hmenu, mii.wID, FALSE, &mii);
			mii.dwTypeData = NULL;
		}
	}
}

#else // _MAP_

inline void UIUpdateMenuBarElement(HMENU hmenu, CText& state) {

	MENUITEMINFO mii;
	memset(&mii, 0, sizeof(mii));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_TYPE;
	mii.fType = MFT_STRING;

	typedef CText::iterator IT;
	for(IT it = state.begin(); it != state.end(); ++it) {
		mii.wID = state.command(it);
		if(mii.wID > 0) {
			mii.dwTypeData = const_cast<LPTSTR>(static_cast<LPCTSTR>(state.value(it)));
			::SetMenuItemInfo(hmenu, mii.wID, FALSE, &mii);
			mii.dwTypeData = NULL;
		}
	}
}

#endif // _MAP_

}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // COMMAND_HPP
