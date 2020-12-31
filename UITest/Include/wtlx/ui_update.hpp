//
// ui_update.hpp
//
//  Copyright (c) 2001 Vladimir Voinkov voinkov@hotbox.ru
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef WTLX_UIAPDATE_HPP
#define WTLX_UIAPDATE_HPP

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#endif // _MSC_VER

/////////////////////////////////////////////////////////////////////////////
// Windows message to request UI update

#define WM_SETUI WM_USER + 1000

namespace wtlx
{

/////////////////////////////////////////////////////////////////////////////
// UI elements ids

enum { status_dirty = 0xFF, status_clear = 0x00 };

typedef DWORD ui_type;

#define UI_TMPL \
	typename UI01 = nil, typename UI02 = nil, typename UI03 = nil, typename UI04 = nil, typename UI05 = nil, \
	typename UI06 = nil, typename UI07 = nil, typename UI08 = nil, typename UI09 = nil, typename UI10 = nil, \
	typename UI11 = nil, typename UI12 = nil, typename UI13 = nil, typename UI14 = nil, typename UI15 = nil, \
	typename UI16 = nil, typename UI17 = nil, typename UI18 = nil, typename UI19 = nil, typename UI20 = nil, \
	typename UI21 = nil, typename UI22 = nil, typename UI23 = nil, typename UI24 = nil, typename UI25 = nil, \
	typename UI26 = nil, typename UI27 = nil, typename UI28 = nil, typename UI29 = nil, typename UI30 = nil, \
	typename UI31 = nil, typename UI32 = nil

#define UI_TMPL_ARG \
	UI01, UI02, UI03, UI04, UI05, UI06, UI07, UI08, UI09, UI10, UI11, UI12, UI13, UI14, UI15, UI16, UI17, UI18, UI19, UI20, \
	UI21, UI22, UI23, UI24, UI25, UI26, UI27, UI28, UI29, UI30, UI31, UI32

#define STATE_TMPL \
	typename S01 = nil, typename S02 = nil, typename S03 = nil, typename S04 = nil, typename S05 = nil, \
	typename S06 = nil, typename S07 = nil, typename S08 = nil, typename S09 = nil, typename S10 = nil, \
	typename S11 = nil, typename S12 = nil, typename S13 = nil, typename S14 = nil, typename S15 = nil, \
	typename S16 = nil, typename S17 = nil, typename S18 = nil, typename S19 = nil, typename S20 = nil, \
	typename S21 = nil, typename S22 = nil, typename S23 = nil, typename S24 = nil, typename S25 = nil, \
	typename S26 = nil, typename S27 = nil, typename S28 = nil, typename S29 = nil, typename S30 = nil, \
	typename S31 = nil, typename S32 = nil

#define STATE_TMPL_ARG \
	S01, S02, S03, S04, S05, S06, S07, S08, S09, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, \
	S21, S22, S23, S24, S25, S26, S27, S28, S29, S30, S31, S32

/////////////////////////////////////////////////////////////////////////////
// Others

typedef WORD command_t;

}

/////////////////////////////////////////////////////////////////////////////
// base definitions

#include <wtlx/type_list.hpp>

#ifdef _MAP_
#	include <wtlx/ui_update/stl_impl.hpp>
#else
#	include <wtlx/ui_update/wtl_impl.hpp>
#endif

#include <wtlx/ui_update/states_impl.hpp>

/////////////////////////////////////////////////////////////////////////////
// states

#include <wtlx/ui_update/style.hpp>
#include <wtlx/ui_update/parts.hpp>

/////////////////////////////////////////////////////////////////////////////
// UIs

#include <wtlx/ui_update/command.hpp>
#include <wtlx/ui_update/tool_bar.hpp>
#include <wtlx/ui_update/status_bar.hpp>
#include <wtlx/ui_update/re_bar.hpp>
#include <wtlx/ui_update/window_container.hpp>

/////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif // _MSC_VER

#endif // WTLX_UIAPDATE_HPP
