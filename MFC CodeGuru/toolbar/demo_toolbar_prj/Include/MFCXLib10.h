//
// Copyright © 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", without WARRANTY OF ANY KIND, and the user
// holds Kirk Stowell blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#ifndef MFCXLB10__H
#define MFCXLB10__H

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifdef _DEBUG
#pragma comment(lib,"mfcxlib10d.lib")
#pragma message("Automatically linking with mfcxlib10d.dll")
#else
#pragma comment(lib,"mfcxlib10r.lib")
#pragma message("Automatically linking with mfcxlib10r.dll")
#endif

#ifndef TB_SETEXTENDEDSTYLE
// Old commctrl.h compatibility
#define TB_SETIMAGELIST         (WM_USER + 48) 
#define TB_SETHOTIMAGELIST      (WM_USER + 52) 
#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#define TBSTYLE_TRANSPARENT     0x8000
#define TBSTYLE_AUTOSIZE        0x0010			// automatically calculate the cx of the button 
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

#include <MFCXFrameWnd.h>
#include <MFCXMDIFrameWnd.h>
#include <MFCXControlBar.h>
#include <MFCXToolBar.h>
#include <MFCXTreeCtrl.h>
#include <MFCXListMenu.h>
#include <MFCXSubclassWnd.h>
#include <MFCXRebarCtrl.h>
#include <MFCXHyperLink.h>
#include <MFCXMenuMgr.h>

#ifdef AUTO_SUBCLASS
// Automatically use new mfc extensions.
#define CToolBar		CMFCXToolBar
#define CControlBar		CMFCXControlBar
#define CTreeCtrl		CMFCXTreeCtrl
#define CMenuMgr		CMFCXMenuMgr
#define CSubclassWnd	CMFCXSubclassWnd
#define CListMenu		CMFCXListMenu
#define CRebarCtrl		CMFCXRebarCtrl
#define CRebarInfo		CMFCXRebarInfo
#define CRebarBandInfo	CMFCXRebarBandInfo
#define CHyperLink		CMFCXHyperLink
#define CFrameWnd		CMFCXFrameWnd
#define CMDIFrameWnd	CMFCXMDIFrameWnd
#define CMenuMgr		CMFCXMenuMgr
#endif

#endif